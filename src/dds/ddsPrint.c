#include "dds/ddsPrint.h"

#include "common/pdLog.h"
#include "common/pdUtil.h"

static const char *dxt10FormatStr(dxt10FormatT f) {
	switch (f) {
		case DXGI_FORMAT_UNKNOWN:                    return "UNKNOWN";
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:      return "R32G32B32A32_TYPELESS";
		case DXGI_FORMAT_R32G32B32A32_FLOAT:         return "R32G32B32A32_FLOAT";
		case DXGI_FORMAT_R32G32B32A32_UINT:          return "R32G32B32A32_UINT";
		case DXGI_FORMAT_R32G32B32A32_SINT:          return "R32G32B32A32_SINT";
		case DXGI_FORMAT_R32G32B32_TYPELESS:         return "R32G32B32_TYPELESS";
		case DXGI_FORMAT_R32G32B32_FLOAT:            return "R32G32B32_FLOAT";
		case DXGI_FORMAT_R32G32B32_UINT:             return "R32G32B32_UINT";
		case DXGI_FORMAT_R32G32B32_SINT:             return "R32G32B32_SINT";
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:      return "R16G16B16A16_TYPELESS";
		case DXGI_FORMAT_R16G16B16A16_FLOAT:         return "R16G16B16A16_FLOAT";
		case DXGI_FORMAT_R16G16B16A16_UNORM:         return "R16G16B16A16_UNORM";
		case DXGI_FORMAT_R16G16B16A16_UINT:          return "R16G16B16A16_UINT";
		case DXGI_FORMAT_R16G16B16A16_SNORM:         return "R16G16B16A16_SNORM";
		case DXGI_FORMAT_R16G16B16A16_SINT:          return "R16G16B16A16_SINT";
		case DXGI_FORMAT_R32G32_TYPELESS:            return "R32G32_TYPELESS";
		case DXGI_FORMAT_R32G32_FLOAT:               return "R32G32_FLOAT";
		case DXGI_FORMAT_R32G32_UINT:                return "R32G32_UINT";
		case DXGI_FORMAT_R32G32_SINT:                return "R32G32_SINT";
		case DXGI_FORMAT_R32G8X24_TYPELESS:          return "R32G8X24_TYPELESS";
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:       return "D32_FLOAT_S8X24_UINT";
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:   return "R32_FLOAT_X8X24_TYPELESS";
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:    return "X32_TYPELESS_G8X24_UINT";
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:       return "R10G10B10A2_TYPELESS";
		case DXGI_FORMAT_R10G10B10A2_UNORM:          return "R10G10B10A2_UNORM";
		case DXGI_FORMAT_R10G10B10A2_UINT:           return "R10G10B10A2_UINT";
		case DXGI_FORMAT_R11G11B10_FLOAT:            return "R11G11B10_FLOAT";
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:          return "R8G8B8A8_TYPELESS";
		case DXGI_FORMAT_R8G8B8A8_UNORM:             return "R8G8B8A8_UNORM";
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:        return "R8G8B8A8_UNORM_SRGB";
		case DXGI_FORMAT_R8G8B8A8_UINT:              return "R8G8B8A8_UINT";
		case DXGI_FORMAT_R8G8B8A8_SNORM:             return "R8G8B8A8_SNORM";
		case DXGI_FORMAT_R8G8B8A8_SINT:              return "R8G8B8A8_SINT";
		case DXGI_FORMAT_R16G16_TYPELESS:            return "R16G16_TYPELESS";
		case DXGI_FORMAT_R16G16_FLOAT:               return "R16G16_FLOAT";
		case DXGI_FORMAT_R16G16_UNORM:               return "R16G16_UNORM";
		case DXGI_FORMAT_R16G16_UINT:                return "R16G16_UINT";
		case DXGI_FORMAT_R16G16_SNORM:               return "R16G16_SNORM";
		case DXGI_FORMAT_R16G16_SINT:                return "R16G16_SINT";
		case DXGI_FORMAT_R32_TYPELESS:               return "R32_TYPELESS";
		case DXGI_FORMAT_D32_FLOAT:                  return "D32_FLOAT";
		case DXGI_FORMAT_R32_FLOAT:                  return "R32_FLOAT";
		case DXGI_FORMAT_R32_UINT:                   return "R32_UINT";
		case DXGI_FORMAT_R32_SINT:                   return "R32_SINT";
		case DXGI_FORMAT_R24G8_TYPELESS:             return "R24G8_TYPELESS";
		case DXGI_FORMAT_D24_UNORM_S8_UINT:          return "D24_UNORM_S8_UINT";
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:      return "R24_UNORM_X8_TYPELESS";
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:       return "X24_TYPELESS_G8_UINT";
		case DXGI_FORMAT_R8G8_TYPELESS:              return "R8G8_TYPELESS";
		case DXGI_FORMAT_R8G8_UNORM:                 return "R8G8_UNORM";
		case DXGI_FORMAT_R8G8_UINT:                  return "R8G8_UINT";
		case DXGI_FORMAT_R8G8_SNORM:                 return "R8G8_SNORM";
		case DXGI_FORMAT_R8G8_SINT:                  return "R8G8_SINT";
		case DXGI_FORMAT_R16_TYPELESS:               return "R16_TYPELESS";
		case DXGI_FORMAT_R16_FLOAT:                  return "R16_FLOAT";
		case DXGI_FORMAT_D16_UNORM:                  return "D16_UNORM";
		case DXGI_FORMAT_R16_UNORM:                  return "R16_UNORM";
		case DXGI_FORMAT_R16_UINT:                   return "R16_UINT";
		case DXGI_FORMAT_R16_SNORM:                  return "R16_SNORM";
		case DXGI_FORMAT_R16_SINT:                   return "R16_SINT";
		case DXGI_FORMAT_R8_TYPELESS:                return "R8_TYPELESS";
		case DXGI_FORMAT_R8_UNORM:                   return "R8_UNORM";
		case DXGI_FORMAT_R8_UINT:                    return "R8_UINT";
		case DXGI_FORMAT_R8_SNORM:                   return "R8_SNORM";
		case DXGI_FORMAT_R8_SINT:                    return "R8_SINT";
		case DXGI_FORMAT_A8_UNORM:                   return "A8_UNORM";
		case DXGI_FORMAT_R1_UNORM:                   return "R1_UNORM";
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:         return "R9G9B9E5_SHAREDEXP";
		case DXGI_FORMAT_R8G8_B8G8_UNORM:            return "R8G8_B8G8_UNORM";
		case DXGI_FORMAT_G8R8_G8B8_UNORM:            return "G8R8_G8B8_UNORM";
		case DXGI_FORMAT_BC1_TYPELESS:               return "BC1_TYPELESS";
		case DXGI_FORMAT_BC1_UNORM:                  return "BC1_UNORM";
		case DXGI_FORMAT_BC1_UNORM_SRGB:             return "BC1_UNORM_SRGB";
		case DXGI_FORMAT_BC2_TYPELESS:               return "BC2_TYPELESS";
		case DXGI_FORMAT_BC2_UNORM:                  return "BC2_UNORM";
		case DXGI_FORMAT_BC2_UNORM_SRGB:             return "BC2_UNORM_SRGB";
		case DXGI_FORMAT_BC3_TYPELESS:               return "BC3_TYPELESS";
		case DXGI_FORMAT_BC3_UNORM:                  return "BC3_UNORM";
		case DXGI_FORMAT_BC3_UNORM_SRGB:             return "BC3_UNORM_SRGB";
		case DXGI_FORMAT_BC4_TYPELESS:               return "BC4_TYPELESS";
		case DXGI_FORMAT_BC4_UNORM:                  return "BC4_UNORM";
		case DXGI_FORMAT_BC4_SNORM:                  return "BC4_SNORM";
		case DXGI_FORMAT_BC5_TYPELESS:               return "BC5_TYPELESS";
		case DXGI_FORMAT_BC5_UNORM:                  return "BC5_UNORM";
		case DXGI_FORMAT_BC5_SNORM:                  return "BC5_SNORM";
		case DXGI_FORMAT_B5G6R5_UNORM:               return "B5G6R5_UNORM";
		case DXGI_FORMAT_B5G5R5A1_UNORM:             return "B5G5R5A1_UNORM";
		case DXGI_FORMAT_B8G8R8A8_UNORM:             return "B8G8R8A8_UNORM";
		case DXGI_FORMAT_B8G8R8X8_UNORM:             return "B8G8R8X8_UNORM";
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return "R10G10B10_XR_BIAS_A2_UNORM";
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:          return "B8G8R8A8_TYPELESS";
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:        return "B8G8R8A8_UNORM_SRGB";
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:          return "B8G8R8X8_TYPELESS";
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:        return "B8G8R8X8_UNORM_SRGB";
		case DXGI_FORMAT_BC6H_TYPELESS:              return "BC6H_TYPELESS";
		case DXGI_FORMAT_BC6H_UF16:                  return "BC6H_UF16";
		case DXGI_FORMAT_BC6H_SF16:                  return "BC6H_SF16";
		case DXGI_FORMAT_BC7_TYPELESS:               return "BC7_TYPELESS";
		case DXGI_FORMAT_BC7_UNORM:                  return "BC7_UNORM";
		case DXGI_FORMAT_BC7_UNORM_SRGB:             return "BC7_UNORM_SRGB";
		case DXGI_FORMAT_AYUV:                       return "AYUV";
		case DXGI_FORMAT_Y410:                       return "Y410";
		case DXGI_FORMAT_Y416:                       return "Y416";
		case DXGI_FORMAT_NV12:                       return "NV12";
		case DXGI_FORMAT_P010:                       return "P010";
		case DXGI_FORMAT_P016:                       return "P016";
		case DXGI_FORMAT_420_OPAQUE:                 return "420_OPAQUE";
		case DXGI_FORMAT_YUY2:                       return "YUY2";
		case DXGI_FORMAT_Y210:                       return "Y210";
		case DXGI_FORMAT_Y216:                       return "Y216";
		case DXGI_FORMAT_NV11:                       return "NV11";
		case DXGI_FORMAT_AI44:                       return "AI44";
		case DXGI_FORMAT_IA44:                       return "IA44";
		case DXGI_FORMAT_P8:                         return "P8";
		case DXGI_FORMAT_A8P8:                       return "A8P8";
		case DXGI_FORMAT_B4G4R4A4_UNORM:             return "B4G4R4A4_UNORM";
		case DXGI_FORMAT_P208:                       return "P208";
		case DXGI_FORMAT_V208:                       return "V208";
		case DXGI_FORMAT_V408:                       return "V408";
		case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE: return "SMAPLER_FEEDBACK_MIN_MIP_OPAQUE";
		case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE: return "SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE";
		default: return "INVALID";
	};
}
static const char *dxt10FormatDesc(dxt10FormatT f) {
	switch (f) {
		case DXGI_FORMAT_UNKNOWN:                    return "The format is not known.";
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:      return "A four-component, 128-bit typeless format that supports 32 bits per channel including alpha.";
		case DXGI_FORMAT_R32G32B32A32_FLOAT:         return "A four-component, 128-bit floating-point format that supports 32 bits per channel including alpha.";
		case DXGI_FORMAT_R32G32B32A32_UINT:          return "A four-component, 128-bit unsigned-integer format that supports 32 bits per channel including alpha.";
		case DXGI_FORMAT_R32G32B32A32_SINT:          return "A four-component, 128-bit signed-integer format that supports 32 bits per channel including alpha.";
		case DXGI_FORMAT_R32G32B32_TYPELESS:         return "A three-component, 96-bit typeless format that supports 32 bits per color channel.";
		case DXGI_FORMAT_R32G32B32_FLOAT:            return "A three-component, 96-bit floating-point format that supports 32 bits per color channel.";
		case DXGI_FORMAT_R32G32B32_UINT:             return "A three-component, 96-bit unsigned-integer format that supports 32 bits per color channel.";
		case DXGI_FORMAT_R32G32B32_SINT:             return "A three-component, 96-bit signed-integer format that supports 32 bits per color channel.";
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:      return "A four-component, 64-bit typeless format that supports 16 bits per channel including alpha.";
		case DXGI_FORMAT_R16G16B16A16_FLOAT:         return "A four-component, 64-bit floating-point format that supports 16 bits per channel including alpha.";
		case DXGI_FORMAT_R16G16B16A16_UNORM:         return "A four-component, 64-bit unsigned-normalized-integer format that supports 16 bits per channel including alpha.";
		case DXGI_FORMAT_R16G16B16A16_UINT:          return "A four-component, 64-bit unsigned-integer format that supports 16 bits per channel including alpha.";
		case DXGI_FORMAT_R16G16B16A16_SNORM:         return "A four-component, 64-bit signed-normalized-integer format that supports 16 bits per channel including alpha.";
		case DXGI_FORMAT_R16G16B16A16_SINT:          return "A four-component, 64-bit signed-integer format that supports 16 bits per channel including alpha.";
		case DXGI_FORMAT_R32G32_TYPELESS:            return "A two-component, 64-bit typeless format that supports 32 bits for the red channel and 32 bits for the green channel.";
		case DXGI_FORMAT_R32G32_FLOAT:               return "A two-component, 64-bit floating-point format that supports 32 bits for the red channel and 32 bits for the green channel.";
		case DXGI_FORMAT_R32G32_UINT:                return "A two-component, 64-bit unsigned-integer format that supports 32 bits for the red channel and 32 bits for the green channel.";
		case DXGI_FORMAT_R32G32_SINT:                return "A two-component, 64-bit signed-integer format that supports 32 bits for the red channel and 32 bits for the green channel.";
		case DXGI_FORMAT_R32G8X24_TYPELESS:          return "A two-component, 64-bit typeless format that supports 32 bits for the red channel, 8 bits for the green channel, and 24 bits are unused.";
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:       return "A 32-bit floating-point component, and two unsigned-integer components (with an additional 32 bits). This format supports 32-bit depth, 8-bit stencil, and 24 bits are unused.";
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:   return "A 32-bit floating-point component, and two typeless components (with an additional 32 bits). This format supports 32-bit red channel, 8 bits are unused, and 24 bits are unused.";
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:    return "A 32-bit typeless component, and two unsigned-integer components (with an additional 32 bits). This format has 32 bits unused, 8 bits for green channel, and 24 bits are unused.";
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:       return "A four-component, 32-bit typeless format that supports 10 bits for each color and 2 bits for alpha.";
		case DXGI_FORMAT_R10G10B10A2_UNORM:          return "A four-component, 32-bit unsigned-normalized-integer format that supports 10 bits for each color and 2 bits for alpha.";
		case DXGI_FORMAT_R10G10B10A2_UINT:           return "A four-component, 32-bit unsigned-integer format that supports 10 bits for each color and 2 bits for alpha.";
		case DXGI_FORMAT_R11G11B10_FLOAT:            return "Three partial-precision floating-point numbers encoded into a single 32-bit value.";
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:          return "A four-component, 32-bit typeless format that supports 8 bits per channel including alpha.";
		case DXGI_FORMAT_R8G8B8A8_UNORM:             return "A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha.";
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:        return "A four-component, 32-bit unsigned-normalized integer sRGB format that supports 8 bits per channel including alpha.";
		case DXGI_FORMAT_R8G8B8A8_UINT:              return "A four-component, 32-bit unsigned-integer format that supports 8 bits per channel including alpha.";
		case DXGI_FORMAT_R8G8B8A8_SNORM:             return "A four-component, 32-bit signed-normalized-integer format that supports 8 bits per channel including alpha.";
		case DXGI_FORMAT_R8G8B8A8_SINT:              return "A four-component, 32-bit signed-integer format that supports 8 bits per channel including alpha.";
		case DXGI_FORMAT_R16G16_TYPELESS:            return "A two-component, 32-bit typeless format that supports 16 bits for the red channel and 16 bits for the green channel.";
		case DXGI_FORMAT_R16G16_FLOAT:               return "A two-component, 32-bit floating-point format that supports 16 bits for the red channel and 16 bits for the green channel.";
		case DXGI_FORMAT_R16G16_UNORM:               return "A two-component, 32-bit unsigned-normalized-integer format that supports 16 bits each for the green and red channels.";
		case DXGI_FORMAT_R16G16_UINT:                return "A two-component, 32-bit unsigned-integer format that supports 16 bits for the red channel and 16 bits for the green channel.";
		case DXGI_FORMAT_R16G16_SNORM:               return "A two-component, 32-bit signed-normalized-integer format that supports 16 bits for the red channel and 16 bits for the green channel.";
		case DXGI_FORMAT_R16G16_SINT:                return "A two-component, 32-bit signed-integer format that supports 16 bits for the red channel and 16 bits for the green channel.";
		case DXGI_FORMAT_R32_TYPELESS:               return "A single-component, 32-bit typeless format that supports 32 bits for the red channel.";
		case DXGI_FORMAT_D32_FLOAT:                  return "A single-component, 32-bit floating-point format that supports 32 bits for depth.";
		case DXGI_FORMAT_R32_FLOAT:                  return "A single-component, 32-bit floating-point format that supports 32 bits for the red channel.";
		case DXGI_FORMAT_R32_UINT:                   return "A single-component, 32-bit unsigned-integer format that supports 32 bits for the red channel.";
		case DXGI_FORMAT_R32_SINT:                   return "A single-component, 32-bit signed-integer format that supports 32 bits for the red channel.";
		case DXGI_FORMAT_R24G8_TYPELESS:             return "A two-component, 32-bit typeless format that supports 24 bits for the red channel and 8 bits for the green channel.";
		case DXGI_FORMAT_D24_UNORM_S8_UINT:          return "A 32-bit z-buffer format that supports 24 bits for depth and 8 bits for stencil.";
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:      return "A 32-bit format, that contains a 24 bit, single-component, unsigned-normalized integer, with an additional typeless 8 bits. This format has 24 bits red channel and 8 bits unused.";
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:       return "A 32-bit format, that contains a 24 bit, single-component, typeless format,  with an additional 8 bit unsigned integer component. This format has 24 bits unused and 8 bits green channel.";
		case DXGI_FORMAT_R8G8_TYPELESS:              return "A two-component, 16-bit typeless format that supports 8 bits for the red channel and 8 bits for the green channel.";
		case DXGI_FORMAT_R8G8_UNORM:                 return "A two-component, 16-bit unsigned-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel.";
		case DXGI_FORMAT_R8G8_UINT:                  return "A two-component, 16-bit unsigned-integer format that supports 8 bits for the red channel and 8 bits for the green channel.";
		case DXGI_FORMAT_R8G8_SNORM:                 return "A two-component, 16-bit signed-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel.";
		case DXGI_FORMAT_R8G8_SINT:                  return "A two-component, 16-bit signed-integer format that supports 8 bits for the red channel and 8 bits for the green channel.";
		case DXGI_FORMAT_R16_TYPELESS:               return "A single-component, 16-bit typeless format that supports 16 bits for the red channel.";
		case DXGI_FORMAT_R16_FLOAT:                  return "A single-component, 16-bit floating-point format that supports 16 bits for the red channel.";
		case DXGI_FORMAT_D16_UNORM:                  return "A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for depth.";
		case DXGI_FORMAT_R16_UNORM:                  return "A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for the red channel.";
		case DXGI_FORMAT_R16_UINT:                   return "A single-component, 16-bit unsigned-integer format that supports 16 bits for the red channel.";
		case DXGI_FORMAT_R16_SNORM:                  return "A single-component, 16-bit signed-normalized-integer format that supports 16 bits for the red channel.";
		case DXGI_FORMAT_R16_SINT:                   return "A single-component, 16-bit signed-integer format that supports 16 bits for the red channel.";
		case DXGI_FORMAT_R8_TYPELESS:                return "A single-component, 8-bit typeless format that supports 8 bits for the red channel.";
		case DXGI_FORMAT_R8_UNORM:                   return "A single-component, 8-bit unsigned-normalized-integer format that supports 8 bits for the red channel.";
		case DXGI_FORMAT_R8_UINT:                    return "A single-component, 8-bit unsigned-integer format that supports 8 bits for the red channel.";
		case DXGI_FORMAT_R8_SNORM:                   return "A single-component, 8-bit signed-normalized-integer format that supports 8 bits for the red channel.";
		case DXGI_FORMAT_R8_SINT:                    return "A single-component, 8-bit signed-integer format that supports 8 bits for the red channel.";
		case DXGI_FORMAT_A8_UNORM:                   return "A single-component, 8-bit unsigned-normalized-integer format for alpha only.";
		case DXGI_FORMAT_R1_UNORM:                   return "A single-component, 1-bit unsigned-normalized integer format that supports 1 bit for the red channel. ².";
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:         return "Three partial-precision floating-point numbers encoded into a single 32-bit value all sharing the same 5-bit exponent.";
		case DXGI_FORMAT_R8G8_B8G8_UNORM:            return "A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format is analogous to the UYVY format.";
		case DXGI_FORMAT_G8R8_G8B8_UNORM:            return "A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format is analogous to the YUY2 format.";
		case DXGI_FORMAT_BC1_TYPELESS:               return "Four-component typeless block-compression format.";
		case DXGI_FORMAT_BC1_UNORM:                  return "Four-component block-compression format.";
		case DXGI_FORMAT_BC1_UNORM_SRGB:             return "Four-component block-compression format for sRGB data.";
		case DXGI_FORMAT_BC2_TYPELESS:               return "Four-component typeless block-compression format.";
		case DXGI_FORMAT_BC2_UNORM:                  return "Four-component block-compression format.";
		case DXGI_FORMAT_BC2_UNORM_SRGB:             return "Four-component block-compression format for sRGB data.";
		case DXGI_FORMAT_BC3_TYPELESS:               return "Four-component typeless block-compression format.";
		case DXGI_FORMAT_BC3_UNORM:                  return "Four-component block-compression format.";
		case DXGI_FORMAT_BC3_UNORM_SRGB:             return "Four-component block-compression format for sRGB data.";
		case DXGI_FORMAT_BC4_TYPELESS:               return "One-component typeless block-compression format.";
		case DXGI_FORMAT_BC4_UNORM:                  return "One-component block-compression format.";
		case DXGI_FORMAT_BC4_SNORM:                  return "One-component block-compression format.";
		case DXGI_FORMAT_BC5_TYPELESS:               return "Two-component typeless block-compression format.";
		case DXGI_FORMAT_BC5_UNORM:                  return "Two-component block-compression format.";
		case DXGI_FORMAT_BC5_SNORM:                  return "Two-component block-compression format.";
		case DXGI_FORMAT_B5G6R5_UNORM:               return "A three-component, 16-bit unsigned-normalized-integer format that supports 5 bits for blue, 6 bits for green, and 5 bits for red.";
		case DXGI_FORMAT_B5G5R5A1_UNORM:             return "A four-component, 16-bit unsigned-normalized-integer format that supports 5 bits for each color channel and 1-bit alpha.";
		case DXGI_FORMAT_B8G8R8A8_UNORM:             return "A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8-bit alpha.";
		case DXGI_FORMAT_B8G8R8X8_UNORM:             return "A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8 bits unused.";
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return "A four-component, 32-bit 2.8-biased fixed-point format that supports 10 bits for each color channel and 2-bit alpha.";
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:          return "A four-component, 32-bit typeless format that supports 8 bits for each channel including alpha.";
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:        return "A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each channel including alpha.";
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:          return "A four-component, 32-bit typeless format that supports 8 bits for each color channel, and 8 bits are unused.";
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:        return "A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each color channel, and 8 bits are unused.";
		case DXGI_FORMAT_BC6H_TYPELESS:              return "A typeless block-compression format.";
		case DXGI_FORMAT_BC6H_UF16:                  return "A block-compression format.";
		case DXGI_FORMAT_BC6H_SF16:                  return "A block-compression format.";
		case DXGI_FORMAT_BC7_TYPELESS:               return "A typeless block-compression format.";
		case DXGI_FORMAT_BC7_UNORM:                  return "A block-compression format.";
		case DXGI_FORMAT_BC7_UNORM_SRGB:             return "A block-compression format.";
		case DXGI_FORMAT_AYUV:                       return "Most common YUV 4:4:4 video resource format.";
		case DXGI_FORMAT_Y410:                       return "10-bit per channel packed YUV 4:4:4 video resource format.";
		case DXGI_FORMAT_Y416:                       return "16-bit per channel packed YUV 4:4:4 video resource format.";
		case DXGI_FORMAT_NV12:                       return "Most common YUV 4:2:0 video resource format.";
		case DXGI_FORMAT_P010:                       return "10-bit per channel planar YUV 4:2:0 video resource format.";
		case DXGI_FORMAT_P016:                       return "16-bit per channel planar YUV 4:2:0 video resource format.";
		case DXGI_FORMAT_420_OPAQUE:                 return "8-bit per channel planar YUV 4:2:0 video resource format.";
		case DXGI_FORMAT_YUY2:                       return "Most common YUV 4:2:2 video resource format.";
		case DXGI_FORMAT_Y210:                       return "10-bit per channel packed YUV 4:2:2 video resource format.";
		case DXGI_FORMAT_Y216:                       return "16-bit per channel packed YUV 4:2:2 video resource format.";
		case DXGI_FORMAT_NV11:                       return "Most common planar YUV 4:1:1 video resource format.";
		case DXGI_FORMAT_AI44:                       return "4-bit palletized YUV format that is commonly used for DVD subpicture.";
		case DXGI_FORMAT_IA44:                       return "4-bit palletized YUV format that is commonly used for DVD subpicture.";
		case DXGI_FORMAT_P8:                         return "8-bit palletized format that is used for palletized RGB data when the processor processes ISDB-T data and for palletized YUV data when the processor processes BluRay data.";
		case DXGI_FORMAT_A8P8:                       return "8-bit palletized format with 8 bits of alpha that is used for palletized YUV data when the processor processes BluRay data.";
		case DXGI_FORMAT_B4G4R4A4_UNORM:             return "A four-component, 16-bit unsigned-normalized integer format that supports 4 bits for each channel including alpha.";
		case DXGI_FORMAT_P208:                       return "A video format; an 8-bit version of a hybrid planar 4:2:2 format.";
		case DXGI_FORMAT_V208:                       return "An 8 bit YCbCrA 4:4 rendering format.";
		case DXGI_FORMAT_V408:                       return "An 8 bit YCbCrA 4:4:4:4 rendering format.";
		case DXGI_FORMAT_FORCE_UINT: return "Forces this enumeration to compile to 32 bits in size.";
		default: return "";
	};
}
static const char *dxt10DimensionStr(dxt10DimensionT d) {
	switch (d) {
		case DDS_DIMENSION_TEXTURE_1D: return "TEXTURE_1D";
		case DDS_DIMENSION_TEXTURE_2D: return "TEXTURE_2D";
		case DDS_DIMENSION_TEXTURE_3D: return "TEXTURE_3D";
		default: return "INVALID";
	}
}
static const char *dxt10ResourceMiscStr(dxt10ResourceMiscT r) {
	switch (r) {
		case DDS_RESOURCE_MISC_TEXTURECUBE: return "MISC_TEXTURECUBE";
		default: return "INVALID";
	}
}
static const char *dxt10AlphaModeStr(dxt10AlphaModeT a) {
	switch (a) {
		case DDS_ALPHA_MODE_UNKNOWN:       return "ALPHA_UNKNOWN";
		case DDS_ALPHA_MODE_STRAIGHT:      return "ALPHA_STRAIGHT";
		case DDS_ALPHA_MODE_PREMULTIPLIED: return "ALPHA_PREMULTIPLIED";
		case DDS_ALPHA_MODE_OPAQUE:        return "ALPHA_OPAQUE";
		case DDS_ALPHA_MODE_CUSTOM:        return "ALPHA_CUSTOM";
		default: return "INVALID";
	}
}

