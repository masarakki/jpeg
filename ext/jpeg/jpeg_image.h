#ifndef RB_JPEG_JPEG_H
#define RB_JPEG_JPEG_H 1
#include <jpeglib.h>
#include "jpeg.h"
#include "ruby.h"

struct rb_jpeg_image {
    struct jpeg_decompress_struct *read;
    struct jpeg_error_mgr *error;
};

void Init_jpeg_image();

#endif
