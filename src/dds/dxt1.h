#ifndef DDS_DXT1_H
#define DDS_DXT1_H

#include <brrtools/brrtypes.h>

#include "dds/util.h"

extern const brru4 dxt1_magic;
extern const fcc_t dxt1_fcc;

// TODO docs
typedef union dxt1_row {
	brru1 row;        // TODO docs
	struct {
		brru1 col0:2; // TODO docs
		brru1 col1:2; // TODO docs
		brru1 col2:2; // TODO docs
		brru1 col3:2; // TODO docs
	};
} dxt1_row_t;

// Each 2-bit value in the table represents an interpolated value of the two colors
// in a dxt1 block, one of four options:
//   00 = color_0 (minimum color)
//   01 = color_1 (maximum color)
//   10 = 2/3 * color_0 + 1/3 * color_1
//   11 = 1/3 * color_0 + 2/3 * color_1
// If the block has a 1-bit alpha channel, then options '10' and '11' instead
// correspond to:
//   10 = (color_0 + color_1) / 2
//   11 = transparent
// Whether a block has an alpha channel is determined by the order of 'color_0'
// and 'color_1', with 'color_0 > color_1' indicating normal r5g6b5 color.
typedef union dxt1_bitmap {
	brru4 table;         // TODO docs
	brru1 _rows[4];      // TODO docs
	dxt1_row_t rows[4];  // TODO docs
	struct {
		dxt1_row_t row0; // TODO docs
		dxt1_row_t row1; // TODO docs
		dxt1_row_t row2; // TODO docs
		dxt1_row_t row3; // TODO docs
	};
} dxt1_bitmap_t;

// TODO docs
typedef struct dxt1_block {
	col_dxt1_t color0;    // TODO docs
	col_dxt1_t color1;    // TODO docs
	dxt1_bitmap_t bitmap; // TODO docs

	col_dxt1_t _color2;   // A calculated value, interpolated between color0 and color1; this is not saved to disk.
	col_dxt1_t _color3;   // A calculated value, interpolated between color0 and color1 (or 0); this is not saved to disk.
} dxt1_block_t;
// DXT1 blocks are exactly 8 bytes
#define DXT1_BLOCK_SIZE 8

/* Return the 2-bit value stored in the compressed color-bitmap 'bm' at index (x:2,y:2). */
brru1
dxt1_bitmap_get(const dxt1_bitmap_t *const bm, brru1 x, brru1 y);

/* Set the index (x:2,y:2) in the compressed color-bitmap 'bm' to the 2-bit value 'v'. */
void
dxt1_bitmap_set(dxt1_bitmap_t *const bm, brru1 x, brru1 y, brru1 v);

/* Get the color value represented by the table index (x:2,y:2) in the bitmap. */
col_dxt1_t
dxt1_block_get(const dxt1_block_t *const block, brru1 x, brru1 y);
col_rgba_t
dxt1_block_get_rgba(const dxt1_block_t *const block, brru1 x, brru1 y);

/* Interpolate between two dxt1 colors. */
col_dxt1_t
dxt1_interpolate(col_dxt1_t a, col_dxt1_t b, brru1 t);
/* Interpolate between two dxt1 colors, without regard for the order of the colors. */
col_dxt1_t
dxt1_interpolate_noalpha(col_dxt1_t a, col_dxt1_t b, brru1 t);

void
dxt1_block_recalculate(dxt1_block_t *const block);

#endif /* DDS_DXT1_H */