void
dxt10PrintHeader(ddsHeaderDXT10T hd)
{
	PD_LOG_OUT("DDS DXT10 Header:");
	PD_LOG_OUT("    Format:     0x%08X %s", hd.format, dxt10FormatStr(hd.format));
	PD_LOG_OUT("    Dimension:  0x%08X %s", hd.dimension, dxt10DimensionStr(hd.dimension));
	PD_LOG_OUT("    Misc Flag:  0x%08X %s", hd.miscflag, dxt10ResourceMiscStr(hd.miscflag));
	PD_LOG_OUT("    Array Size: %u", hd.arraysize);
	PD_LOG_OUT("    Alpha Mode: 0x%08X %s", hd.alphaflag, dxt10AlphaModeStr(hd.alphaflag));
}

#define PRINT_FLAG(fs, F, c) do { if (fs & F) { if (c) PD_LOGN_OUT("%s", " | "); PD_LOGN_OUT("%s", #F); c++; } } while(0)
static void printhdrflags(u32 flags) {
	int bf = 0;
	PRINT_FLAG(flags, DDSD_CAPS, bf);
	PRINT_FLAG(flags, DDSD_HEIGHT, bf);
	PRINT_FLAG(flags, DDSD_WIDTH, bf);
	PRINT_FLAG(flags, DDSD_PITCH, bf);
	PRINT_FLAG(flags, DDSD_PIXELFORMAT, bf);
	PRINT_FLAG(flags, DDSD_MIPMAPCOUNT, bf);
	PRINT_FLAG(flags, DDSD_LINEARSIZE, bf);
	PRINT_FLAG(flags, DDSD_DEPTH, bf);
}
static void printpfflags(u32 flags) {
	int bf = 0;
	PRINT_FLAG(flags, DDPF_ALPHAPIXELS, bf);
	PRINT_FLAG(flags, DDPF_ALPHA, bf);
	PRINT_FLAG(flags, DDPF_FOURCC, bf);
	PRINT_FLAG(flags, DDPF_RGB, bf);
	PRINT_FLAG(flags, DDPF_YUV, bf);
	PRINT_FLAG(flags, DDPF_LUMINANCE, bf);
}
static void printcaps(u32 caps) {
	int bf = 0;
	PRINT_FLAG(caps, DDSCAPS_COMPLEX, bf);
	PRINT_FLAG(caps, DDSCAPS_MIPMAP, bf);
	PRINT_FLAG(caps, DDSCAPS_TEXTURE, bf);
}
static void printcaps2(u32 caps2) {
	int bf = 0;
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP, bf);
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP_POSITIVEX, bf);
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP_NEGATIVEX, bf);
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP_POSITIVEY, bf);
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP_NEGATIVEY, bf);
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP_POSITIVEZ, bf);
	PRINT_FLAG(caps2, DDSCAPS2_CUBEMAP_NEGATIVEZ, bf);
	PRINT_FLAG(caps2, DDSCAPS2_VOLUME, bf);
}

