#include "dds/dxt10.h"

pr_desc_t
dxt10_dxgi_format_desc(dxt10_dxgi_format_t format)
{
	switch (format) {
		case DXGI_FORMAT_UNKNOWN:                     return (pr_desc_t){.display="UNKNOWN",                    .description="The format is not known."};
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:       return (pr_desc_t){.display="R32G32B32A32_TYPELESS",      .description="A four-component, 128-bit typeless format that supports 32 bits per channel including alpha."};
		case DXGI_FORMAT_R32G32B32A32_FLOAT:          return (pr_desc_t){.display="R32G32B32A32_FLOAT",         .description="A four-component, 128-bit floating-point format that supports 32 bits per channel including alpha."};
		case DXGI_FORMAT_R32G32B32A32_UINT:           return (pr_desc_t){.display="R32G32B32A32_UINT",          .description="A four-component, 128-bit unsigned-integer format that supports 32 bits per channel including alpha."};
		case DXGI_FORMAT_R32G32B32A32_SINT:           return (pr_desc_t){.display="R32G32B32A32_SINT",          .description="A four-component, 128-bit signed-integer format that supports 32 bits per channel including alpha."};
		case DXGI_FORMAT_R32G32B32_TYPELESS:          return (pr_desc_t){.display="R32G32B32_TYPELESS",         .description="A three-component, 96-bit typeless format that supports 32 bits per color channel."};
		case DXGI_FORMAT_R32G32B32_FLOAT:             return (pr_desc_t){.display="R32G32B32_FLOAT",            .description="A three-component, 96-bit floating-point format that supports 32 bits per color channel."};
		case DXGI_FORMAT_R32G32B32_UINT:              return (pr_desc_t){.display="R32G32B32_UINT",             .description="A three-component, 96-bit unsigned-integer format that supports 32 bits per color channel."};
		case DXGI_FORMAT_R32G32B32_SINT:              return (pr_desc_t){.display="R32G32B32_SINT",             .description="A three-component, 96-bit signed-integer format that supports 32 bits per color channel."};
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:       return (pr_desc_t){.display="R16G16B16A16_TYPELESS",      .description="A four-component, 64-bit typeless format that supports 16 bits per channel including alpha."};
		case DXGI_FORMAT_R16G16B16A16_FLOAT:          return (pr_desc_t){.display="R16G16B16A16_FLOAT",         .description="A four-component, 64-bit floating-point format that supports 16 bits per channel including alpha."};
		case DXGI_FORMAT_R16G16B16A16_UNORM:          return (pr_desc_t){.display="R16G16B16A16_UNORM",         .description="A four-component, 64-bit unsigned-normalized-integer format that supports 16 bits per channel including alpha."};
		case DXGI_FORMAT_R16G16B16A16_UINT:           return (pr_desc_t){.display="R16G16B16A16_UINT",          .description="A four-component, 64-bit unsigned-integer format that supports 16 bits per channel including alpha."};
		case DXGI_FORMAT_R16G16B16A16_SNORM:          return (pr_desc_t){.display="R16G16B16A16_SNORM",         .description="A four-component, 64-bit signed-normalized-integer format that supports 16 bits per channel including alpha."};
		case DXGI_FORMAT_R16G16B16A16_SINT:           return (pr_desc_t){.display="R16G16B16A16_SINT",          .description="A four-component, 64-bit signed-integer format that supports 16 bits per channel including alpha."};
		case DXGI_FORMAT_R32G32_TYPELESS:             return (pr_desc_t){.display="R32G32_TYPELESS",            .description="A two-component, 64-bit typeless format that supports 32 bits for the red channel and 32 bits for the green channel."};
		case DXGI_FORMAT_R32G32_FLOAT:                return (pr_desc_t){.display="R32G32_FLOAT",               .description="A two-component, 64-bit floating-point format that supports 32 bits for the red channel and 32 bits for the green channel."};
		case DXGI_FORMAT_R32G32_UINT:                 return (pr_desc_t){.display="R32G32_UINT",                .description="A two-component, 64-bit unsigned-integer format that supports 32 bits for the red channel and 32 bits for the green channel."};
		case DXGI_FORMAT_R32G32_SINT:                 return (pr_desc_t){.display="R32G32_SINT",                .description="A two-component, 64-bit signed-integer format that supports 32 bits for the red channel and 32 bits for the green channel."};
		case DXGI_FORMAT_R32G8X24_TYPELESS:           return (pr_desc_t){.display="R32G8X24_TYPELESS",          .description="A two-component, 64-bit typeless format that supports 32 bits for the red channel, 8 bits for the green channel, and 24 bits are unused."};
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:        return (pr_desc_t){.display="D32_FLOAT_S8X24_UINT",       .description="A 32-bit floating-point component, and two unsigned-integer components (with an additional 32 bits). This format supports 32-bit depth, 8-bit stencil, and 24 bits are unused."};
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:    return (pr_desc_t){.display="R32_FLOAT_X8X24_TYPELESS",   .description="A 32-bit floating-point component, and two typeless components (with an additional 32 bits). This format supports 32-bit red channel, 8 bits are unused, and 24 bits are unused."};
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:     return (pr_desc_t){.display="X32_TYPELESS_G8X24_UINT",    .description="A 32-bit typeless component, and two unsigned-integer components (with an additional 32 bits). This format has 32 bits unused, 8 bits for green channel, and 24 bits are unused."};
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:        return (pr_desc_t){.display="R10G10B10A2_TYPELESS",       .description="A four-component, 32-bit typeless format that supports 10 bits for each color and 2 bits for alpha."};
		case DXGI_FORMAT_R10G10B10A2_UNORM:           return (pr_desc_t){.display="R10G10B10A2_UNORM",          .description="A four-component, 32-bit unsigned-normalized-integer format that supports 10 bits for each color and 2 bits for alpha."};
		case DXGI_FORMAT_R10G10B10A2_UINT:            return (pr_desc_t){.display="R10G10B10A2_UINT",           .description="A four-component, 32-bit unsigned-integer format that supports 10 bits for each color and 2 bits for alpha."};
		case DXGI_FORMAT_R11G11B10_FLOAT:             return (pr_desc_t){.display="R11G11B10_FLOAT",            .description="Three partial-precision floating-point numbers encoded into a single 32-bit value."};
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:           return (pr_desc_t){.display="R8G8B8A8_TYPELESS",          .description="A four-component, 32-bit typeless format that supports 8 bits per channel including alpha."};
		case DXGI_FORMAT_R8G8B8A8_UNORM:              return (pr_desc_t){.display="R8G8B8A8_UNORM",             .description="A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha."};
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:         return (pr_desc_t){.display="R8G8B8A8_UNORM_SRGB",        .description="A four-component, 32-bit unsigned-normalized integer sRGB format that supports 8 bits per channel including alpha."};
		case DXGI_FORMAT_R8G8B8A8_UINT:               return (pr_desc_t){.display="R8G8B8A8_UINT",              .description="A four-component, 32-bit unsigned-integer format that supports 8 bits per channel including alpha."};
		case DXGI_FORMAT_R8G8B8A8_SNORM:              return (pr_desc_t){.display="R8G8B8A8_SNORM",             .description="A four-component, 32-bit signed-normalized-integer format that supports 8 bits per channel including alpha."};
		case DXGI_FORMAT_R8G8B8A8_SINT:               return (pr_desc_t){.display="R8G8B8A8_SINT",              .description="A four-component, 32-bit signed-integer format that supports 8 bits per channel including alpha."};
		case DXGI_FORMAT_R16G16_TYPELESS:             return (pr_desc_t){.display="R16G16_TYPELESS",            .description="A two-component, 32-bit typeless format that supports 16 bits for the red channel and 16 bits for the green channel."};
		case DXGI_FORMAT_R16G16_FLOAT:                return (pr_desc_t){.display="R16G16_FLOAT",               .description="A two-component, 32-bit floating-point format that supports 16 bits for the red channel and 16 bits for the green channel."};
		case DXGI_FORMAT_R16G16_UNORM:                return (pr_desc_t){.display="R16G16_UNORM",               .description="A two-component, 32-bit unsigned-normalized-integer format that supports 16 bits each for the green and red channels."};
		case DXGI_FORMAT_R16G16_UINT:                 return (pr_desc_t){.display="R16G16_UINT",                .description="A two-component, 32-bit unsigned-integer format that supports 16 bits for the red channel and 16 bits for the green channel."};
		case DXGI_FORMAT_R16G16_SNORM:                return (pr_desc_t){.display="R16G16_SNORM",               .description="A two-component, 32-bit signed-normalized-integer format that supports 16 bits for the red channel and 16 bits for the green channel."};
		case DXGI_FORMAT_R16G16_SINT:                 return (pr_desc_t){.display="R16G16_SINT",                .description="A two-component, 32-bit signed-integer format that supports 16 bits for the red channel and 16 bits for the green channel."};
		case DXGI_FORMAT_R32_TYPELESS:                return (pr_desc_t){.display="R32_TYPELESS",               .description="A single-component, 32-bit typeless format that supports 32 bits for the red channel."};
		case DXGI_FORMAT_D32_FLOAT:                   return (pr_desc_t){.display="D32_FLOAT",                  .description="A single-component, 32-bit floating-point format that supports 32 bits for depth."};
		case DXGI_FORMAT_R32_FLOAT:                   return (pr_desc_t){.display="R32_FLOAT",                  .description="A single-component, 32-bit floating-point format that supports 32 bits for the red channel."};
		case DXGI_FORMAT_R32_UINT:                    return (pr_desc_t){.display="R32_UINT",                   .description="A single-component, 32-bit unsigned-integer format that supports 32 bits for the red channel."};
		case DXGI_FORMAT_R32_SINT:                    return (pr_desc_t){.display="R32_SINT",                   .description="A single-component, 32-bit signed-integer format that supports 32 bits for the red channel."};
		case DXGI_FORMAT_R24G8_TYPELESS:              return (pr_desc_t){.display="R24G8_TYPELESS",             .description="A two-component, 32-bit typeless format that supports 24 bits for the red channel and 8 bits for the green channel."};
		case DXGI_FORMAT_D24_UNORM_S8_UINT:           return (pr_desc_t){.display="D24_UNORM_S8_UINT",          .description="A 32-bit z-buffer format that supports 24 bits for depth and 8 bits for stencil."};
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:       return (pr_desc_t){.display="R24_UNORM_X8_TYPELESS",      .description="A 32-bit format, that contains a 24 bit, single-component, unsigned-normalized integer, with an additional typeless 8 bits. This format has 24 bits red channel and 8 bits unused."};
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:        return (pr_desc_t){.display="X24_TYPELESS_G8_UINT",       .description="A 32-bit format, that contains a 24 bit, single-component, typeless format,  with an additional 8 bit unsigned integer component. This format has 24 bits unused and 8 bits green channel."};
		case DXGI_FORMAT_R8G8_TYPELESS:               return (pr_desc_t){.display="R8G8_TYPELESS",              .description="A two-component, 16-bit typeless format that supports 8 bits for the red channel and 8 bits for the green channel."};
		case DXGI_FORMAT_R8G8_UNORM:                  return (pr_desc_t){.display="R8G8_UNORM",                 .description="A two-component, 16-bit unsigned-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel."};
		case DXGI_FORMAT_R8G8_UINT:                   return (pr_desc_t){.display="R8G8_UINT",                  .description="A two-component, 16-bit unsigned-integer format that supports 8 bits for the red channel and 8 bits for the green channel."};
		case DXGI_FORMAT_R8G8_SNORM:                  return (pr_desc_t){.display="R8G8_SNORM",                 .description="A two-component, 16-bit signed-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel."};
		case DXGI_FORMAT_R8G8_SINT:                   return (pr_desc_t){.display="R8G8_SINT",                  .description="A two-component, 16-bit signed-integer format that supports 8 bits for the red channel and 8 bits for the green channel."};
		case DXGI_FORMAT_R16_TYPELESS:                return (pr_desc_t){.display="R16_TYPELESS",               .description="A single-component, 16-bit typeless format that supports 16 bits for the red channel."};
		case DXGI_FORMAT_R16_FLOAT:                   return (pr_desc_t){.display="R16_FLOAT",                  .description="A single-component, 16-bit floating-point format that supports 16 bits for the red channel."};
		case DXGI_FORMAT_D16_UNORM:                   return (pr_desc_t){.display="D16_UNORM",                  .description="A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for depth."};
		case DXGI_FORMAT_R16_UNORM:                   return (pr_desc_t){.display="R16_UNORM",                  .description="A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for the red channel."};
		case DXGI_FORMAT_R16_UINT:                    return (pr_desc_t){.display="R16_UINT",                   .description="A single-component, 16-bit unsigned-integer format that supports 16 bits for the red channel."};
		case DXGI_FORMAT_R16_SNORM:                   return (pr_desc_t){.display="R16_SNORM",                  .description="A single-component, 16-bit signed-normalized-integer format that supports 16 bits for the red channel."};
		case DXGI_FORMAT_R16_SINT:                    return (pr_desc_t){.display="R16_SINT",                   .description="A single-component, 16-bit signed-integer format that supports 16 bits for the red channel."};
		case DXGI_FORMAT_R8_TYPELESS:                 return (pr_desc_t){.display="R8_TYPELESS",                .description="A single-component, 8-bit typeless format that supports 8 bits for the red channel."};
		case DXGI_FORMAT_R8_UNORM:                    return (pr_desc_t){.display="R8_UNORM",                   .description="A single-component, 8-bit unsigned-normalized-integer format that supports 8 bits for the red channel."};
		case DXGI_FORMAT_R8_UINT:                     return (pr_desc_t){.display="R8_UINT",                    .description="A single-component, 8-bit unsigned-integer format that supports 8 bits for the red channel."};
		case DXGI_FORMAT_R8_SNORM:                    return (pr_desc_t){.display="R8_SNORM",                   .description="A single-component, 8-bit signed-normalized-integer format that supports 8 bits for the red channel."};
		case DXGI_FORMAT_R8_SINT:                     return (pr_desc_t){.display="R8_SINT",                    .description="A single-component, 8-bit signed-integer format that supports 8 bits for the red channel."};
		case DXGI_FORMAT_A8_UNORM:                    return (pr_desc_t){.display="A8_UNORM",                   .description="A single-component, 8-bit unsigned-normalized-integer format for alpha only."};
		case DXGI_FORMAT_R1_UNORM:                    return (pr_desc_t){.display="R1_UNORM",                   .description="A single-component, 1-bit unsigned-normalized integer format that supports 1 bit for the red channel. ²."};
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:          return (pr_desc_t){.display="R9G9B9E5_SHAREDEXP",         .description="Three partial-precision floating-point numbers encoded into a single 32-bit value all sharing the same 5-bit exponent."};
		case DXGI_FORMAT_R8G8_B8G8_UNORM:             return (pr_desc_t){.display="R8G8_B8G8_UNORM",            .description="A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format is analogous to the UYVY format."};
		case DXGI_FORMAT_G8R8_G8B8_UNORM:             return (pr_desc_t){.display="G8R8_G8B8_UNORM",            .description="A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format is analogous to the YUY2 format."};
		case DXGI_FORMAT_BC1_TYPELESS:                return (pr_desc_t){.display="BC1_TYPELESS",               .description="Four-component typeless block-compression format."};
		case DXGI_FORMAT_BC1_UNORM:                   return (pr_desc_t){.display="BC1_UNORM",                  .description="Four-component block-compression format."};
		case DXGI_FORMAT_BC1_UNORM_SRGB:              return (pr_desc_t){.display="BC1_UNORM_SRGB",             .description="Four-component block-compression format for sRGB data."};
		case DXGI_FORMAT_BC2_TYPELESS:                return (pr_desc_t){.display="BC2_TYPELESS",               .description="Four-component typeless block-compression format."};
		case DXGI_FORMAT_BC2_UNORM:                   return (pr_desc_t){.display="BC2_UNORM",                  .description="Four-component block-compression format."};
		case DXGI_FORMAT_BC2_UNORM_SRGB:              return (pr_desc_t){.display="BC2_UNORM_SRGB",             .description="Four-component block-compression format for sRGB data."};
		case DXGI_FORMAT_BC3_TYPELESS:                return (pr_desc_t){.display="BC3_TYPELESS",               .description="Four-component typeless block-compression format."};
		case DXGI_FORMAT_BC3_UNORM:                   return (pr_desc_t){.display="BC3_UNORM",                  .description="Four-component block-compression format."};
		case DXGI_FORMAT_BC3_UNORM_SRGB:              return (pr_desc_t){.display="BC3_UNORM_SRGB",             .description="Four-component block-compression format for sRGB data."};
		case DXGI_FORMAT_BC4_TYPELESS:                return (pr_desc_t){.display="BC4_TYPELESS",               .description="One-component typeless block-compression format."};
		case DXGI_FORMAT_BC4_UNORM:                   return (pr_desc_t){.display="BC4_UNORM",                  .description="One-component block-compression format."};
		case DXGI_FORMAT_BC4_SNORM:                   return (pr_desc_t){.display="BC4_SNORM",                  .description="One-component block-compression format."};
		case DXGI_FORMAT_BC5_TYPELESS:                return (pr_desc_t){.display="BC5_TYPELESS",               .description="Two-component typeless block-compression format."};
		case DXGI_FORMAT_BC5_UNORM:                   return (pr_desc_t){.display="BC5_UNORM",                  .description="Two-component block-compression format."};
		case DXGI_FORMAT_BC5_SNORM:                   return (pr_desc_t){.display="BC5_SNORM",                  .description="Two-component block-compression format."};
		case DXGI_FORMAT_B5G6R5_UNORM:                return (pr_desc_t){.display="B5G6R5_UNORM",               .description="A three-component, 16-bit unsigned-normalized-integer format that supports 5 bits for blue, 6 bits for green, and 5 bits for red."};
		case DXGI_FORMAT_B5G5R5A1_UNORM:              return (pr_desc_t){.display="B5G5R5A1_UNORM",             .description="A four-component, 16-bit unsigned-normalized-integer format that supports 5 bits for each color channel and 1-bit alpha."};
		case DXGI_FORMAT_B8G8R8A8_UNORM:              return (pr_desc_t){.display="B8G8R8A8_UNORM",             .description="A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8-bit alpha."};
		case DXGI_FORMAT_B8G8R8X8_UNORM:              return (pr_desc_t){.display="B8G8R8X8_UNORM",             .description="A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8 bits unused."};
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:  return (pr_desc_t){.display="R10G10B10_XR_BIAS_A2_UNORM", .description="A four-component, 32-bit 2.8-biased fixed-point format that supports 10 bits for each color channel and 2-bit alpha."};
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:           return (pr_desc_t){.display="B8G8R8A8_TYPELESS",          .description="A four-component, 32-bit typeless format that supports 8 bits for each channel including alpha."};
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:         return (pr_desc_t){.display="B8G8R8A8_UNORM_SRGB",        .description="A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each channel including alpha."};
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:           return (pr_desc_t){.display="B8G8R8X8_TYPELESS",          .description="A four-component, 32-bit typeless format that supports 8 bits for each color channel, and 8 bits are unused."};
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:         return (pr_desc_t){.display="B8G8R8X8_UNORM_SRGB",        .description="A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each color channel, and 8 bits are unused."};
		case DXGI_FORMAT_BC6H_TYPELESS:               return (pr_desc_t){.display="BC6H_TYPELESS",              .description="A typeless block-compression format."};
		case DXGI_FORMAT_BC6H_UF16:                   return (pr_desc_t){.display="BC6H_UF16",                  .description="A block-compression format."};
		case DXGI_FORMAT_BC6H_SF16:                   return (pr_desc_t){.display="BC6H_SF16",                  .description="A block-compression format."};
		case DXGI_FORMAT_BC7_TYPELESS:                return (pr_desc_t){.display="BC7_TYPELESS",               .description="A typeless block-compression format."};
		case DXGI_FORMAT_BC7_UNORM:                   return (pr_desc_t){.display="BC7_UNORM",                  .description="A block-compression format."};
		case DXGI_FORMAT_BC7_UNORM_SRGB:              return (pr_desc_t){.display="BC7_UNORM_SRGB",             .description="A block-compression format."};
		case DXGI_FORMAT_AYUV:                        return (pr_desc_t){.display="AYUV",                       .description="Most common YUV 4:4:4 video resource format."};
		case DXGI_FORMAT_Y410:                        return (pr_desc_t){.display="Y410",                       .description="10-bit per channel packed YUV 4:4:4 video resource format."};
		case DXGI_FORMAT_Y416:                        return (pr_desc_t){.display="Y416",                       .description="16-bit per channel packed YUV 4:4:4 video resource format."};
		case DXGI_FORMAT_NV12:                        return (pr_desc_t){.display="NV12",                       .description="Most common YUV 4:2:0 video resource format."};
		case DXGI_FORMAT_P010:                        return (pr_desc_t){.display="P010",                       .description="10-bit per channel planar YUV 4:2:0 video resource format."};
		case DXGI_FORMAT_P016:                        return (pr_desc_t){.display="P016",                       .description="16-bit per channel planar YUV 4:2:0 video resource format."};
		case DXGI_FORMAT_420_OPAQUE:                  return (pr_desc_t){.display="420_OPAQUE",                 .description="8-bit per channel planar YUV 4:2:0 video resource format."};
		case DXGI_FORMAT_YUY2:                        return (pr_desc_t){.display="YUY2",                       .description="Most common YUV 4:2:2 video resource format."};
		case DXGI_FORMAT_Y210:                        return (pr_desc_t){.display="Y210",                       .description="10-bit per channel packed YUV 4:2:2 video resource format."};
		case DXGI_FORMAT_Y216:                        return (pr_desc_t){.display="Y216",                       .description="16-bit per channel packed YUV 4:2:2 video resource format."};
		case DXGI_FORMAT_NV11:                        return (pr_desc_t){.display="NV11",                       .description="Most common planar YUV 4:1:1 video resource format."};
		case DXGI_FORMAT_AI44:                        return (pr_desc_t){.display="AI44",                       .description="4-bit palletized YUV format that is commonly used for DVD subpicture."};
		case DXGI_FORMAT_IA44:                        return (pr_desc_t){.display="IA44",                       .description="4-bit palletized YUV format that is commonly used for DVD subpicture."};
		case DXGI_FORMAT_P8:                          return (pr_desc_t){.display="P8",                         .description="8-bit palletized format that is used for palletized RGB data when the processor processes ISDB-T data and for palletized YUV data when the processor processes BluRay data."};
		case DXGI_FORMAT_A8P8:                        return (pr_desc_t){.display="A8P8",                       .description="8-bit palletized format with 8 bits of alpha that is used for palletized YUV data when the processor processes BluRay data."};
		case DXGI_FORMAT_B4G4R4A4_UNORM:              return (pr_desc_t){.display="B4G4R4A4_UNORM",             .description="A four-component, 16-bit unsigned-normalized integer format that supports 4 bits for each channel including alpha."};
		case DXGI_FORMAT_P208:                        return (pr_desc_t){.display="P208",                       .description="A video format; an 8-bit version of a hybrid planar 4:2:2 format."};
		case DXGI_FORMAT_V208:                        return (pr_desc_t){.display="V208",                       .description="An 8 bit YCbCrA 4:4 rendering format."};
		case DXGI_FORMAT_V408:                        return (pr_desc_t){.display="V408",                       .description="An 8 bit YCbCrA 4:4:4:4 rendering format."};
		case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:          return (pr_desc_t){.display="SAMPLER_FEEDBACK_MIN_MIP_OPAQUE",         .description="Description TODO"};
		case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:  return (pr_desc_t){.display="SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE", .description="Description TODO"};
		default: return (pr_desc_t){.display="INVALID", .description="The format is invalid."};
	}
}

