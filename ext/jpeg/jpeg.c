#include "jpeg.h"
#include "jpeg_image.h"
#include "jpeg_error.h"

VALUE rb_mJpeg;

void
Init_jpeg(void) {
    rb_mJpeg = rb_define_module("Jpeg");
    Init_jpeg_image();
    Init_jpeg_error();
}
