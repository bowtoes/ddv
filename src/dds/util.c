#define _keep_dds_util_gens
#include "dds/util.h"

#define _t(a, b, c) MAGIC((c)[0], (c)[1], (c)[2], (c)[3]),
const brru4 dds_magics[dds_magic_count] = { _g_dds_util_magics(_t) };
#undef _t

#define _t(a, b, c) {.fourcc={(c)[0], (c)[1], (c)[2], (c)[3]}},
const fcc_t dds_fccs[dds_magic_count] = { _g_dds_util_magics(_t) };
#undef _t

//#define _t(a, b, c) const brru4 DDS_MAGIC_##b = MAGIC((c)[0], (c)[1], (c)[2], (c)[3]);
//_g(_t)
//#undef _t
//#define _t(a, b, c) const fcc_t DDS_FCC_##b = {.fourcc={(c)[0], (c)[1], (c)[2], (c)[3]}};
//_g(_t)
//#undef _t

col_dxt1_t
col_rgba_dxt1(col_rgba_t rgba)
{
	return (col_dxt1_t){
		.r = rgba.r >> 3,
		.g = rgba.g >> 2,
		.b = rgba.b >> 3,
	};
}

col_dxt2_t
col_rgba_dxt2(col_rgba_t rgba)
{
	return (col_dxt2_t){
		.dxt1 = col_rgba_dxt1(rgba),
		.a = rgba.a >> 4
	};
}

col_rgba_t
col_dxt1_rgba(col_dxt1_t dxt1)
{
	return (col_rgba_t){
		.r = dxt1.r << 3,
		.g = dxt1.g << 2,
		.b = dxt1.b << 3,
	};
}

col_dxt2_t
col_dxt1_dxt2(col_dxt1_t dxt1)
{
	return (col_dxt2_t){
		.dxt1 = dxt1,
		.a = 0
	};
}

col_rgba_t
col_dxt2_rgba(col_dxt2_t dxt2)
{
	return (col_rgba_t){
		.r = dxt2.r << 3,
		.g = dxt2.g << 2,
		.b = dxt2.b << 3,
		.a = dxt2.a << 4,
	};
}

col_dxt1_t
col_dxt2_dxt1(col_dxt2_t dxt2)
{
	return dxt2.dxt1;
}
