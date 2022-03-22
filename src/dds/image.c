#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <brrtools/brrlog.h>
#include <brrtools/brrnum.h>

#include "dds/image.h"

void
dds_image_free(dds_image_t *const image)
{
	if (!image)
		return;
	if (image->principle)
		free(image->principle);
	memset(image, 0, sizeof(*image));
}

static brru4 i_calculate_data_sizes(dds_image_t *dds, int fix)
{
	brru4 errflag = 0;
	dds_image_t D = *dds;

	brru4 depth = (D._meta.mode&DDMM_VOLUME?D.header.depth:1);
	// Check pitch/linear size (this is probably most wrong out of all)
	if (HASFLAG(D._meta.mode, DDMM_VOLUME)) {
		BRRLOG_WAR("DDS Support for volumetric/depth textures is currently (entirely) incomplete.");
	}
	if (HASFLAG(D._meta.mode, DDMM_CUBEMAP)) {
		BRRLOG_WAR("DDS Support for cubemaps is currently (entirely) incomplete.");
	}
	if (HASFLAG(D._meta.mode, DDMM_UNCOMPRESSED)) {
		brru4 calcpitch = (D.header.width * D.header.ddspf.rgb_bits) >> 3;
		if (HASFLAG(D.header.flags, DDSD_LINEARSIZE)) {
			BRRLOG_WAR("DDS uncompressed image has flag DDSD_LINEARSIZE");
			if (fix)
				D.header.flags &= ~DDSD_LINEARSIZE;
		}
		if (!HASFLAG(D.header.flags, DDSD_PITCH)) {
			BRRLOG_WAR("DDS uncompressed image missing required flag DDSD_PITCH");
			if (fix)
				D.header.flags |= DDSD_PITCH;
		}
		if (D.header.pitch != calcpitch) {
			BRRLOG_WAR("DDS uncompressed image pitch %zu mismatch with calculated %zu", D.header.pitch, calcpitch);
			if (fix)
				D.header.pitch = calcpitch;
		}
		D._meta.principle_size = D.header.height * D.header.pitch * depth;
	} else if (HASFLAG(D._meta.mode, DDMM_COMPRESSED)) {
		brru4 calcsize = 0;
		// Specifically this part I think is most wrong, but I have nothing to test with
		// and haven't found (looked for) any detailed, relevant documentation.
		if (HASFLAG(D._meta.mode, DDMM_PACKED)) {
			calcsize = (4 * (D.header.width+1)/2) * (4 * (D.header.height+1)/2);
		} else if (HASFLAG(D._meta.mode, DDMM_DXT10)) {
			// TODO Linear size is calculated per-format.
			BRRLOG_WAR("DDS Support for DXGI extended formats currently incomplete.");
			calcsize = 0;
		} else {
			calcsize =
				brrnum_umax(1, (D.header.width + 3) >> 2) *
				brrnum_umax(1, (D.header.height+ 3) >> 2) *
				8;
			if (HASFLAG(D._meta.mode, DDMM_ALPHABLOCK))
				calcsize <<= 1;
		}

		if (HASFLAG(D.header.flags, DDSD_PITCH)) {
			BRRLOG_WAR("DDS compressed image has flag DDSD_PITCH");
			if (fix)
				D.header.flags &= ~DDSD_PITCH;
		}
		if (!HASFLAG(D.header.flags, DDSD_LINEARSIZE)) {
			BRRLOG_WAR("DDS compressed image missing required flag DDSD_LINEARSIZE");
			if (fix)
				D.header.flags |= DDSD_LINEARSIZE;
		}
		if (D.header.linear_size != calcsize) {
			BRRLOG_WAR("DDS compressed image linear size %zu mismatch with calculated %zu", D.header.linear_size, calcsize);
			if (fix)
				D.header.linear_size = calcsize;
		}
		D._meta.principle_size = D.header.linear_size;
	}

	// Calculate ancillary_size
	if (HASFLAG(D._meta.mode, DDMM_MIPMAP)) {
		// I should think that mipmaps take up an extra 1/3 principle_size bytes in the file,
		// but that doesn't seem to be the case.
		brrsz block = 8 + (D._meta.mode&DDMM_MIPMAP?8:0);
		brrsz sz = D._meta.principle_size >> 2;
		for (brrsz i = 1; i < D.header.mipmaps; ++i) {
			D._meta.ancillary_size += sz;
			sz = brrnum_umax(block, sz >> 2);
		}
	} else if (HASFLAG(D._meta.mode, DDMM_CUBEMAP | DDMM_VOLUME)) {
		BRRLOG_WAR("DDS Reading extra data from cubemaps/volumetrics is currently unsupported.");
		D._meta.ancillary_size = 0;
	} else {
		D._meta.ancillary_size = 0;
	}
	*dds = D;

	return errflag;
}
static brru4 i_validate_headers(dds_image_t *dds, int fix)
{
	brru4 errflag = 0;
	dds_image_t D = *dds;

	if (D.header.size != DDS_HEADER_SIZE) {
		BRRLOG_WAR("DDS header size set to invalid value %zu, should be %zu", D.header.size, DDS_HEADER_SIZE);
		if (fix)
			D.header.size = DDS_HEADER_SIZE;
	}
	//
	// Check required flags
	if (!(D.header.flags & DDSD_CAPS)) {
		BRRLOG_WAR("DDS header missing required flag DDSD_CAPS");
		if (fix)
			D.header.flags |= DDSD_CAPS;
	}
	if (!(D.header.flags & DDSD_HEIGHT)) {
		BRRLOG_WAR("DDS header missing required flag DDSD_HEIGHT");
		if (fix)
			D.header.flags |= DDSD_HEIGHT;
	}
	if (!(D.header.flags & DDSD_WIDTH)) {
		BRRLOG_WAR("DDS header missing required flag DDSD_WIDTH");
		if (fix)
			D.header.flags |= DDSD_WIDTH;
	}
	if (!(D.header.flags & DDSD_PIXELFORMAT)) {
		BRRLOG_WAR("DDS header missing required flag DDSD_PIXELFORMAT");
		if (fix)
			D.header.flags |= DDSD_PIXELFORMAT;
	}
	//
	// Get meta information
	if (D.header.mipmaps > 1 || D.header.flags & DDSD_MIPMAPCOUNT || D.header.caps & DDSCAPS_MIPMAP) {
		D._meta.mode |= DDMM_MIPMAP;
	}
	if (D.header.depth > 1 || D.header.flags & DDSD_DEPTH || D.header.caps2 & DDSCAPS2_VOLUME)
		D._meta.mode |= DDMM_VOLUME;
	if (D.header.caps2 & DDSCAPS2_CUBEMAP) {
		D._meta.mode |= DDMM_CUBEMAP;
		if (D.header.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEX) D._meta.cube_faces++;
		if (D.header.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEY) D._meta.cube_faces++;
		if (D.header.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEZ) D._meta.cube_faces++;
		if (D.header.caps2 & DDSCAPS2_CUBEMAP_POSITIVEX) D._meta.cube_faces++;
		if (D.header.caps2 & DDSCAPS2_CUBEMAP_POSITIVEY) D._meta.cube_faces++;
		if (D.header.caps2 & DDSCAPS2_CUBEMAP_POSITIVEZ) D._meta.cube_faces++;
	}
	//
	// Check mipmaps
	if (D._meta.mode & DDMM_MIPMAP) {
		// If D.mipmaps, then ensure DDSD_MIPMAPCOUNT and DDSCAPS_MIPMAP set accordingly
		if (D.header.mipmaps > 1) {
			if (!(D.header.flags & DDSD_MIPMAPCOUNT)) {
				BRRLOG_WAR("DDS with mipmaps missing flag DDSD_MIPMAPCOUNT");
				if (fix)
					D.header.flags |= DDSD_MIPMAPCOUNT;
			}
			if (!(D.header.caps & DDSCAPS_MIPMAP)) {
				BRRLOG_WAR("DDS with mipmaps missing flag DDSCAPS_MIPMAP");
				if (fix)
					D.header.caps |= DDSCAPS_MIPMAP;
			}
		} else {
			if (D.header.flags & DDSD_MIPMAPCOUNT) {
				BRRLOG_WAR("DDS without mipmaps has flag DDSD_MIPMAPCOUNT");
				if (fix)
					D.header.flags &= ~DDSD_MIPMAPCOUNT;
			}
			if (D.header.caps & DDSCAPS_MIPMAP) {
				BRRLOG_WAR("DDS without mipmaps has flag DDSCAPS_MIPMAP");
				if (fix)
					D.header.caps &= ~DDSCAPS_MIPMAP;
			}
		}
	}
	//
	// Check depth
	if (D._meta.mode & DDMM_VOLUME) {
		if (D.header.depth > 1) {
			if (!(D.header.flags & DDSD_DEPTH)) {
				BRRLOG_WAR("DDS volume texture missing flag DDSD_DEPTH");
				if (fix)
					D.header.flags |= DDSD_DEPTH;
			}
			if (!(D.header.caps2 & DDSCAPS2_VOLUME)) {
				BRRLOG_WAR("DDS volume texture missing flag DDSCAPS2_VOLUME");
				if (fix)
					D.header.caps2 |= DDSCAPS2_VOLUME;
			}
		} else {
			if (D.header.flags & DDSD_DEPTH) {
				BRRLOG_WAR("DDS without depth has flag DDSD_DEPTH");
				if (fix)
					D.header.flags &= ~DDSD_DEPTH;
			}
			if (D.header.caps2 & DDSCAPS2_VOLUME) {
				BRRLOG_WAR("DDS without depth has flag DDSCAPS2_VOLUME");
				if (fix)
					D.header.caps2 &= ~DDSCAPS2_VOLUME;
			}
		}
	}
	//
	// Check caps
	if (!(D.header.caps & DDSCAPS_TEXTURE)) {
		BRRLOG_WAR("DDS caps missing required flag DDSCAPS_TEXTURE");
		if (fix)
			D.header.caps |= DDSCAPS_TEXTURE;
	}
	if (D._meta.mode & DDMM_COMPLEX && !(D.header.caps & DDSCAPS_COMPLEX)) {
		BRRLOG_WAR("DDS with multiple surfaces missing flag DDSCAPS_COMPLEX");
		if (fix)
			D.header.caps |= DDSCAPS_COMPLEX;
	} else if (!(D._meta.mode & DDMM_COMPLEX) && D.header.caps & DDSCAPS_COMPLEX) {
		BRRLOG_WAR("DDS without multiple surfaces has flag DDSCAPS_COMPLEX");
		if (fix)
			D.header.caps &= ~DDSCAPS_COMPLEX;
	}
	if (!(D.header.caps2 & DDSCAPS2_CUBEMAP) && D._meta.cube_faces > 0) {
		BRRLOG_WAR("DDS with cubemaps missing flag DDSCAPS2_CUBEMAP");
		if (fix)
			D.header.caps2 |= DDSCAPS2_CUBEMAP;
	} else if (D.header.caps2 & DDSCAPS2_CUBEMAP && D._meta.cube_faces == 0) {
		BRRLOG_WAR("DDS without cubemaps has flag DDSCAPS2_CUBEMAP");
		if (fix)
			D.header.caps2 &= ~DDSCAPS2_CUBEMAP;
	}

	if (D.header.ddspf.flags & DDPF_FOURCC) {
		fcc_t f = D.header.ddspf.fourcc;
		if (f.id == dds_magics[dds_magic_dxt1]) {
			D._meta.mode |= DDMM_DXT1;
		} else if (f.id == dds_magics[dds_magic_dxt2]) {
			D._meta.mode |= DDMM_DXT2;
		} else if (f.id == dds_magics[dds_magic_dxt3]) {
			D._meta.mode |= DDMM_DXT3;
		} else if (f.id == dds_magics[dds_magic_dxt4]) {
			D._meta.mode |= DDMM_DXT4;
		} else if (f.id == dds_magics[dds_magic_dxt5]) {
			D._meta.mode |= DDMM_DXT5;
		} else if (f.id == dds_magics[dds_magic_dxt10]) {
			D._meta.mode |= DDMM_DXT10;
		} else {
			D._meta.mode |= DDMM_UNKNOWN;
			BRRLOG_WAR("Unrecognized pixelformat FourCC %4.4s 0x%08x", f.fourcc, f.id);
		}
	} else {
		D._meta.mode |= DDMM_UNCOMPRESSED;
	}

	// check extended header
	if (D._meta.mode & DDMM_DXT10) {
		switch (D.header10.format) {
			case DXGI_FORMAT_R8G8_B8G8_UNORM:
			case DXGI_FORMAT_G8R8_G8B8_UNORM:
			case DXGI_FORMAT_YUY2:D._meta.mode |= DDMM_PACKED; break;
			default:break;
		}
	}
	errflag |= i_calculate_data_sizes(&D, fix);
	*dds = D;

	return errflag;
}

