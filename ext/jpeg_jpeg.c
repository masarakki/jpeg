#include <stdio.h>
#include <jpeglib.h>
#include "jpeg_jpeg.h"

VALUE Jpeg;

void Init_jpeg_jpeg() {
    Jpeg = rb_define_module("Jpeg");
}
