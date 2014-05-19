#include "jpeg.h"
#include "jpeg_error.h"
#include "ruby.h"

extern VALUE rb_mJpeg;
VALUE rb_eJpegError;

void Init_jpeg_error() {
    rb_eJpegError = rb_define_class_under(rb_mJpeg, "Error", rb_eStandardError);
}
