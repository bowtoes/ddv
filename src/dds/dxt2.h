#ifndef DDS_DXT2_H
#define DDS_DXT2_H

#include <brrtools/brrtypes.h>

#include "dds/util.h"
#include "dds/dxt1.h"

// TODO docs
typedef union dxt2_row {
	brru2 row;        // TODO docs
	struct {
		brru1 col0:4; // TODO docs
		brru1 col1:4; // TODO docs
		brru1 col2:4; // TODO docs
		brru1 col3:4; // TODO docs
	};
} dxt2_row_t;

// TODO docs
typedef union dxt2_alpha_bitmap {
	brru8 table;         // TODO docs
	brru2 _rows[4];      // TODO docs
	dxt2_row_t rows[4];  // TODO docs
	struct {
		dxt2_row_t row0; // TODO docs
		dxt2_row_t row1; // TODO docs
		dxt2_row_t row2; // TODO docs
		dxt2_row_t row3; // TODO docs
	};
} dxt2_alpha_bitmap_t;

// TODO docs
typedef struct dxt2_block {
	dxt2_alpha_bitmap_t alpha_bitmap; // TODO docs
	union {
		dxt1_block_t         color_block; // The underlying color data, stored as a dxt1 color block.
		struct {
			col_dxt1_t color0;
			col_dxt1_t color1;
			dxt1_bitmap_t bitmap;

			col_dxt1_t _color2;
			col_dxt1_t _color3;
		};
	};
} dxt2_block_t;
// DXT2 blocks are exactly 16 bytes
#define DXT2_BLOCK_SIZE 16

extern const brru4 dxt2_magic;
extern const fcc_t dxt2_fcc;
extern const brru4 dxt3_magic;
extern const fcc_t dxt3_fcc;

/* Returns the 4-bit value stored in the compressed alpha-bitmap 'abm' at index (x:2,y:2) */
brru1
dxt2_alpha_get(const dxt2_alpha_bitmap_t *const abm, brru1 x, brru1 y);

/* Sets the index (x:2,y:2) in the compressed alpha-bitmap 'abm' to the 4-bit value 'v' */
void
dxt2_alpha_set(dxt2_alpha_bitmap_t *const abm, brru1 x, brru1 y, brru1 v);

void
dxt2_block_recalculate(dxt2_block_t *const block);

col_dxt2_t
dxt2_block_get(const dxt2_block_t *const block, brru1 x, brru1 y);

#endif /* DDS_DXT2_H */