pr_desc_t
dxt10_dimension_desc(dxt10_dimension_t dimension)
{
	switch (dimension) {
		case DDS_DIMENSION_TEXTURE_1D: return (pr_desc_t){.display="TEXTURE_1D", .description="TODO description"};
		case DDS_DIMENSION_TEXTURE_2D: return (pr_desc_t){.display="TEXTURE_2D", .description="TODO description"};
		case DDS_DIMENSION_TEXTURE_3D: return (pr_desc_t){.display="TEXTURE_3D", .description="TODO description"};
		default: return (pr_desc_t){.display="INVALID", .description="Invalid dimension."};
	}
}

pr_desc_t
dxt10_resource_misc_desc(dxt10_resource_misc_t resource)
{
	switch(resource) {
		case DDS_RESOURCE_MISC_TEXTURECUBE: return (pr_desc_t){.display="MISC_TEXTURECUBE", .description="TODO description"};
		default: return (pr_desc_t){.display="INVALID", .description="Invalid resource."};
	}
}

pr_desc_t
dxt10_alpha_mode_desc(dxt10_alpha_mode_t mode)
{
	switch (mode) {
		case DDS_ALPHA_MODE_UNKNOWN:       return (pr_desc_t){.display="ALPHA_UNKNOWN", .description="TODO description"};
		case DDS_ALPHA_MODE_STRAIGHT:      return (pr_desc_t){.display="ALPHA_STRAIGHT", .description="TODO description"};
		case DDS_ALPHA_MODE_PREMULTIPLIED: return (pr_desc_t){.display="ALPHA_PREMULTIPLIED", .description="TODO description"};
		case DDS_ALPHA_MODE_OPAQUE:        return (pr_desc_t){.display="ALPHA_OPAQUE", .description="TODO description"};
		case DDS_ALPHA_MODE_CUSTOM:        return (pr_desc_t){.display="ALPHA_CUSTOM", .description="TODO description"};
		default: return (pr_desc_t){.display="INVALID", .description="Invalid mode."};
	}
}
