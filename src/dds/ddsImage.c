#include "dds/ddsImage.h"

#include <string.h> // strerror()
#include <errno.h>

#include "common/pdLog.h"
#include "common/pdUtil.h"
#include "dds/dds.h"
#include "dds/dxtn/dxt1.h"
#include "dds/dxtn/dxt2.h"
#include "dds/dxtn/dxt4.h"

#include "dds/ddsPrint.h"

static u32 calcSizes(ddsImageT *dds, int fix) {
	u32 flag = 0;
	u32 depth = (dds->meta.mode&DDMM_VOLUME?dds->header.depth:1);
	// Check pitch/linear size (this is probably most wrong out of all)
	if (HASFLAG(dds->meta.mode, DDMM_VOLUME)) {
		PD_LOG_WARN("DDS Support for volumetric/depth textures is currently incomplete (entirely).");
	}
	if (HASFLAG(dds->meta.mode, DDMM_CUBEMAP)) {
		PD_LOG_WARN("DDS Support for cubemaps is currently incomplete (entirely).");
	}
	if (HASFLAG(dds->meta.mode, DDMM_UNCOMPRESSED)) {
		u32 calcpitch = (dds->header.width * dds->header.ddspf.rgb_bits) >> 3;
		if (HASFLAG(dds->header.flags, DDSD_LINEARSIZE)) {
			PD_LOG_WARN("DDS uncompressed image has flag DDSD_LINEARSIZE");
			if (fix) dds->header.flags &= ~DDSD_LINEARSIZE;
			flag |= DDS_HEADER_ERR_UNCOMPRESSED_LINEARSIZE;
		}
		if (!HASFLAG(dds->header.flags, DDSD_PITCH)) {
			PD_LOG_WARN("DDS uncompressed image missing required flag DDSD_PITCH");
			if (fix) dds->header.flags |= DDSD_PITCH;
			flag |= DDS_HEADER_ERR_FLAG_PITCH;
		}
		if (dds->header.pitch != calcpitch) {
			PD_LOG_WARN("DDS uncompressed image pitch %zu mismatch with calculated %zu", dds->header.pitch, calcpitch);
			if (fix) dds->header.pitch = calcpitch;
			flag |= DDS_HEADER_ERR_PITCH;
		}
		dds->meta.data_size = dds->header.height * dds->header.pitch * depth;
	} else if (HASFLAG(dds->meta.mode, DDMM_COMPRESSED)) {
		u32 calcsize = 0;
		// Specifically this part I think is most wrong, but I have nothing to test with
		// and haven't found (looked for) any detailed, relevant documentation.
		if (HASFLAG(dds->meta.mode, DDMM_PACKED)) {
			calcsize = (4 * (dds->header.width+1)/2) * (4 * (dds->header.height+1)/2);
		} else if (HASFLAG(dds->meta.mode, DDMM_DXT10)) {
			// TODO Linear size is calculated per-format.
			PD_LOG_WARN("DDS Support for DXGI extended formats currently incomplete.");
			calcsize = 0;
		} else {
			calcsize = pdMax(1,(dds->header.width+3)/4)
				*pdMax(1,(dds->header.height+3)/4)*8;
			if (HASFLAG(dds->meta.mode, DDMM_ALPHABLOCK))
				calcsize <<= 1;
		}

		if (HASFLAG(dds->header.flags, DDSD_PITCH)) {
			PD_LOG_WARN("DDS compressed image has flag DDSD_PITCH");
			if (fix) dds->header.flags &= ~DDSD_PITCH;
			flag |= DDS_HEADER_ERR_COMPRESSED_PITCH;
		}
		if (!HASFLAG(dds->header.flags, DDSD_LINEARSIZE)) {
			PD_LOG_WARN("DDS compressed image missing required flag DDSD_LINEARSIZE");
			if (fix) dds->header.flags |= DDSD_LINEARSIZE;
			flag |= DDS_HEADER_ERR_FLAG_LINEARSIZE;
		}
		if (dds->header.linear_size != calcsize) {
			PD_LOG_WARN("DDS compressed image linear size %zu mismatch with calculated %zu", dds->header.linear_size, calcsize);
			if (fix) dds->header.linear_size = calcsize;
			flag |= DDS_HEADER_ERR_LINEARSIZE;
		}
		dds->meta.data_size = dds->header.linear_size;
	}

	// Calculate data2_size
	if (HASFLAG(dds->meta.mode, DDMM_MIPMAP)) {
		// I should think that mipmaps take up an extra 1/3 data_size bytes in the file,
		// but that doesn't seem to be the case.
		pdSz block = 8 + (dds->meta.mode&DDMM_MIPMAP?8:0);
		pdSz sz = dds->meta.data_size >> 2;
		for (pdSz i = 1; i < dds->header.mipmaps; ++i) {
			dds->meta.data2_size += sz;
			sz = pdMax(block, sz >> 2);
		}
	} else if (HASFLAG(dds->meta.mode, DDMM_CUBEMAP | DDMM_VOLUME)) {
		PD_LOG_WARN("DDS Reading extra data from cubemaps/volumetrics is currently unsupported.");
		dds->meta.data2_size = 0;
	} else {
		dds->meta.data2_size = 0;
	}
	return flag;
}
static u32 validateHeader(ddsImageT *dds, int fix) {
	u32 flag = 0;
	if (dds->header.size != DDS_HEADER_SIZE) {
		PD_LOG_WARN("DDS header size set to invalid value %zu, should be %zu", dds->header.size, DDS_HEADER_SIZE);
		if (fix) dds->header.size = DDS_HEADER_SIZE;
		flag |= DDS_HEADER_ERR_SIZE;
	}
	// Check required flags
	if (!HASFLAG(dds->header.flags, DDSD_CAPS)) {
		PD_LOG_WARN("DDS header missing required flag DDSD_CAPS");
		if (fix) dds->header.flags |= DDSD_CAPS;
		flag |= DDS_HEADER_ERR_FLAG_CAPS;
	}
	if (!HASFLAG(dds->header.flags, DDSD_HEIGHT)) {
		PD_LOG_WARN("DDS header missing required flag DDSD_HEIGHT");
		if (fix) dds->header.flags |= DDSD_HEIGHT;
		flag |= DDS_HEADER_ERR_FLAG_HEIGHT;
	}
	if (!HASFLAG(dds->header.flags, DDSD_WIDTH)) {
		PD_LOG_WARN("DDS header missing required flag DDSD_WIDTH");
		if (fix) dds->header.flags |= DDSD_WIDTH;
		flag |= DDS_HEADER_ERR_FLAG_WIDTH;
	}
	if (!HASFLAG(dds->header.flags, DDSD_PIXELFORMAT)) {
		PD_LOG_WARN("DDS header missing required flag DDSD_PIXELFORMAT");
		if (fix) dds->header.flags |= DDSD_PIXELFORMAT;
		flag |= DDS_HEADER_ERR_FLAG_PIXELFORMAT;
	}

	// Get meta information
	if (dds->header.mipmaps > 1 || HASFLAG(dds->header.flags, DDSD_MIPMAPCOUNT) || HASFLAG(dds->header.caps, DDSCAPS_MIPMAP)) {
		dds->meta.mode |= DDMM_MIPMAP;
	}
	if (dds->header.depth > 1 || HASFLAG(dds->header.flags, DDSD_DEPTH) || HASFLAG(dds->header.caps2, DDSCAPS2_VOLUME))
		dds->meta.mode |= DDMM_VOLUME;
	if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP)) {
		dds->meta.mode |= DDMM_CUBEMAP;
		if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP_NEGATIVEX)) dds->meta.cubecount++;
		if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP_NEGATIVEY)) dds->meta.cubecount++;
		if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP_NEGATIVEZ)) dds->meta.cubecount++;
		if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP_POSITIVEX)) dds->meta.cubecount++;
		if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP_POSITIVEY)) dds->meta.cubecount++;
		if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP_POSITIVEZ)) dds->meta.cubecount++;
	}

	// Check mipmaps
	if (HASFLAG(dds->meta.mode, DDMM_MIPMAP)) {
		// If dds->mipmaps, then ensure DDSD_MIPMAPCOUNT and DDSCAPS_MIPMAP set accordingly
		if (dds->header.mipmaps > 1) {
			if (!HASFLAG(dds->header.flags, DDSD_MIPMAPCOUNT)) {
				PD_LOG_WARN("DDS with mipmaps missing flag DDSD_MIPMAPCOUNT");
				if (fix) dds->header.flags |= DDSD_MIPMAPCOUNT;
				flag |= DDS_HEADER_ERR_FLAG_MIPMAPCOUNT;
			}
			if (!HASFLAG(dds->header.caps, DDSCAPS_MIPMAP)) {
				PD_LOG_WARN("DDS with mipmaps missing flag DDSCAPS_MIPMAP");
				if (fix) dds->header.caps |= DDSCAPS_MIPMAP;
				flag |= DDS_HEADER_ERR_CAPS_MIPMAP;
			}
		} else {
			if (HASFLAG(dds->header.flags, DDSD_MIPMAPCOUNT)) {
				PD_LOG_WARN("DDS without mipmaps has flag DDSD_MIPMAPCOUNT");
				if (fix) dds->header.flags &= ~DDSD_MIPMAPCOUNT;
				flag |= DDS_HEADER_ERR_MIPMAPS;
			}
			if (HASFLAG(dds->header.caps, DDSCAPS_MIPMAP)) {
				PD_LOG_WARN("DDS without mipmaps has flag DDSCAPS_MIPMAP");
				if (fix) dds->header.caps &= ~DDSCAPS_MIPMAP;
				flag |= DDS_HEADER_ERR_MIPMAPS;
			}
		}
	}
	// Check depth
	if (HASFLAG(dds->meta.mode, DDMM_VOLUME)) {
		if (dds->header.depth > 1) {
			if (!HASFLAG(dds->header.flags, DDSD_DEPTH)) {
				PD_LOG_WARN("DDS volume texture missing flag DDSD_DEPTH");
				if (fix) dds->header.flags |= DDSD_DEPTH;
				flag |= DDS_HEADER_ERR_FLAG_DEPTH;
			}
			if (!HASFLAG(dds->header.caps2, DDSCAPS2_VOLUME)) {
				PD_LOG_WARN("DDS volume texture missing flag DDSCAPS2_VOLUME");
				if (fix) dds->header.caps2 |= DDSCAPS2_VOLUME;
				flag |= DDS_HEADER_ERR_CAPS2_VOLUME;
			}
		} else {
			if (HASFLAG(dds->header.flags, DDSD_DEPTH)) {
				PD_LOG_WARN("DDS without depth has flag DDSD_DEPTH");
				if (fix) dds->header.flags &= ~DDSD_DEPTH;
				flag |= DDS_HEADER_ERR_DEPTH;
			}
			if (HASFLAG(dds->header.caps2, DDSCAPS2_VOLUME)) {
				PD_LOG_WARN("DDS without depth has flag DDSCAPS2_VOLUME");
				if (fix) dds->header.caps2 &= ~DDSCAPS2_VOLUME;
				flag |= DDS_HEADER_ERR_DEPTH;
			}
		}
	}
	// Check caps
	if (!HASFLAG(dds->header.caps, DDSCAPS_TEXTURE)) {
		PD_LOG_WARN("DDS caps missing required flag DDSCAPS_TEXTURE");
		if (fix) dds->header.caps |= DDSCAPS_TEXTURE;
		flag |= DDS_HEADER_ERR_CAPS_TEXTURE;
	}
	if (HASFLAG(dds->meta.mode, DDMM_COMPLEX) && !HASFLAG(dds->header.caps, DDSCAPS_COMPLEX)) {
		PD_LOG_WARN("DDS with multiple surfaces missing flag DDSCAPS_COMPLEX");
		if (fix) dds->header.caps |= DDSCAPS_COMPLEX;
		flag |= DDS_HEADER_ERR_CAPS_COMPLEX;
	} else if (!HASFLAG(dds->meta.mode, DDMM_COMPLEX) && HASFLAG(dds->header.caps, DDSCAPS_COMPLEX)) {
		PD_LOG_WARN("DDS without multiple surfaces has flag DDSCAPS_COMPLEX");
		if (fix) dds->header.caps &= ~DDSCAPS_COMPLEX;
		flag |= DDS_HEADER_ERR_CAPS_COMPLEX;
	}
	if (!HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP) && dds->meta.cubecount > 0) {
		PD_LOG_WARN("DDS with cubemaps missing flag DDSCAPS2_CUBEMAP");
		if (fix) dds->header.caps2 |= DDSCAPS2_CUBEMAP;
		flag |= DDS_HEADER_ERR_CAPS2_CUBEMAP;
	} else if (HASFLAG(dds->header.caps2, DDSCAPS2_CUBEMAP) && dds->meta.cubecount == 0) {
		PD_LOG_WARN("DDS without cubemaps has flag DDSCAPS2_CUBEMAP");
		if (fix) dds->header.caps2 &= ~DDSCAPS2_CUBEMAP;
		flag |= DDS_HEADER_ERR_CUBECOUNT;
	}

	if (HASFLAG(dds->header.ddspf.flags, DDPF_FOURCC)) {
		switch (dds->header.ddspf.fourcc.id) {
			case DXT1_MAGIC:dds->meta.mode |= DDMM_DXT1; break;
			case DXT2_MAGIC:
			case DXT3_MAGIC:dds->meta.mode |= DDMM_DXT3; break;
			case DXT4_MAGIC:
			case DXT5_MAGIC:dds->meta.mode |= DDMM_DXT5; break;
			case DXT10_MAGIC:dds->meta.mode |= DDMM_DXT10; break;
			default: {
				dds->meta.mode |= DDMM_UNKNOWN;
				PD_LOG_WARN("Unrecognized pixelformat FourCC %4.4s 0x%08x",
					dds->header.ddspf.fourcc.fourcc, dds->header.ddspf.fourcc.id);
				break;
			}
		}
	} else {
		dds->meta.mode |= DDMM_UNCOMPRESSED;
	}

	// check extended header
	if (HASFLAG(dds->meta.mode, DDMM_DXT10)) {
		switch (dds->header10.format) {
			case DXGI_FORMAT_R8G8_B8G8_UNORM:
			case DXGI_FORMAT_G8R8_G8B8_UNORM:
			case DXGI_FORMAT_YUY2:dds->meta.mode |= DDMM_PACKED; break;
			default:break;
		}
	}
	flag |= calcSizes(dds, fix);

	return flag;
}

