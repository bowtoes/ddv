#ifndef DXT2_H
#define DXT2_H

#include "dds/dxtn/dxt1.h"

typedef union dxt2RowT {
	u16 row;
	struct {
		u8 col0:4;
		u8 col1:4;
		u8 col2:4;
		u8 col3:4;
	};
} dxt2RowT;
typedef union dxt2AlphaT {
	u64 table;
	u16 rows[4];
	struct {
		dxt2RowT row0;
		dxt2RowT row1;
		dxt2RowT row2;
		dxt2RowT row3;
	};
} dxt2AlphaT;

typedef struct dxt2BlockT {
	dxt2AlphaT alphablock;
	dxt1BlockT colorblock;
} dxt2BlockT;
PD_STATIC_ASSERT(sizeof(dxt2BlockT) == 16, "");

/* The only difference between DXT2 and DXT3 when stored on disk is the fourcc. */
#define DXT2_MAGIC  MAGIC('D','X','T','2')
#define DXT2_FOURCC FOURCC('D','X','T','2')
#define DXT3_MAGIC  MAGIC('D','X','T','3')
#define DXT3_FOURCC FOURCC('D','X','T','3')

// Return the alpha value stored at position (x,y), in the lowest 4-bits of output.
u8 dxt2GetAlphaBits(dxt2AlphaT *table, u8 x, u8 y);
// Set the value in the table at position (x,y) to the lowest 4-bits of input v.
void dxt2SetAlphaBits(dxt2AlphaT *table, u8 x, u8 y, u8 v);

#endif /* DXT2_H */
