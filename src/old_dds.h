#ifndef OLD_DDS_H
#define OLD_DDS_H

#include <brrtools/brrtypes.h>
#include <brrtools/brrdebug.h>

typedef union fcc_t {
	char fourcc[4];
	brru4 id;
} fcc_t;

typedef enum ddxPixelFormatFlagsT {
	DDPF_ALPHAPIXELS = 0x00000001, // Texture contains alpha data, a_mask contains valid data.
	DDPF_ALPHA       = 0x00000002, // Used in older DDS files, alpha channel only with uncompressed data; a_mask contains valid data.
	DDPF_FOURCC      = 0x00000004, // Texture contains compressed RGB data; fcc contains valid data.
	DDPF_RGB         = 0x00000040, // Texture contains uncompressed RGB data; rgb_bits and bitmask contain valid data.
	DDPF_YUV         = 0x00000200, // Used in oder DDS files for uncompressed YUV data; rgb_bits and bitmask contain valid data, analogous to YUV colorspace.
	DDPF_LUMINANCE   = 0x00020000, // Used in older DDS files for single-color uncompressed data; rgb_bits and r_mask contain valid data.
} ddxPixelFormatFlagsT;
typedef struct ddsPixelFormatT {
	brru4 size;               // Size of structure; is 32.
	brru4 flags;              // Pixel format flags speficying type of data stored in texture.
	fcc_t fourcc;             // FourCC indicating compressed texture format.
	union {
		brru4 rgb_bits;       // RGB(A) image bit depth
		brru4 luminance_bits; // RGB image bit depth (and it's called luminance?)
		brru4 yuv_bits;       // YUV image bit depth
	};
	union {
		brru4 r_mask;         // Red bit mask.
		brru4 luminance_mask; // Luminance bit mask.
		brru4 y_mask;         // Y bit mask.
	};
	union {
		brru4 g_mask;         // Green/U bit mask.
		brru4 u_mask;         // U bit mask.
	};
	union {
		brru4 b_mask;         // Blue/V bit mask.
		brru4 v_mask;         // V bit mask.
	};
	brru4 a_mask;             // Alpha bit mask.
} ddsPixelFormatT;
#define DDS_PIXELFORMAT_SIZE 32

typedef enum ddsHeaderFlagsT {
	DDSD_CAPS        = 0x00000001, // Required; caps contain valid data.
	DDSD_HEIGHT      = 0x00000002, // Required; height contains valid data
	DDSD_WIDTH       = 0x00000004, // Required; width contains valid data.
	DDSD_PITCH       = 0x00000008, // If file is uncompressed, required; pitch contains valid data.
	DDSD_PIXELFORMAT = 0x00001000, // Required; indicates ddspf contains valid data.
	DDSD_MIPMAPCOUNT = 0x00020000, // Indicates an image contains mipmaps; mipmaps stores count.
	DDSD_LINEARSIZE  = 0x00080000, // If file is compressed, required; linear_size contains compressed linear size.
	DDSD_DEPTH       = 0x00800000, // Texture is a depth texture and depth contains valid data.
} ddsHeaderFlagsT;
typedef enum ddsCapsT {
	DDSCAPS_COMPLEX = 0x00000008, // Indicates file contains multiple surfaces (mipmaps, cubemap, ...), required if so.
	DDSCAPS_MIPMAP  = 0x00400000, // Should be used for a texture that is a mipmap.
	DDSCAPS_TEXTURE = 0x00001000, // Required; file is a texture (duh).
} ddsCapsT;
typedef enum ddsCaps2T {
	DDSCAPS2_CUBEMAP           = 0x00000200, // Required for a cubemap.
	DDSCAPS2_CUBEMAP_POSITIVEX = 0x00000400, // Required when +X surfaces are stored in a cubemap.
	DDSCAPS2_CUBEMAP_NEGATIVEX = 0x00000800, // Required when -X surfaces are stored in a cubemap.
	DDSCAPS2_CUBEMAP_POSITIVEY = 0x00001000, // Required when +Y surfaces are stored in a cubemap.
	DDSCAPS2_CUBEMAP_NEGATIVEY = 0x00002000, // Required when -Y surfaces are stored in a cubemap.
	DDSCAPS2_CUBEMAP_POSITIVEZ = 0x00004000, // Required when +Z surfaces are stored in a cubemap.
	DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x00008000, // Required when -Z surfaces are stored in a cubemap.
	DDSCAPS2_VOLUME            = 0x00200000, // Required for volume texture.
} ddsCaps2T;
typedef struct ddsHeaderT {
	brru4 size;            // Size of structure; is 124.
	brru4 flags;           // Texture format bit-flags.
	brru4 height;          // Texture height in pixels.
	brru4 width;           // Texture width in pixels.
	union {
		brru4 pitch;       // The pitch/stride, or number of bytes per-scanline; how many bytes to the first byte of the next scanline.
		brru4 linear_size; // Number of bytes for top level texture of a compressed image.
	};
	brru4 depth;           // Depth of texture if has volume, otherwise unused.
	brru4 mipmaps;         // Number of mimaps in texture.
	brru4 reserved1[11];   // Unused.
	ddsPixelFormatT ddspf; // Texture pixelformat.
	brru4 caps;            // Texture complexity; if has more than one 'surface'.
	brru4 caps2;           // Additional surfaces detail.
	brru4 caps3;           // Unused.
	brru4 caps4;           // Unused.
	brru4 reserved2;       // Unused.
} ddsHeaderT;
#define DDS_HEADER_SIZE 124

#define DDS_MAGIC  MAGIC('D','D','S',' ')
#define DDS_FOURCC FOURCC('D','D','S',' ')

#endif /* OLD_DDS_H */
