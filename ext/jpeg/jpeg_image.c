#include <stdio.h>
#include <jpeglib.h>
#include "jpeg_image.h"
#include "jpeg_error.h"

extern VALUE rb_mJpeg;
VALUE rb_cJpegImage;

static VALUE jpeg_image_s_open(int argc, VALUE *argv, VALUE sef);
static VALUE jpeg_image_alloc(VALUE klass);
static void jpeg_image_mark(struct rb_jpeg_image *p);
static void jpeg_image_free(struct rb_jpeg_image *p);
static VALUE jpeg_image_width(VALUE self);
static VALUE jpeg_image_height(VALUE self);
static VALUE jpeg_image_size(VALUE self);
static VALUE jpeg_image_color_info(VALUE self);

extern VALUE rb_eJpegError;

void Init_jpeg_image(void) {
    rb_cJpegImage = rb_define_class_under(rb_mJpeg, "Image", rb_cObject);
    rb_define_alloc_func(rb_cJpegImage, jpeg_image_alloc);
    rb_define_singleton_method(rb_cJpegImage, "open", jpeg_image_s_open, -1);
    rb_define_method(rb_cJpegImage, "width", jpeg_image_width, 0);
    rb_define_method(rb_cJpegImage, "height", jpeg_image_height, 0);
    rb_define_method(rb_cJpegImage, "size", jpeg_image_size, 0);
    rb_define_method(rb_cJpegImage, "color_info", jpeg_image_color_info, 0);
}

void jpeg_image_exit(j_common_ptr jpeg) {
    char buffer[JMSG_LENGTH_MAX];
    jpeg->err->format_message(jpeg, buffer);
    rb_raise(rb_eJpegError, "%s", buffer);
}

static VALUE jpeg_image_alloc(VALUE klass) {
    struct rb_jpeg_image *jpeg = ALLOC(struct rb_jpeg_image);

    jpeg->read = (void *)ALLOC(struct jpeg_decompress_struct);
    jpeg->error = (void *)ALLOC(struct jpeg_error_mgr);
    jpeg->read->err = jpeg_std_error(jpeg->error);
    jpeg->error->error_exit = jpeg_image_exit;
    jpeg_create_decompress(jpeg->read);

    return Data_Wrap_Struct(klass, jpeg_image_mark, jpeg_image_free, jpeg);
}

static void jpeg_image_mark(struct rb_jpeg_image *p) {

}

static void jpeg_image_free(struct rb_jpeg_image *p) {
    if (p->read) {
        jpeg_destroy_decompress(p->read);
        xfree(p->read);
    }
    if (p->error) {
        xfree(p->error);
    }
    xfree(p);
}

static VALUE jpeg_image_s_open(int argc, VALUE *argv, VALUE self) {
    VALUE path;
    VALUE jpeg;
    struct rb_jpeg_image *p_jpeg;
    FILE *fp;
    char *filename;
    rb_scan_args(argc, argv, "1", &path);
    Check_Type(path, T_STRING);

    jpeg = rb_funcall(rb_cJpegImage, rb_intern("new"), 0);
    Data_Get_Struct(jpeg, struct rb_jpeg_image, p_jpeg);
    filename = StringValuePtr(path);

    if ((fp = fopen(filename, "rb")) == NULL) {
        rb_raise(rb_eJpegError, "Open file failed: %s", filename);
    }
    jpeg_stdio_src(p_jpeg->read, fp);

    jpeg_read_header(p_jpeg->read, TRUE);
    jpeg_start_decompress(p_jpeg->read);
    fclose(fp);
    return jpeg;
}

static VALUE jpeg_image_width(VALUE self) {
    struct rb_jpeg_image *p_jpeg;
    Data_Get_Struct(self, struct rb_jpeg_image, p_jpeg);
    return rb_int_new(p_jpeg->read->output_width);
}

static VALUE jpeg_image_height(VALUE self) {
    struct rb_jpeg_image *p_jpeg;
    Data_Get_Struct(self, struct rb_jpeg_image, p_jpeg);
    return rb_int_new(p_jpeg->read->output_height);
}

static VALUE jpeg_image_size(VALUE self) {
    struct rb_jpeg_image *p_jpeg;
    VALUE array;
    Data_Get_Struct(self, struct rb_jpeg_image, p_jpeg);

    array = rb_ary_new();
    rb_ary_push(array, rb_int_new(p_jpeg->read->output_width));
    rb_ary_push(array, rb_int_new(p_jpeg->read->output_height));

    return array;
}

static VALUE jpeg_image_color_info(VALUE self) {
    struct rb_jpeg_image *p_jpeg;

    Data_Get_Struct(self, struct rb_jpeg_image, p_jpeg);
    return ID2SYM(rb_intern( p_jpeg->read->out_color_components == 3 ? "rgb" : "gray" ));
}