void
ddsPrintHeader(ddsImageT dds)
{
	ddsHeaderT hd = dds.header;
	PD_LOG_OUT("DDS Header:");
	PD_LOGN_OUT("    Flags:       0x%08X ", hd.flags);
	printhdrflags(hd.flags);
	PD_LOG_OUT("");
	PD_LOG_OUT("    Width:       %u", hd.width);
	PD_LOG_OUT("    Height:      %u", hd.height);
	if (hd.flags & DDSD_PITCH)
		PD_LOG_OUT("    Pitch:       %u", hd.pitch);
	else if (hd.flags & DDSD_LINEARSIZE)
		PD_LOG_OUT("    Linear Size: %u", hd.linear_size);
	else
		PD_LOG_OUT("    Pitch (und): %u", hd.pitch);
	PD_LOG_OUT("    Depth:       %u", hd.depth);
	PD_LOG_OUT("    Mipmaps:     %u", hd.mipmaps);
	PD_LOGN_OUT("    Reserved1:   ");
	for (int i = 0; i < 11; ++i) {
		PD_LOGN_OUT("0x%08X ", hd.reserved1[i]);
	}
	PD_LOGN_OUT("'");
	for (int i = 0; i < 11; ++i) {
		PD_LOGN_OUT("%4.4s", (char *)&hd.reserved1[i]);
	}
	PD_LOGN_OUT("' ");
	PD_LOG_OUT("");
	PD_LOG_OUT("    Pixel Format:");
	PD_LOGN_OUT("        Flags:      0x%08X ", hd.ddspf.flags);
	printpfflags(hd.ddspf.flags);
	PD_LOG_OUT("");
	PD_LOG_OUT("        FCC:        0x%08X %4.4s", hd.ddspf.fourcc.id, hd.ddspf.fourcc.fourcc);
	PD_LOG_OUT("        Pixel Bits: %u", hd.ddspf.rgb_bits);
	PD_LOG_OUT("        R_Mask:     0x%08X", hd.ddspf.r_mask);
	PD_LOG_OUT("        G_Mask:     0x%08X", hd.ddspf.g_mask);
	PD_LOG_OUT("        B_Mask:     0x%08X", hd.ddspf.b_mask);
	PD_LOG_OUT("        A_Mask:     0x%08X", hd.ddspf.a_mask);
	PD_LOGN_OUT("    Caps:       0x%08X ", hd.caps);
	printcaps(hd.caps);
	PD_LOG_OUT("");
	PD_LOGN_OUT("    Caps2:      0x%08X ", hd.caps2);
	printcaps2(hd.caps2);
	PD_LOG_OUT("");
	PD_LOG_OUT("    Reserved2:  0x%08X", hd.reserved2);
	PD_LOGN_OUT("Primary Data Size:   ");
	PD_LOGDN_OUT(0, dds.meta.data_size);
	PD_LOG_OUT(" bytes");
	PD_LOGN_OUT("Secondary Data Size: ");
	PD_LOGDN_OUT(0, dds.meta.data2_size);
	PD_LOG_OUT(" bytes");
	PD_LOGN_OUT("Total Data Size:     ");
	PD_LOGDN_OUT(0, dds.meta.data_size + dds.meta.data2_size);
	PD_LOG_OUT(" bytes");
	PD_LOGN_OUT("Total File Size:     ");
	PD_LOGDN_OUT(0, dds.meta.data_size + dds.meta.data2_size + dds.header.size + (dds.meta.mode&DDMM_DXT10?DDS_HEADERDXT10_SIZE:0) + 4);
	PD_LOG_OUT(" bytes");
	if (dds.meta.mode & DDMM_DXT10) {
		dxt10PrintHeader(dds.header10);
	}
}
