#include "jpeg.h"
#include "jpeg_jpeg.h"
#include "jpeg_error.h"

void Init_jpeg() {
    Init_jpeg_jpeg();
    Init_jpeg_error();
}
