#include "dds_loader.h"

int
dds_load_to_image(Image *const img, const brrstringr_t *const file)
{
	if (!img || !file)
		return 1;
	/* TODO load image MYSELF then pass that to raylib
	 * Raylib's dds image loading is VERY imperfect, and rather finickey */
	Image I = LoadImage(file->cstr);
	if (!I.data) {
		return 1;
	}
	I.mipmaps = 1;
	if (I.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8) {
		// Gotta swap RED and BLUE channels on uncompressed, 24-bit RGB DDS files specifically (for some reason)
		char *id = I.data;
		for (int i = 0; i < I.width * I.height * 3; i += 3) {
			char b = id[i];
			id[i] = id[i+2];
			id[i+2]=b;
		}
	}
	*img = I;
	return 0;
}
