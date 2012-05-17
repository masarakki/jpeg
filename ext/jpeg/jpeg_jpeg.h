#ifndef __JPEG_JPEG_
#define __JPEG_JPEG_
#include <jpeglib.h>
#include "jpeg.h"
#include "ruby.h"

struct jpeg_jpeg {
    struct jpeg_decompress_struct *read;
    struct jpeg_error_mgr *error;
};

void Init_jpeg_jpeg();

#endif
