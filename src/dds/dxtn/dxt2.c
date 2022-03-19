#include "dds/dxtn/dxt2.h"

#include "common/pdTypes.h"

u8
dxt2GetAlphaBits(dxt2AlphaT *table, u8 x, u8 y)
{
	u8 v = 0;
	if (table) {
		x %= 4;
		y %= 4;
		v = (table->rows[y] & (15 << (4 * x))) >> (4 * x);
	}
	return v;
}

void
dxt2SetAlphaBits(dxt2AlphaT *table, u8 x, u8 y, u8 v)
{
	if (table) {
		x %= 4;
		y %= 4;
		table->rows[y] = (table->rows[y] & ~(15 << (4 * x))) | ((v & 15) << (2 * x));
	}
}
