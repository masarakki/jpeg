#include "jpeg.h"
#include "jpeg_error.h"
#include "ruby.h"

extern VALUE Jpeg;
VALUE Error;

void Init_jpeg_error() {
    Error = rb_define_class_under(Jpeg, "Error", rb_eStandardError);
}
