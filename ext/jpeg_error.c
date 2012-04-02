#include "jpeg.h"
#include "jpeg_error.h"
#include "ruby.h"

extern VALUE Jpeg;
VALUE Jpeg_Error;

void Init_jpeg_error() {
    Jpeg_Error = rb_define_class_under(Jpeg, "Error", rb_eStandardError);
}
