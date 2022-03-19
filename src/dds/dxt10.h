#ifndef DXT10_H
#define DXT10_H

#include "common/pdTypes.h"
#include "common/pdDebug.h"
#include "common/pdUtil.h"

typedef enum dxt10DXGIFormatT{
	DXGI_FORMAT_UNKNOWN,                    // The format is not known.
	DXGI_FORMAT_R32G32B32A32_TYPELESS,      // A four-component, 128-bit typeless format that supports 32 bits per channel including alpha.
	DXGI_FORMAT_R32G32B32A32_FLOAT,         // A four-component, 128-bit floating-point format that supports 32 bits per channel including alpha.
	DXGI_FORMAT_R32G32B32A32_UINT,          // A four-component, 128-bit unsigned-integer format that supports 32 bits per channel including alpha.
	DXGI_FORMAT_R32G32B32A32_SINT,          // A four-component, 128-bit signed-integer format that supports 32 bits per channel including alpha.
	DXGI_FORMAT_R32G32B32_TYPELESS,         // A three-component, 96-bit typeless format that supports 32 bits per color channel.
	DXGI_FORMAT_R32G32B32_FLOAT,            // A three-component, 96-bit floating-point format that supports 32 bits per color channel.
	DXGI_FORMAT_R32G32B32_UINT,             // A three-component, 96-bit unsigned-integer format that supports 32 bits per color channel.
	DXGI_FORMAT_R32G32B32_SINT,             // A three-component, 96-bit signed-integer format that supports 32 bits per color channel.
	DXGI_FORMAT_R16G16B16A16_TYPELESS,      // A four-component, 64-bit typeless format that supports 16 bits per channel including alpha.
	DXGI_FORMAT_R16G16B16A16_FLOAT,         // A four-component, 64-bit floating-point format that supports 16 bits per channel including alpha.
	DXGI_FORMAT_R16G16B16A16_UNORM,         // A four-component, 64-bit unsigned-normalized-integer format that supports 16 bits per channel including alpha.
	DXGI_FORMAT_R16G16B16A16_UINT,          // A four-component, 64-bit unsigned-integer format that supports 16 bits per channel including alpha.
	DXGI_FORMAT_R16G16B16A16_SNORM,         // A four-component, 64-bit signed-normalized-integer format that supports 16 bits per channel including alpha.
	DXGI_FORMAT_R16G16B16A16_SINT,          // A four-component, 64-bit signed-integer format that supports 16 bits per channel including alpha.
	DXGI_FORMAT_R32G32_TYPELESS,            // A two-component, 64-bit typeless format that supports 32 bits for the red channel and 32 bits for the green channel.
	DXGI_FORMAT_R32G32_FLOAT,               // A two-component, 64-bit floating-point format that supports 32 bits for the red channel and 32 bits for the green channel.
	DXGI_FORMAT_R32G32_UINT,                // A two-component, 64-bit unsigned-integer format that supports 32 bits for the red channel and 32 bits for the green channel.
	DXGI_FORMAT_R32G32_SINT,                // A two-component, 64-bit signed-integer format that supports 32 bits for the red channel and 32 bits for the green channel.
	DXGI_FORMAT_R32G8X24_TYPELESS,          // A two-component, 64-bit typeless format that supports 32 bits for the red channel, 8 bits for the green channel, and 24 bits are unused.
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT,       // A 32-bit floating-point component, and two unsigned-integer components (with an additional 32 bits). This format supports 32-bit depth, 8-bit stencil, and 24 bits are unused.
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,   // A 32-bit floating-point component, and two typeless components (with an additional 32 bits). This format supports 32-bit red channel, 8 bits are unused, and 24 bits are unused.
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,    // A 32-bit typeless component, and two unsigned-integer components (with an additional 32 bits). This format has 32 bits unused, 8 bits for green channel, and 24 bits are unused.
	DXGI_FORMAT_R10G10B10A2_TYPELESS,       // A four-component, 32-bit typeless format that supports 10 bits for each color and 2 bits for alpha.
	DXGI_FORMAT_R10G10B10A2_UNORM,          // A four-component, 32-bit unsigned-normalized-integer format that supports 10 bits for each color and 2 bits for alpha.
	DXGI_FORMAT_R10G10B10A2_UINT,           // A four-component, 32-bit unsigned-integer format that supports 10 bits for each color and 2 bits for alpha.
	DXGI_FORMAT_R11G11B10_FLOAT,            // Three partial-precision floating-point numbers encoded into a single 32-bit value.
	DXGI_FORMAT_R8G8B8A8_TYPELESS,          // A four-component, 32-bit typeless format that supports 8 bits per channel including alpha.
	DXGI_FORMAT_R8G8B8A8_UNORM,             // A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha.
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,        // A four-component, 32-bit unsigned-normalized integer sRGB format that supports 8 bits per channel including alpha.
	DXGI_FORMAT_R8G8B8A8_UINT,              // A four-component, 32-bit unsigned-integer format that supports 8 bits per channel including alpha.
	DXGI_FORMAT_R8G8B8A8_SNORM,             // A four-component, 32-bit signed-normalized-integer format that supports 8 bits per channel including alpha.
	DXGI_FORMAT_R8G8B8A8_SINT,              // A four-component, 32-bit signed-integer format that supports 8 bits per channel including alpha.
	DXGI_FORMAT_R16G16_TYPELESS,            // A two-component, 32-bit typeless format that supports 16 bits for the red channel and 16 bits for the green channel.
	DXGI_FORMAT_R16G16_FLOAT,               // A two-component, 32-bit floating-point format that supports 16 bits for the red channel and 16 bits for the green channel.
	DXGI_FORMAT_R16G16_UNORM,               // A two-component, 32-bit unsigned-normalized-integer format that supports 16 bits each for the green and red channels.
	DXGI_FORMAT_R16G16_UINT,                // A two-component, 32-bit unsigned-integer format that supports 16 bits for the red channel and 16 bits for the green channel.
	DXGI_FORMAT_R16G16_SNORM,               // A two-component, 32-bit signed-normalized-integer format that supports 16 bits for the red channel and 16 bits for the green channel.
	DXGI_FORMAT_R16G16_SINT,                // A two-component, 32-bit signed-integer format that supports 16 bits for the red channel and 16 bits for the green channel.
	DXGI_FORMAT_R32_TYPELESS,               // A single-component, 32-bit typeless format that supports 32 bits for the red channel.
	DXGI_FORMAT_D32_FLOAT,                  // A single-component, 32-bit floating-point format that supports 32 bits for depth.
	DXGI_FORMAT_R32_FLOAT,                  // A single-component, 32-bit floating-point format that supports 32 bits for the red channel.
	DXGI_FORMAT_R32_UINT,                   // A single-component, 32-bit unsigned-integer format that supports 32 bits for the red channel.
	DXGI_FORMAT_R32_SINT,                   // A single-component, 32-bit signed-integer format that supports 32 bits for the red channel.
	DXGI_FORMAT_R24G8_TYPELESS,             // A two-component, 32-bit typeless format that supports 24 bits for the red channel and 8 bits for the green channel.
	DXGI_FORMAT_D24_UNORM_S8_UINT,          // A 32-bit z-buffer format that supports 24 bits for depth and 8 bits for stencil.
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,      // A 32-bit format, that contains a 24 bit, single-component, unsigned-normalized integer, with an additional typeless 8 bits. This format has 24 bits red channel and 8 bits unused.
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,       // A 32-bit format, that contains a 24 bit, single-component, typeless format,  with an additional 8 bit unsigned integer component. This format has 24 bits unused and 8 bits green channel.
	DXGI_FORMAT_R8G8_TYPELESS,              // A two-component, 16-bit typeless format that supports 8 bits for the red channel and 8 bits for the green channel.
	DXGI_FORMAT_R8G8_UNORM,                 // A two-component, 16-bit unsigned-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
	DXGI_FORMAT_R8G8_UINT,                  // A two-component, 16-bit unsigned-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
	DXGI_FORMAT_R8G8_SNORM,                 // A two-component, 16-bit signed-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
	DXGI_FORMAT_R8G8_SINT,                  // A two-component, 16-bit signed-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
	DXGI_FORMAT_R16_TYPELESS,               // A single-component, 16-bit typeless format that supports 16 bits for the red channel.
	DXGI_FORMAT_R16_FLOAT,                  // A single-component, 16-bit floating-point format that supports 16 bits for the red channel.
	DXGI_FORMAT_D16_UNORM,                  // A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for depth.
	DXGI_FORMAT_R16_UNORM,                  // A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for the red channel.
	DXGI_FORMAT_R16_UINT,                   // A single-component, 16-bit unsigned-integer format that supports 16 bits for the red channel.
	DXGI_FORMAT_R16_SNORM,                  // A single-component, 16-bit signed-normalized-integer format that supports 16 bits for the red channel.
	DXGI_FORMAT_R16_SINT,                   // A single-component, 16-bit signed-integer format that supports 16 bits for the red channel.
	DXGI_FORMAT_R8_TYPELESS,                // A single-component, 8-bit typeless format that supports 8 bits for the red channel.
	DXGI_FORMAT_R8_UNORM,                   // A single-component, 8-bit unsigned-normalized-integer format that supports 8 bits for the red channel.
	DXGI_FORMAT_R8_UINT,                    // A single-component, 8-bit unsigned-integer format that supports 8 bits for the red channel.
	DXGI_FORMAT_R8_SNORM,                   // A single-component, 8-bit signed-normalized-integer format that supports 8 bits for the red channel.
	DXGI_FORMAT_R8_SINT,                    // A single-component, 8-bit signed-integer format that supports 8 bits for the red channel.
	DXGI_FORMAT_A8_UNORM,                   // A single-component, 8-bit unsigned-normalized-integer format for alpha only.
	DXGI_FORMAT_R1_UNORM,                   // A single-component, 1-bit unsigned-normalized integer format that supports 1 bit for the red channel. ².
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP,         // Three partial-precision floating-point numbers encoded into a single 32-bit value all sharing the same 5-bit exponent.
	DXGI_FORMAT_R8G8_B8G8_UNORM,            // A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format is analogous to the UYVY format.
	DXGI_FORMAT_G8R8_G8B8_UNORM,            // A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format is analogous to the YUY2 format.
	DXGI_FORMAT_BC1_TYPELESS,               // Four-component typeless block-compression format.
	DXGI_FORMAT_BC1_UNORM,                  // Four-component block-compression format.
	DXGI_FORMAT_BC1_UNORM_SRGB,             // Four-component block-compression format for sRGB data.
	DXGI_FORMAT_BC2_TYPELESS,               // Four-component typeless block-compression format.
	DXGI_FORMAT_BC2_UNORM,                  // Four-component block-compression format.
	DXGI_FORMAT_BC2_UNORM_SRGB,             // Four-component block-compression format for sRGB data.
	DXGI_FORMAT_BC3_TYPELESS,               // Four-component typeless block-compression format.
	DXGI_FORMAT_BC3_UNORM,                  // Four-component block-compression format.
	DXGI_FORMAT_BC3_UNORM_SRGB,             // Four-component block-compression format for sRGB data.
	DXGI_FORMAT_BC4_TYPELESS,               // One-component typeless block-compression format.
	DXGI_FORMAT_BC4_UNORM,                  // One-component block-compression format.
	DXGI_FORMAT_BC4_SNORM,                  // One-component block-compression format.
	DXGI_FORMAT_BC5_TYPELESS,               // Two-component typeless block-compression format.
	DXGI_FORMAT_BC5_UNORM,                  // Two-component block-compression format.
	DXGI_FORMAT_BC5_SNORM,                  // Two-component block-compression format.
	DXGI_FORMAT_B5G6R5_UNORM,               // A three-component, 16-bit unsigned-normalized-integer format that supports 5 bits for blue, 6 bits for green, and 5 bits for red.
	DXGI_FORMAT_B5G5R5A1_UNORM,             // A four-component, 16-bit unsigned-normalized-integer format that supports 5 bits for each color channel and 1-bit alpha.
	DXGI_FORMAT_B8G8R8A8_UNORM,             // A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8-bit alpha.
	DXGI_FORMAT_B8G8R8X8_UNORM,             // A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8 bits unused.
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM, // A four-component, 32-bit 2.8-biased fixed-point format that supports 10 bits for each color channel and 2-bit alpha.
	DXGI_FORMAT_B8G8R8A8_TYPELESS,          // A four-component, 32-bit typeless format that supports 8 bits for each channel including alpha.
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,        // A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each channel including alpha.
	DXGI_FORMAT_B8G8R8X8_TYPELESS,          // A four-component, 32-bit typeless format that supports 8 bits for each color channel, and 8 bits are unused.
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,        // A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each color channel, and 8 bits are unused.
	DXGI_FORMAT_BC6H_TYPELESS,              // A typeless block-compression format.
	DXGI_FORMAT_BC6H_UF16,                  // A block-compression format.
	DXGI_FORMAT_BC6H_SF16,                  // A block-compression format.
	DXGI_FORMAT_BC7_TYPELESS,               // A typeless block-compression format.
	DXGI_FORMAT_BC7_UNORM,                  // A block-compression format.
	DXGI_FORMAT_BC7_UNORM_SRGB,             // A block-compression format.
	DXGI_FORMAT_AYUV,                       // Most common YUV 4:4:4 video resource format.
	DXGI_FORMAT_Y410,                       // 10-bit per channel packed YUV 4:4:4 video resource format.
	DXGI_FORMAT_Y416,                       // 16-bit per channel packed YUV 4:4:4 video resource format.
	DXGI_FORMAT_NV12,                       // Most common YUV 4:2:0 video resource format.
	DXGI_FORMAT_P010,                       // 10-bit per channel planar YUV 4:2:0 video resource format.
	DXGI_FORMAT_P016,                       // 16-bit per channel planar YUV 4:2:0 video resource format.
	DXGI_FORMAT_420_OPAQUE,                 // 8-bit per channel planar YUV 4:2:0 video resource format.
	DXGI_FORMAT_YUY2,                       // Most common YUV 4:2:2 video resource format.
	DXGI_FORMAT_Y210,                       // 10-bit per channel packed YUV 4:2:2 video resource format.
	DXGI_FORMAT_Y216,                       // 16-bit per channel packed YUV 4:2:2 video resource format.
	DXGI_FORMAT_NV11,                       // Most common planar YUV 4:1:1 video resource format.
	DXGI_FORMAT_AI44,                       // 4-bit palletized YUV format that is commonly used for DVD subpicture.
	DXGI_FORMAT_IA44,                       // 4-bit palletized YUV format that is commonly used for DVD subpicture.
	DXGI_FORMAT_P8,                         // 8-bit palletized format that is used for palletized RGB data when the processor processes ISDB-T data and for palletized YUV data when the processor processes BluRay data.
	DXGI_FORMAT_A8P8,                       // 8-bit palletized format with 8 bits of alpha that is used for palletized YUV data when the processor processes BluRay data.
	DXGI_FORMAT_B4G4R4A4_UNORM,             // A four-component, 16-bit unsigned-normalized integer format that supports 4 bits for each channel including alpha.
	DXGI_FORMAT_P208,                       // A video format; an 8-bit version of a hybrid planar 4:2:2 format.
	DXGI_FORMAT_V208,                       // An 8 bit YCbCrA 4:4 rendering format.
	DXGI_FORMAT_V408,                       // An 8 bit YCbCrA 4:4:4:4 rendering format.
	DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
	DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
	DXGI_FORMAT_FORCE_UINT = 0xFFFFFFFFUL   // Forces this enumeration to compile to 32 bits in size.
} dxt10FormatT;
typedef enum dxt10DimensionT {
	DDS_DIMENSION_TEXTURE_1D = 2, // DDS is a 1D texture, with size stored in width.
	DDS_DIMENSION_TEXTURE_2D = 3, // DDS is a 2D texture, with width and height stored in width and height respectively.
	DDS_DIMENSION_TEXTURE_3D = 4, // DDS is a 3D texture, with depth stored in depth.
} dxt10DimensionT;
typedef enum dxt10ResourceMiscT {
	DDS_RESOURCE_MISC_TEXTURECUBE = 0x4, // Indicates a 2D texture is a cubemap.
} dxt10ResourceMiscT;
typedef enum dxt10AlphaModeT {
	DDS_ALPHA_MODE_UNKNOWN       = 0x0, // Alpha channel content is unknown.
	DDS_ALPHA_MODE_STRAIGHT      = 0x1, // Alpha channel content is presumed to be straight.
	DDS_ALPHA_MODE_PREMULTIPLIED = 0x2, // Alpha channel content is premultiplied.
	DDS_ALPHA_MODE_OPAQUE        = 0x3, // Alpha channel content is set to fully opaque.
	DDS_ALPHA_MODE_CUSTOM        = 0x4, // Alpha channel content is not meant to represent transparancy.
} dxt10AlphaModeT;
typedef struct ddsHeaderDXT10T {
	u32 format;     // DXGI pixel format.
	u32 dimension;  // D3D10 resource dimension.
	u32 miscflag;   // Less common options for resources.
	u32 arraysize;  // Number of textures in DDS. Must be 1 for 3D textures.
	u32 alphaflag;  // Flag specifiying how alpha is represented in DDS.
} ddsHeaderDXT10T;
#define DDS_HEADERDXT10_SIZE 20
PD_STATIC_ASSERT(sizeof(ddsHeaderDXT10T) == DDS_HEADERDXT10_SIZE, "");

#define DXT10_MAGIC  MAGIC('D','X','1','0')
#define DXT10_FOURCC FOURCC('D','X','1','0')

#endif /* DXT10_H */
