#include "dds/dxt2.h"

brru1
dxt2_alpha_get(const dxt2_alpha_bitmap_t *const abm, brru1 x, brru1 y)
{
	if (!abm)
		return 0;
	return abm->rows[y & 3].row & (15 << ((x & 3) * 4));
}

void
dxt2_alpha_set(dxt2_alpha_bitmap_t *const abm, brru1 x, brru1 y, brru1 v)
{
	if (!abm)
		return;
	x = 4 * (x & 3);
	y = y & 3;
	abm->rows[y].row = (abm->rows[y].row & ~(15 << x)) | ((v & 15) << x);
}

void
dxt2_block_recalculate(dxt2_block_t *const block)
{
	if (!block)
		return;
	block->_color2 = dxt1_interpolate_noalpha(block->color0, block->color1, 2);
	block->_color3 = dxt1_interpolate_noalpha(block->color0, block->color1, 3);
}

col_dxt2_t
dxt2_block_get(const dxt2_block_t *const block, brru1 x, brru1 y)
{
	return (col_dxt2_t){
		.dxt1 = dxt1_block_get(&block->color_block, x, y),
		.a = dxt2_alpha_get(&block->alpha_bitmap, x, y)
	};
}
