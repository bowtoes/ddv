#ifndef DDS_UTIL_H
#define DDS_UTIL_H

// Is x a power of 2
#define IISP2(x) ((x)&&!((x)&((x)-1)))
// Is x a multiple of 4
#define IISM4(x) (((x)&3)==0)
// Give lowest int y such that 4|y and y>=x
#define IRND4(x) (((x)+3)&(~3))

// TODO I'm unsure if the order of these bytes holds up on different endians.
#define MAGIC(a,b,c,d) ((brru4)((brru1)(a)<<0)|((brru1)(b)<<8)|((brru1)(c)<<16)|((brru1)(d)<<24))
#define FOURCC(a,b,c,d) ((fcc_t){.fourcc = {(a),(b),(c),(d)}})

#define TOGGLE(a) ((a)=!(a))
#define HASFLAGS(x, f) (((x)&(f))==(f))
#define HASFLAG(x, f) (((x)&(f))!=0)

#include <brrtools/brrtypes.h>

typedef union fcc {
	char fourcc[4];
	brru4 id;
} fcc_t;

typedef struct pr_desc {
	const char *const display;
	const char *const description;
} pr_desc_t;

#define _g_dds_util_magics(_V_) \
	_V_(dds,   DDS,   "DDS ") \
	_V_(dxt1,  DXT1,  "DXT1") \
	_V_(dxt2,  DXT2,  "DXT2") \
	_V_(dxt3,  DXT3,  "DXT3") \
	_V_(dxt4,  DXT5,  "DXT4") \
	_V_(dxt5,  DXT4,  "DXT5") \
	_V_(dxt10, DXT10, "DX10") \

#define _t(a, b, c) dds_magic_##a,
typedef enum dds_magic_index {
	_g_dds_util_magics(_t)
	dds_magic_count,
} dds_magic_index_t;
#undef _t

extern const brru4 dds_magics[dds_magic_count];
extern const fcc_t dds_fccs[dds_magic_count];

typedef union col_rgba {
	brru4 s;
	struct {
		brru1 r;
		brru1 g;
		brru1 b;
		brru1 a;
	};
} col_rgba_t;

typedef union col_dxt1 {
	brru2 s;
	struct {
		brru2 r:5;
		brru2 g:6;
		brru2 b:5;
	};
} col_dxt1_t;

typedef union col_dxt2 {
	brru4 s;
	struct {
		union {
			col_dxt1_t dxt1;
			struct {
				brru2 r:5;
				brru2 g:6;
				brru2 b:5;
			};
		};
		brru2 a:4;
	};
} col_dxt2_t;

/* rgba -> dxt1  */
col_dxt1_t
col_rgba_dxt1(col_rgba_t rgba); // 01

/* rgba -> dxt2  */
col_dxt2_t
col_rgba_dxt2(col_rgba_t rgba); // 02


/* dxt1 -> rgba */
col_rgba_t
col_dxt1_rgba(col_dxt1_t dxt1); // 10

/* dxt1 -> dxt2 */
col_dxt2_t
col_dxt1_dxt2(col_dxt1_t dxt1); // 12


/* dxt2 -> rgba */
col_rgba_t
col_dxt2_rgba(col_dxt2_t dxt2); // 20

/* dxt2 -> dxt1 */
col_dxt1_t
col_dxt2_dxt1(col_dxt2_t dxt2); // 21

#ifndef _keep_dds_util_gens
#undef _g_
#endif

#endif /* DDS_UTIL_H */
