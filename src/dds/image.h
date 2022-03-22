#ifndef DDS_IMAGE_H
#define DDS_IMAGE_H

#include <brrtools/brrtypes.h>

#include "dds/dds.h"
#include "dds/dxt10.h"

// TODO docs
typedef enum dds_image_mode {
	DDMM_BC1     = 0x00000001, // Colors are compressed into a 4x4 table of 2-bit pixel indexes into an interpolated color look-up table.
	DDMM_DXT1    = 0x00000001, // Synonym for BC1.

	DDMM_BC2     = 0x00000002, // BC1 compressed colors, with a preceding 4x4 table of 4-bit pixel alphas.
	DDMM_DXT2    = 0x00000002, // Synonym for BC2, with premultiplied alphas.
	DDMM_DXT3    = 0x00000002, // Synonym for BC2, with straight alphas.

	DDMM_BC3     = 0x00000004, // BC1 compressed colors, with a preceding 4x4 table of 3-bit pixel-indexes into an interpolated table of alphas.
	DDMM_DXT4    = 0x00000004, // Synonym for BC3, with premultiplied alphas.
	DDMM_DXT5    = 0x00000004, // Synonym for BC3, with straight alphas.

	DDMM_DXT10   = 0x00000008, // DirectX 10 extended format; indicates the presence of a DXT10 header following main header.

	DDMM_PACKED  = 0x00000010, // R8G8_B8G8, G8R8_G8B8, YUY2, UYVY. Unique pitch calculation.

	DDMM_MIPMAP  = 0x01000000, // DDS contains mipmaps.
	DDMM_CUBEMAP = 0x02000000, // DDS is a cubemap.
	DDMM_VOLUME  = 0x04000000, // DDS is volumetric.
	DDMM_COMPLEX = 0x07000000, // DDS is/has any of above three.

	DDMM_UNKNOWN      = 0x10000000, // Unknown type, test for equality. (?)
	DDMM_UNCOMPRESSED = 0x20000000, // Uncompressed type.

	DDMM_ALPHABLOCK = DDMM_BC2,            // Modes that have an alpha block.
	DDMM_COMPRESSED = DDMM_BC1 | DDMM_BC2 | DDMM_BC3, // Compressed modes.
} dds_image_mode_t;

// TODO docs
typedef struct dds_image_meta {
	dds_image_mode_t mode; // TODO docs
	brrsz principle_size;  // TODO docs
	brrsz ancillary_size;  // TODO docs
	brru2 cube_faces;      // TODO docs
} dds_image_meta_t;

// TODO docs
typedef struct dds_image {
	fcc_t fourcc;                // The four magic bytes indicating this is a dds file; 'D', 'D', 'S', ' '
	dds_header_t header;         // The main DDS header.
	dds_header_dxt10_t header10; // DirectX 10 extended DDS header; present only when pixelformat 'fourcc' is 'DX10'
	brru4 _padding; // irrelevant to dds, just noted for when reading/writing disk.
	brru1 *principle;            // Principle image data.
	brru1 *ancillary;            // Ancillary image data (mipmaps, cubemaps, volume depths).

	dds_image_meta_t _meta;
} dds_image_t;

void
dds_image_free(dds_image_t *const image);

/* Copies values from 'data' into local memory
 * It is safe to free 'data' after parsing into an image.
 * */
int
dds_image_parse(dds_image_t *const image, const char *const data, brrsz data_len);

void
dds_image_log_headers(const dds_image_t *const image);

#endif /* DDS_IMAGE_H */
