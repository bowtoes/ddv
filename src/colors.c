static const char pix_white[] = { 255 };
static const Image img_white = {
	.width = 1, .height = 1, .mipmaps = 1,
	.format = RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE,
	.data = pix_white,
};
static const char pix_black[] = { 0 };
static const Image img_black = {
	.width = 1, .height = 1, .mipmaps = 1,
	.format = RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE,
	.data = pix_black,
};
static const char pix_checker[] = {
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
};
static const Image img_checker = {
	.width = 16, .height = 16, .mipmaps = 1,
	.format = RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE,
	.data = pix_checker,
};