pdErrT
ddsReadImage(ddsImageT *img, pdFileT *const file)
{
	pdErrT err = ERR_DDS_NONE;

	if (!img || !file) {
		return ERR_DDS_NONE;
	} else if (!file->fp) {
		PD_LOG_ERROR("Tried to read DDS from uninitialized file %s", SAFESTR(file->path));
		return ERR_INVALID_ARGUMENT;
	}
	// Reset img
	*img = (ddsImageT){0};
	// Find next DDS
	if ((err = pdSearchFile(file, DDS_FOURCC, 4, 0)) != ERR_PATH_NONE) {
		if (err & ERR_PATH_END) {
			return ERR_DDS_MAGIC;
		} else {
			PD_LOG_ERROR("Failed searching for DDS magic in file %s : %s", SAFESTR(file->path), strerror(errno));
			return ERR_DDS_FILE | err;
		}
	}
	// Read DDS magic
	if ((err = pdRead(file, 4, &img->magic, NULL)) != ERR_PATH_NONE) {
		PD_LOG_ERROR("Failed reading DDS magic from %s : %s", strerror(errno));
		return ERR_DDS_FILE | err;
	}
	// Read primary header
	if ((err = pdRead(file, DDS_HEADER_SIZE, &img->header, NULL)) != ERR_PATH_NONE) {
		return ERR_DDS_HEADER | err;
	}
	// Read secondary header
	if (HASFLAG(img->header.ddspf.flags, DDPF_FOURCC) && img->header.ddspf.fourcc.id == DXT10_MAGIC) {
		if ((err = pdRead(file, DDS_HEADERDXT10_SIZE, &img->header10, NULL)) != ERR_PATH_NONE) {
			return ERR_DDS_HEADER10 | err;
		}
	}

	validateHeader(img, 1);
	// Read primary data
	if (img->meta.data_size) {
		img->data = pdAlloc(img->data, img->meta.data_size, 1);
		if ((err = pdRead(file, img->meta.data_size, img->data, NULL)) != ERR_PATH_NONE) {
			img->data = pdAlloc(img->data, 0, 0);
			return ERR_DDS_DATA | err;
		}
	}
	// Read secondary data
	// TODO
	if (img->meta.data2_size) {
		img->data2 = pdAlloc(img->data2, img->meta.data2_size, 1);
		if ((err = pdRead(file, img->meta.data2_size, img->data2, NULL)) != ERR_PATH_NONE) {
			img->data2 = pdAlloc(img->data2, 0, 0);
			return ERR_DDS_DATA2 | err;
		}
	}

	return err;
}

