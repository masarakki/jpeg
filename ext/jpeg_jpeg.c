#include <stdio.h>
#include <jpeglib.h>
#include "jpeg_jpeg.h"
#include "jpeg_error.h"

VALUE Jpeg;

static VALUE jpeg_jpeg_s_open(int argc, VALUE *argv, VALUE sef);
static VALUE jpeg_jpeg_alloc(VALUE klass);
static void jpeg_jpeg_mark(struct jpeg_jpeg *p);
static void jpeg_jpeg_free(struct jpeg_jpeg *p);
static VALUE jpeg_jpeg_width(VALUE self);
static VALUE jpeg_jpeg_height(VALUE self);
static VALUE jpeg_jpeg_size(VALUE self);
static VALUE jpeg_jpeg_color_info(VALUE self);

extern VALUE Jpeg_Error;

void Init_jpeg_jpeg() {
    Jpeg = rb_define_class("Jpeg", rb_cObject);
    rb_define_alloc_func(Jpeg, jpeg_jpeg_alloc);
    rb_define_singleton_method(Jpeg, "open", jpeg_jpeg_s_open, -1);
    rb_define_method(Jpeg, "width", jpeg_jpeg_width, 0);
    rb_define_method(Jpeg, "height", jpeg_jpeg_height, 0);
    rb_define_method(Jpeg, "size", jpeg_jpeg_size, 0);
    rb_define_method(Jpeg, "color_info", jpeg_jpeg_color_info, 0);
}

void jpeg_jpeg_exit(j_common_ptr jpeg) {
    char buffer[JMSG_LENGTH_MAX];
    jpeg->err->format_message(jpeg, buffer);
    rb_raise(Jpeg_Error, buffer);
}

static VALUE jpeg_jpeg_alloc(VALUE klass) {
    struct jpeg_jpeg *jpeg = ALLOC(struct jpeg_jpeg);

    jpeg->read = (void *)ALLOC(struct jpeg_decompress_struct);
    jpeg->error = (void *)ALLOC(struct jpeg_error_mgr);
    jpeg->read->err = jpeg_std_error(jpeg->error);
    jpeg->error->error_exit = jpeg_jpeg_exit;
    jpeg_create_decompress(jpeg->read);

    return Data_Wrap_Struct(klass, jpeg_jpeg_mark, jpeg_jpeg_free, jpeg);
}

static void jpeg_jpeg_mark(struct jpeg_jpeg *p) {

}

static void jpeg_jpeg_free(struct jpeg_jpeg *p) {
    if (p->read) {
        jpeg_destroy_decompress(p->read);
        free(p->read);
    }
    if (p->error) {
        free(p->error);
    }
    xfree(p);
}

static VALUE jpeg_jpeg_s_open(int argc, VALUE *argv, VALUE self) {
    VALUE path;
    VALUE jpeg;
    struct jpeg_jpeg *p_jpeg;
    int errorp;
    FILE *fp;
    rb_scan_args(argc, argv, "1", &path);
    Check_Type(path, T_STRING);

    jpeg = rb_funcall(Jpeg, rb_intern("new"), 0);
    Data_Get_Struct(jpeg, struct jpeg_jpeg, p_jpeg);

    if ((fp = fopen(RSTRING_PTR(path), "rb")) == NULL) {
        rb_raise(rb_eRuntimeError, "Open file failed");
    }
    jpeg_stdio_src(p_jpeg->read, fp);

    jpeg_read_header(p_jpeg->read, TRUE);
    jpeg_start_decompress(p_jpeg->read);
    fclose(fp);
    return jpeg;
}

static VALUE jpeg_jpeg_width(VALUE self) {
    struct jpeg_jpeg *p_jpeg;
    Data_Get_Struct(self, struct jpeg_jpeg, p_jpeg);
    return rb_int_new(p_jpeg->read->output_width);
}

static VALUE jpeg_jpeg_height(VALUE self) {
    struct jpeg_jpeg *p_jpeg;
    Data_Get_Struct(self, struct jpeg_jpeg, p_jpeg);
    return rb_int_new(p_jpeg->read->output_height);
}

static VALUE jpeg_jpeg_size(VALUE self) {
    struct jpeg_jpeg *p_jpeg;
    VALUE array;
    Data_Get_Struct(self, struct jpeg_jpeg, p_jpeg);

    array = rb_ary_new();
    rb_ary_push(array, rb_int_new(p_jpeg->read->output_width));
    rb_ary_push(array, rb_int_new(p_jpeg->read->output_height));

    return array;
}

static VALUE jpeg_jpeg_color_info(VALUE self) {
    struct jpeg_jpeg *p_jpeg;

    Data_Get_Struct(self, struct jpeg_jpeg, p_jpeg);

    return ID2SYM(rb_intern( p_jpeg->read->out_color_components == 3 ? "rgb", "gray" ));
}
