#ifndef DDS_H
#define DDS_H

#include <raylib.h>

#include <brrtools/brrstringr.h>

int
dds_load_to_image(Image *const img, const brrstringr_t *const file);

#endif /* DDS_H */
