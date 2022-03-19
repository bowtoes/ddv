#include "dds/dxtn/dxt1.h"

#include "common/pdLog.h"

u8
dxt1GetBitmapBits(dxt1BitmapT *table, u8 x, u8 y)
{
	if (!table)
		return 0;
	x %= 4;
	y %= 4;
	return (table->rows[y] & (3 << (2 * x))) >> (2 * x);
}
void
dxt1SetBitmapBits(dxt1BitmapT *table, u8 x, u8 y, u8 v)
{
	if (!table)
		return;
	x %= 4;
	y %= 4;
	table->rows[y] = (table->rows[y] & ~(3 << (2 * x))) | ((v & 3) << (2 * x));
}
dxt1ColorT
dxt1GetBitmapColor(dxt1BlockT *block, u8 x, u8 y)
{
	u32 out = 0;
	if (block) {
		u8 bt = dxt1GetBitmapBits(&block->bitmap, x, y);
		if (bt == 0) {
			out = block->color0.color;
		} else if (bt == 1) {
			out = block->color1.color;
		} else if (bt == 2) {
			if (block->color0.color > block->color1.color) {
				out = 2 * block->color0.color + 1;
				out += block->color1.color;
				out /= 3;
			} else {
				out = (block->color0.color + block->color1.color) / 2;
			}
		} else if (bt == 3) {
			if (block->color0.color > block->color1.color) {
				out = block->color0.color + 1;
				out += 2 * block->color1.color;
				out /= 3;
			} else {
				out = 0; // Used to represent alpha, I guess.
			}
		}
	}
	return (dxt1ColorT){(u16)out};
}

static void printtable(dxt1BitmapT *table, int aaaa) {
	PD_LOG_OUT("Table %08x %u", table->table, table->table);
	if (aaaa) {
		for (int y = 0; y < 4; ++y) {
			PD_LOG_OUT("Row %i %u", y, table->rows[y]);
		}
	}
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			u8 d = dxt1GetBitmapBits(table, x, y);
			PD_LOGBN_OUT(0, 0, &d, 2);
			if (x < 3)
				PD_LOGN_OUT(" ");
		}
		PD_LOG_OUT("");
	}
}