pdErrT
ddsSaveImage(ddsImageT *img, const char *const path)
{
	pdErrT err = ERR_DDS_NONE;
	pdFileT file = {0};
	if (!img || !path)
		return ERR_DDS_NONE;

	if ((err = pdOpen(&file, path, PDFL_MODE_WRITE)) != ERR_PATH_NONE) {
		PD_LOG_ERROR("DDS Failed opening file for output %s : %s", SAFESTR(path), strerror(errno));
		return ERR_DDS_FILE | err;
	}

	// Write magic
	if ((err = pdWrite(&file, 4, img->magic.fourcc, NULL)) != ERR_PATH_NONE) {
		pdClose(&file);
		PD_LOG_ERROR("DDS Failed writing magic to %s : %s", SAFESTR(path), strerror(errno));
		return ERR_DDS_MAGIC | err;
	}
	// Write primary header
	if ((err = pdWrite(&file, img->header.size, &img->header, NULL)) != ERR_PATH_NONE) {
		pdClose(&file);
		PD_LOG_ERROR("DDS Failed writing primary header to %s : %s", SAFESTR(path), strerror(errno));
		return ERR_DDS_HEADER | err;
	}
	// Write secondary header
	if (HASFLAG(img->meta.mode, DDMM_DXT10)) {
		if ((err = pdWrite(&file, DDS_HEADERDXT10_SIZE, &img->header10, NULL)) != ERR_PATH_NONE) {
			pdClose(&file);
			PD_LOG_ERROR("DDS Failed writing secondary header to %s : %s", SAFESTR(path), strerror(errno));
			return ERR_DDS_HEADER10 | err;
		}
	}
	// Write primary data
	if (img->meta.data_size) {
		if ((err = pdWrite(&file, img->meta.data_size, img->data, NULL)) != ERR_PATH_NONE) {
			pdClose(&file);
			PD_LOG_ERROR("DDS Failed writing primary data to %s : %s", SAFESTR(path), strerror(errno));
			return ERR_DDS_DATA | err;
		}
	}
	// Write secondary data
	// TODO
	if (img->meta.data2_size) {
		if ((err = pdWrite(&file, img->meta.data2_size, img->data2, NULL)) != ERR_PATH_NONE) {
			pdClose(&file);
			PD_LOG_ERROR("DDS Failed writing secondary data to %s : %s", SAFESTR(path), strerror(errno));
			return ERR_DDS_DATA2 | err;
		}
	}

	pdClose(&file);
	return err;
}

static const ddsImageT empty_image = {0};
static const ddsImageT default_image = {.magic.id=DDS_MAGIC};
pdErrT
ddsFreeImage(ddsImageT *img)
{
	if (img) {
		pdAlloc(img->data, 0, 0);
		pdAlloc(img->data2, 0, 0);
		*img = empty_image;
	}
	return ERR_DDS_NONE;
}