int
dds_image_parse(dds_image_t *const image, const char *const data, brrsz data_len)
{
	/* TODO parsing still doesn't fail when it should (specifically in validate_headers,
	 * but it also doesn't check if the DDS fcc is correct or the ddspf mode/fcc is valid
	 * */
	if (!image || !data)
		return 1;

	if (data_len < DDS_HEADER_SIZE) {
		BRRLOG_ERR("Passed data of size %zu must be at least %zu bytes to contain a valid DDS header.", data_len, DDS_HEADER_SIZE);
	}

	brrsz of = 0;
	dds_image_t I = {.fourcc = dds_fccs[dds_magic_dds]};

	if (0 == memcmp(data, &dds_magics[dds_magic_dds], 4)) {
		/* skip 'DDS ' magic if present */
		of += 4;
	}

	/* First header */
	I.header = *(dds_header_t *)(data + of);
	of += DDS_HEADER_SIZE;

	if (I.header.ddspf.flags & DDPF_FOURCC && I.header.ddspf.fourcc.id == dds_magics[dds_magic_dxt10]) {
		/* Extended header */
		I.header10 = *(dds_header_dxt10_t *)(data + of);
		of += DDS_HEADER_DXT10_SIZE;
	}

	if (i_validate_headers(&I, 0)) {
		BRRLOG_ERR("Bad DDS data");
		return 1;
	}

	if (!(I.principle = malloc(I._meta.principle_size + I._meta.ancillary_size))) {
		BRRLOG_ERR("Failed to allocate %zu bytes for DDS data: %s (%i)", I._meta.principle_size + I._meta.ancillary_size, strerror(errno), errno);
		return 1;
	}
	I.ancillary = I.principle + I._meta.principle_size;

	memcpy(I.principle, data + of, I._meta.principle_size);
	of += I._meta.principle_size;
	memcpy(I.ancillary, data + of, I._meta.ancillary_size);
	of += I._meta.ancillary_size;
	if (of != data_len) {
		BRRLOG_WAR("Read %zu bytes %s than %zu given", of, of > data_len?"more":"less", data_len);
	}

	*image = I;
	return 0;
}

