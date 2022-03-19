#ifndef DDS_H
#define DDS_H

#include "common/pdTypes.h"
#include "common/pdDebug.h"
#include "common/pdUtil.h"

typedef enum ddxPixelFormatFlagsT {
	DDPF_ALPHAPIXELS = 0x00000001, // Texture contains alpha data, a_mask contains valid data.
	DDPF_ALPHA       = 0x00000002, // Used in older DDS files, alpha channel only with uncompressed data; a_mask contains valid data.
	DDPF_FOURCC      = 0x00000004, // Texture contains compressed RGB data; fcc contains valid data.
	DDPF_RGB         = 0x00000040, // Texture contains uncompressed RGB data; rgb_bits and bitmask contain valid data.
	DDPF_YUV         = 0x00000200, // Used in oder DDS files for uncompressed YUV data; rgb_bits and bitmask contain valid data, analogous to YUV colorspace.
	DDPF_LUMINANCE   = 0x00020000, // Used in older DDS files for single-color uncompressed data; rgb_bits and r_mask contain valid data.
} ddxPixelFormatFlagsT;
typedef struct ddsPixelFormatT {
	u32 size;     // Size of structure; is 32.
	u32 flags;    // Pixel format flags speficying type of data stored in texture.
	pdFccT fourcc;     // FourCC indicating compressed texture format.
	union {
		u32 rgb_bits; // Bit depth of an RGB(A) image
		u32 luminance_bits; // Bit depth of an RGB image
		u32 yuv_bits; // Bit depth of an YUV image
	};
	union {
		u32 r_mask;   // Red bit mask.
		u32 luminance_mask;   // Luminance bit mask.
		u32 y_mask;   // Y bit mask.
	};
	union {
		u32 g_mask;   // Green/U bit mask.
		u32 u_mask;   // U bit mask.
	};
	union {
		u32 b_mask;   // Blue/V bit mask.
		u32 v_mask;   // V bit mask.
	};
	u32 a_mask;   // Alpha bit mask.
} ddsPixelFormatT;
#define DDS_PIXELFORMAT_SIZE 32
PD_STATIC_ASSERT(sizeof(ddsPixelFormatT) == DDS_PIXELFORMAT_SIZE, "");

typedef enum ddsHeaderFlagsT {
	DDSD_CAPS        = 0x00000001, // Required; caps contain valid data.
	DDSD_HEIGHT      = 0x00000002, // Required; height contains valid data
	DDSD_WIDTH       = 0x00000004, // Required; width contains valid data.
	DDSD_PITCH       = 0x00000008, // If file is uncompressed, required; pitch contains valid data.
	DDSD_PIXELFORMAT = 0x00001000, // Required; ddspf contains valid data.
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
	u32 size;              // Size of structure; is 124.
	u32 flags;             // Texture format bit-flags.
	u32 height;            // Texture height in pixels.
	u32 width;             // Texture width in pixels.
	union {
		u32 pitch;         // The pitch/stride, or number of bytes per-scanline;
		                   // how many bytes to the first byte of the next scanline.
		u32 linear_size;   // Number of bytes for top level texture of a compressed image.
	};
	u32 depth;             // Depth of texture if has volume, otherwise unused.
	u32 mipmaps;           // Number of mimaps in texture.
	u32 reserved1[11];     // Unused.
	ddsPixelFormatT ddspf; // Texture pixelformat.
	u32 caps;              // Texture complexity; if has more than one 'surface'.
	u32 caps2;             // Additional surfaces detail.
	u32 caps3;             // Unused.
	u32 caps4;             // Unused.
	u32 reserved2;         // Unused.
} ddsHeaderT;
#define DDS_HEADER_SIZE 124
PD_STATIC_ASSERT(sizeof(ddsHeaderT) == DDS_HEADER_SIZE, "");

#define DDS_MAGIC  MAGIC('D','D','S',' ')
#define DDS_FOURCC FOURCC('D','D','S',' ')

#endif /* DDS_H */
