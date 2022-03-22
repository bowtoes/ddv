#include "dds/dxt1.h"

brru1
dxt1_bitmap_get(const dxt1_bitmap_t *const bm, brru1 x, brru1 y)
{
	if (!bm)
		return 0;
	return bm->rows[y & 3].row & (3 << ((x & 3) * 2));
}

void
dxt1_bitmap_set(dxt1_bitmap_t *const bm, brru1 x, brru1 y, brru1 v)
{
	if (!bm)
		return;
	x = 2 * (x & 3);
	y = y & 3;
	bm->rows[y].row = (bm->rows[y].row & ~(3 << x)) | ((v & 3) << x);
}

col_dxt1_t
dxt1_block_get(const dxt1_block_t *const block, brru1 x, brru1 y)
{
	if (!block)
		return (col_dxt1_t){.s=0};
	brru1 b = dxt1_bitmap_get(&block->bitmap, x, y);
	if (b == 0) {
		return block->color0;
	} else if (b == 1) {
		return block->color1;
	} else if (b == 2) {
		return block->_color2;
	} else {/*(b == 3)*/
		return block->_color3;
	}
}

col_dxt1_t
dxt1_interpolate(col_dxt1_t a, col_dxt1_t b, brru1 t)
{
	if (t == 0)
		return a;
	if (t == 1)
		return b;
	if (t == 2) {
		if (a.s > b.s) {
			brru4 s = 2 * a.s + b.s + 1;
			return (col_dxt1_t){.s=(brru2)(s/3)};
		} else {
			brru4 s = (a.s+b.s);
			return (col_dxt1_t){.s=(brru2)(s/2)};
		}
	}
	if (a.s > b.s) {
		brru4 s = a.s + 2 * b.s + 1;
		return (col_dxt1_t){(brru2)(s/3)};
	} else {
		return (col_dxt1_t){.s=0};
	}
}
col_dxt1_t
dxt1_interpolate_noalpha(col_dxt1_t a, col_dxt1_t b, brru1 t)
{
	if (t == 0)
		return a;
	if (t == 1)
		return b;
	if (t == 2) {
		brru4 s = 2 * a.s + b.s + 1;
		return (col_dxt1_t){.s=(brru2)(s/3)};
	}
	brru4 s = a.s + 2 * b.s + 1;
	return (col_dxt1_t){(brru2)(s/3)};
}

void
dxt1_block_recalculate(dxt1_block_t *const block)
{
	if (!block)
		return;
	block->_color2 = dxt1_interpolate(block->color0, block->color1, 2);
	block->_color3 = dxt1_interpolate(block->color0, block->color1, 3);
}