#define PRINT_FLAG(_f_, _flag_, _count_) do { \
	if (_f_ & _flag_) { \
		if (_count_) \
			BRRLOG_NORN("%s", " | "); \
		BRRLOG_NORN("%s", #_flag_); \
		_count_++; \
	} \
} while(0)
void
dds_image_log_headers(const dds_image_t *const image)
{
	if (!image)
		return;

	dds_header_t hd = image->header;
	dds_image_meta_t meta = image->_meta;

	BRRLOG_NOR("DDS Header:");
	BRRLOG_NORN("    Flags:       0x%08X ", hd.flags);
	{
		int bf = 0;
		PRINT_FLAG(hd.flags, DDSD_CAPS, bf);
		PRINT_FLAG(hd.flags, DDSD_HEIGHT, bf);
		PRINT_FLAG(hd.flags, DDSD_WIDTH, bf);
		PRINT_FLAG(hd.flags, DDSD_PITCH, bf);
		PRINT_FLAG(hd.flags, DDSD_PIXELFORMAT, bf);
		PRINT_FLAG(hd.flags, DDSD_MIPMAPCOUNT, bf);
		PRINT_FLAG(hd.flags, DDSD_LINEARSIZE, bf);
		PRINT_FLAG(hd.flags, DDSD_DEPTH, bf);
	}
	BRRLOG_NOR("");
	BRRLOG_NOR("    Width:       %u", hd.width);
	BRRLOG_NOR("    Height:      %u", hd.height);
	if (hd.flags & DDSD_PITCH)
		BRRLOG_NOR("    Pitch:       %u", hd.pitch);
	else if (hd.flags & DDSD_LINEARSIZE)
		BRRLOG_NOR("    Linear Size: %u", hd.linear_size);
	else
		BRRLOG_NOR("    Pitch (und): %u", hd.pitch);
	BRRLOG_NOR("    Depth:       %u", hd.depth);
	BRRLOG_NOR("    Mipmaps:     %u", hd.mipmaps);
	BRRLOG_NORN("    Reserved1:   ");
	for (int i = 0; i < 11; ++i) {
		BRRLOG_NORN("0x%08X ", hd.reserved1[i]);
	}
	BRRLOG_NORN("'");
	for (int i = 0; i < 11; ++i) {
		BRRLOG_NORN("%4.4s", (char *)&hd.reserved1[i]);
	}
	BRRLOG_NORN("' ");
	BRRLOG_NOR("");
	BRRLOG_NOR("    Pixel Format:");
	BRRLOG_NORN("        Flags:      0x%08X ", hd.ddspf.flags);
	{
		int bf = 0;
		PRINT_FLAG(hd.ddspf.flags, DDPF_ALPHAPIXELS, bf);
		PRINT_FLAG(hd.ddspf.flags, DDPF_ALPHA, bf);
		PRINT_FLAG(hd.ddspf.flags, DDPF_FOURCC, bf);
		PRINT_FLAG(hd.ddspf.flags, DDPF_RGB, bf);
		PRINT_FLAG(hd.ddspf.flags, DDPF_YUV, bf);
		PRINT_FLAG(hd.ddspf.flags, DDPF_LUMINANCE, bf);
	}
	BRRLOG_NOR("");
	BRRLOG_NOR("        FCC:        0x%08X %4.4s", hd.ddspf.fourcc.id, hd.ddspf.fourcc.fourcc);
	BRRLOG_NOR("        Pixel Bits: %u", hd.ddspf.rgb_bits);
	BRRLOG_NOR("        R_Mask:     0x%08X", hd.ddspf.r_mask);
	BRRLOG_NOR("        G_Mask:     0x%08X", hd.ddspf.g_mask);
	BRRLOG_NOR("        B_Mask:     0x%08X", hd.ddspf.b_mask);
	BRRLOG_NOR("        A_Mask:     0x%08X", hd.ddspf.a_mask);
	BRRLOG_NORN("    Caps:       0x%08X ", hd.caps);
	{
		int bf = 0;
		PRINT_FLAG(hd.caps, DDSCAPS_COMPLEX, bf);
		PRINT_FLAG(hd.caps, DDSCAPS_MIPMAP, bf);
		PRINT_FLAG(hd.caps, DDSCAPS_TEXTURE, bf);
	}
	BRRLOG_NOR("");
	BRRLOG_NORN("    Caps2:      0x%08X ", hd.caps2);
	{
		int bf = 0;
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP_POSITIVEX, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP_NEGATIVEX, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP_POSITIVEY, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP_NEGATIVEY, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP_POSITIVEZ, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_CUBEMAP_NEGATIVEZ, bf);
		PRINT_FLAG(hd.caps2, DDSCAPS2_VOLUME, bf);
	}
	BRRLOG_NOR("");
	BRRLOG_NOR("    Reserved2:  0x%08X", hd.reserved2);
	BRRLOG_NORN("Principle Data Size:   ");
	BRRLOGD_NORN(meta.principle_size, 10, brrfalse, ',', 3);
	BRRLOG_NOR(" bytes");
	BRRLOG_NORN("Ancillary Data Size: ");
	BRRLOGD_NORN(meta.ancillary_size, 10, brrfalse, ',', 3);
	BRRLOG_NOR(" bytes");
	BRRLOG_NORN("Total Data Size:     ");
	BRRLOGD_NORN(meta.principle_size + meta.ancillary_size, 10, brrfalse, ',', 3);
	BRRLOG_NOR(" bytes");
	BRRLOG_NORN("Total File Size:     ");
	BRRLOGD_NORN(meta.principle_size + meta.ancillary_size + DDS_HEADER_SIZE + (meta.mode&DDMM_DXT10?DDS_HEADER_DXT10_SIZE:0) + 4, 10, brrfalse, ',', 3);
	BRRLOG_NOR(" bytes");
	if (meta.mode & DDMM_DXT10) {
		dds_header_dxt10_t hd = image->header10;
		pr_desc_t format     = dxt10_dxgi_format_desc(hd.format);
		pr_desc_t dimension  = dxt10_dimension_desc(hd.dimension);
		pr_desc_t misc_flag  = dxt10_resource_misc_desc(hd.miscflag);
		pr_desc_t alpha_mode = dxt10_alpha_mode_desc(hd.alphaflag);

		BRRLOG_NOR("DDS DXT10 Header:");
		BRRLOG_NOR("    Format:     0x%08X %s", hd.format, format.display);
		BRRLOG_NOR("    Dimension:  0x%08X %s", hd.dimension, dimension.display);
		BRRLOG_NOR("    Misc Flag:  0x%08X %s", hd.miscflag, misc_flag.display);
		BRRLOG_NOR("    Array Size: %u", hd.arraysize);
		BRRLOG_NOR("    Alpha Mode: 0x%08X %s", hd.alphaflag, alpha_mode.display);
	}
}
