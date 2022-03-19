#ifndef DXT1_H
#define DXT1_H

#include "common/pdTypes.h"
#include "common/pdDebug.h"
#include "common/pdUtil.h"

typedef union dxt1ColorT {
	u16 color;
	struct {
		u16 r:5;
		u16 g:6;
		u16 b:5;
	};
} dxt1ColorT;

typedef union dxt1RowT {
	u8 row;
	struct {
		u8 col0:2;
		u8 col1:2;
		u8 col2:2;
		u8 col3:2;
	};
} dxt1RowT;
typedef union dxt1BitmapT {
	u32 table;
	u8 rows[4];
	struct {
		dxt1RowT row0;
		dxt1RowT row1;
		dxt1RowT row2;
		dxt1RowT row3;
	};
} dxt1BitmapT;

typedef struct dxt1BlockT{
	dxt1ColorT color0;
	dxt1ColorT color1;
	dxt1BitmapT bitmap;
} dxt1BlockT;
PD_STATIC_ASSERT(sizeof(dxt1BlockT) == 8, "");

#define DXT1_MAGIC  MAGIC('D','X','T','1')
#define DXT1_FOURCC FOURCC('D','X','T','1')

// Return the value in the table at position (x,y), in the lowest 2-bits of output.
u8 dxt1GetBitmapBits(dxt1BitmapT *table, u8 x, u8 y);
// Set the value in the table at position (x,y) to the lowest 2-bits of input v.
void dxt1SetBitmapBits(dxt1BitmapT *table, u8 x, u8 y, u8 v);
// Get the color value represented by the table index (x,y) of dxt1Block block.
dxt1ColorT dxt1GetBitmapColor(dxt1BlockT *block, u8 x, u8 y);

#endif /* DXT1_H */
