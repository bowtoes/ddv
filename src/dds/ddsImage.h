#ifndef DDSIMAGE_H
#define DDSIMAGE_H

#include "common/pdFile.h"
#include "dds/dxt10.h"
#include "dds/dds.h"

typedef enum ddsHeaderErrT {
	DDS_HEADER_ERR_NONE                    = 0x00000000, // No header errors.
	DDS_HEADER_ERR_SIZE                    = 0x00000001, // Header has size set incorrectly.
	DDS_HEADER_ERR_FLAG_CAPS               = 0x00000002, // Header missing DDSD_CAPS flag.
	DDS_HEADER_ERR_FLAG_HEIGHT             = 0x00000004, // Header missing DDSD_HEIGHT flag.
	DDS_HEADER_ERR_FLAG_WIDTH              = 0x00000008, // Header missing DDSD_WIDTH flag.
	DDS_HEADER_ERR_FLAG_PIXELFORMAT        = 0x00000010, // Header missing DDSD_PIXELFORMAT flag.
	DDS_HEADER_ERR_FLAG_MIPMAPCOUNT        = 0x00000020, // Header missing DDSD_MIPMAPCOUNT flag in a mipmapped file.
	DDS_HEADER_ERR_MIPMAPS                 = 0x00000040, // Header mipmaps value set incorrectly relative to DDSD_MIPMAPCOUNT flag.
	DDS_HEADER_ERR_FLAG_DEPTH              = 0x00000080, // Header missing DDSD_DEPTH flag in a depth texture.
	DDS_HEADER_ERR_DEPTH                   = 0x00000100, // Header depth value set incorrectly relative to DDSD_DEPTH flag.
	DDS_HEADER_ERR_CAPS_TEXTURE            = 0x00000200, // Header caps missing DDSCAPS_TEXTURE flag.
	DDS_HEADER_ERR_CAPS_COMPLEX            = 0x00000400, // Header caps missing DDSCAPS_COMPLEX flag when it's required.
	DDS_HEADER_ERR_CAPS_MIPMAP             = 0x00000800, // Header caps missing DDSCAPS_MIPMAP flag in a mipmap file.
	DDS_HEADER_ERR_UNCOMPRESSED_LINEARSIZE = 0x00001000, // Header has DDSD_LINEARSIZE flag set in an uncompressed texture.
	DDS_HEADER_ERR_FLAG_PITCH              = 0x00002000, // Header missing DDSD_PITCH flag in an uncompressed texture.
	DDS_HEADER_ERR_PITCH                   = 0x00004000, // Header pitch value different from what is calculated to be the correct value.
	DDS_HEADER_ERR_COMPRESSED_PITCH        = 0x00008000, // Header has DDSD_PITCH flag set in a compressed texture.
	DDS_HEADER_ERR_FLAG_LINEARSIZE         = 0x00010000, // Header missing DDSD_LINEARSIZE flag in a compressed texture.
	DDS_HEADER_ERR_LINEARSIZE              = 0x00020000, // Header linear_size value different from what is calculated to be the correct value.
	DDS_HEADER_ERR_CAPS2_VOLUME            = 0x00040000, // Header caps2 missing DDSCAPS2_VOLUME when header has flag DEPTH.
	DDS_HEADER_ERR_CAPS2_CUBEMAP           = 0x00080000, // Header caps2 missing DDSCAPS2_CUBEMAP when header has any cubemap direction flags.
	DDS_HEADER_ERR_CUBECOUNT               = 0x00100000, // Header caps2 has flag DDSCAPS2_CUBEMAP but is missing all cubemap direction flags.
	DDS_HEADER_ERR                         = 0x001FFFFF,
} ddsHeaderErrT;

typedef enum ddsMetaModeT {
	DDMM_DXT1    = 0x00000001, // Basic block compression; chunks of 4x4 pixels are each stored into a 4x4 table of 2 bits per pixel, representing interpolation between two extreme colors of the chunk.
	DDMM_BC1     = 0x00000001, // Synonym for DXT1; indicates a specific compression algorithm instead of just data layout.

	DDMM_DXT2    = 0x00000002, // Similar to DXT1, with a preceding 4x4 table of 4-bit values representing straight alpha of each pixel. Alphas assumed to be premultiplied.
	DDMM_BC2     = 0x00000002, // Synonym for DXT2; indicates a specific compression algorithm instead of just data layout.

	DDMM_DXT3    = 0x00000002, // Same as DXT2, except alphas are not assumed to be premultiplied.
	DDMM_BC3     = 0x00000002, // Synonym for DXT3; indicates a specific compression algorithm instead of just data layout.

	DDMM_DXT4    = 0x00000004, // Similar to DXT2 compression; 4-bit alpha values represent alpha interpolation; alphas assumed to be premultiplied.
	DDMM_BC4     = 0x00000004, // Synonym for DXT4; indicates a specific compression algorithm instead of just data layout.

	DDMM_DXT5    = 0x00000004, // Same as DXT4, except alphas are not assumed to be premultiplied.
	DDMM_BC5     = 0x00000004, // Synonym for DXT5; indicates a specific compression algorithm instead of just data layout.

	DDMM_DXT10   = 0x00000008, // DirectX 10 extended format; indicates the presence of a DXT10 header following main header. Format information stored there.

	DDMM_PACKED  = 0x00000010, // R8G8_B8G8, G8R8_G8B8, YUY2, UYVY. Unique pitch calculation.

	DDMM_MIPMAP  = 0x01000000, // DDS contains mipmaps.
	DDMM_CUBEMAP = 0x02000000, // DDS is a cubemap.
	DDMM_VOLUME  = 0x04000000, // DDS is volumetric.
	DDMM_COMPLEX = 0x07000000, // DDS is/has any of above three.

	DDMM_UNKNOWN = 0x10000000, // Unknown type, test for equality.
	DDMM_UNCOMPRESSED = 0x20000000, // Uncompressed type.

	DDMM_ALPHABLOCK = DDMM_BC2 | DDMM_BC5, // Modes that have an alpha block.
	DDMM_COMPRESSED = DDMM_BC1 | DDMM_BC2 | DDMM_BC4, // Compressed modes.
} ddsMetaModeT;

typedef struct ddsImageMetaT {
	ddsMetaModeT mode;
	pdSz data_size;
	pdSz data2_size;
	pdCt cubecount;
} ddsImageMetaT;
typedef struct ddsImageT {
	pdFccT magic;
	ddsHeaderT header;
	ddsHeaderDXT10T header10;
	u32 _padding; // Structure padding; irrelevant to DDS.
	u8 *data; // Main texture data.
	u8 *data2; // Mipmaps, cubemaps, volume depths.
	ddsImageMetaT meta;
} ddsImageT;

// Read dds image data from given file.
pdErrT ddsReadImage(ddsImageT *img, pdFileT *const file);
// Save dds image data to a given path.
pdErrT ddsSaveImage(ddsImageT *img, const char *const path);

pdErrT ddsFreeImage(ddsImageT *img);

#endif /* DDSIMAGE_H */
