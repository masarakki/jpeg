#include <stdio.h>
#include <jpeglib.h>
#include "jpeg_image.h"
#include "jpeg_error.h"

extern VALUE rb_mJpeg;
VALUE rb_cJpegImage;

static VALUE jpeg_image_s_open(int argc, VALUE *argv, VALUE sef);
static VALUE jpeg_image_s_open_buffer(int argc, VALUE *argv, VALUE sef);
static VALUE jpeg_image_alloc(VALUE klass);
static void jpeg_image_mark(struct rb_jpeg_image *p);
static void jpeg_image_free(struct rb_jpeg_image *p);
static VALUE jpeg_image_size(VALUE self);
static VALUE jpeg_image_raw_data(VALUE self);

extern VALUE rb_eJpegError;

void Init_jpeg_image(void) {
    rb_cJpegImage = rb_define_class_under(rb_mJpeg, "Image", rb_cObject);
    rb_define_alloc_func(rb_cJpegImage, jpeg_image_alloc);
    rb_define_singleton_method(rb_cJpegImage, "open", jpeg_image_s_open, -1);
    rb_define_singleton_method(rb_cJpegImage, "open_buffer", jpeg_image_s_open_buffer, -1);
    rb_attr(rb_cJpegImage, rb_intern("width"), 1, 0, 0);
    rb_attr(rb_cJpegImage, rb_intern("height"), 1, 0, 0);
    rb_attr(rb_cJpegImage, rb_intern("color_info"), 1, 0, 0);

    rb_define_method(rb_cJpegImage, "size", jpeg_image_size, 0);
    rb_define_method(rb_cJpegImage, "raw_data", jpeg_image_raw_data, 0);
}

void jpeg_image_exit(j_common_ptr jpeg) {
    char buffer[JMSG_LENGTH_MAX];
    jpeg->err->format_message(jpeg, buffer);
    rb_raise(rb_eJpegError, "%s", buffer);
}

static VALUE jpeg_image_alloc(VALUE klass) {
    struct rb_jpeg_image *jpeg = ALLOC(struct rb_jpeg_image);

    jpeg->fp = NULL;
    jpeg->read = (void *)ALLOC(struct jpeg_decompress_struct);
    jpeg->error = (void *)ALLOC(struct jpeg_error_mgr);
    jpeg->read->err = jpeg_std_error(jpeg->error);
    jpeg->error->error_exit = jpeg_image_exit;

    return Data_Wrap_Struct(klass, jpeg_image_mark, jpeg_image_free, jpeg);
}

static void jpeg_image_mark(struct rb_jpeg_image *p) {

}

static void jpeg_image_free(struct rb_jpeg_image *p) {
    if (p->read) {
        xfree(p->read);
    }
    if (p->error) {
        xfree(p->error);
    }
    if (p->fp) {
        fclose(p->fp);
    }
    xfree(p);
}

static void jpeg_image_s_set_read_source(struct rb_jpeg_image *p_jpeg) {

    if (p_jpeg->filename) {

        if ((p_jpeg->fp = fopen(p_jpeg->filename, "rb")) == NULL) {
            rb_raise(rb_eJpegError, "Open file failed: %s", p_jpeg->filename);
        }

    } else {

#if JPEG_LIB_VERSION >= 80
        jpeg_mem_src(p_jpeg->read, (unsigned char *) p_jpeg->buffer, p_jpeg->buffer_len);
#else
        if ((p_jpeg->fp = fmemopen(p_jpeg->buffer, p_jpeg->buffer_len, "rb")) == NULL) {
            rb_raise(rb_eJpegError, "Could not read jpeg from buffer");
        }
#endif

    }

    if (p_jpeg->fp) {
        jpeg_stdio_src(p_jpeg->read, p_jpeg->fp);
    }
}

static VALUE jpeg_image_s_get_image_values(char *filename, char *buffer, int64_t buffer_len, VALUE self) {
    VALUE jpeg;
    struct rb_jpeg_image *p_jpeg;

    jpeg = rb_obj_alloc(rb_cJpegImage);
    rb_obj_call_init(jpeg, 0, NULL);

    Data_Get_Struct(jpeg, struct rb_jpeg_image, p_jpeg);

    p_jpeg->filename = filename;
    p_jpeg->buffer = buffer;
    p_jpeg->buffer_len = buffer_len;

    jpeg_create_decompress(p_jpeg->read);

    jpeg_image_s_set_read_source(p_jpeg);

    jpeg_read_header(p_jpeg->read, TRUE);

    rb_iv_set(jpeg, "@width", LONG2NUM(p_jpeg->read->image_width));
    rb_iv_set(jpeg, "@height", LONG2NUM(p_jpeg->read->image_height));
    rb_iv_set(jpeg, "@color_info", ID2SYM(rb_intern( p_jpeg->read->out_color_space == JCS_GRAYSCALE ? "gray" : "rgb" )));

    jpeg_destroy_decompress(p_jpeg->read);

    if (p_jpeg->fp) {
        fclose(p_jpeg->fp);
        p_jpeg->fp = NULL;
    }

    return jpeg;
}

static VALUE jpeg_image_s_open(int argc, VALUE *argv, VALUE self) {
    VALUE path;

    rb_scan_args(argc, argv, "1", &path);
    Check_Type(path, T_STRING);

    return jpeg_image_s_get_image_values(StringValuePtr(path), NULL, 0, self);
}

static VALUE jpeg_image_s_open_buffer(int argc, VALUE *argv, VALUE self) {
    VALUE str;

    rb_scan_args(argc, argv, "1", &str);
    Check_Type(str, T_STRING);

    return jpeg_image_s_get_image_values(NULL, StringValuePtr(str), RSTRING_LEN(str), self);
}

static VALUE jpeg_image_size(VALUE self) {
    VALUE array;

    array = rb_ary_new();

    rb_ary_push(array, rb_iv_get(self, "@width"));
    rb_ary_push(array, rb_iv_get(self, "@height"));

    return array;
}

static VALUE jpeg_image_raw_data(VALUE self) {
    struct rb_jpeg_image *p_jpeg;
    VALUE matrix;
    VALUE line;
    VALUE point;
    int64_t line_size;
    int64_t i;
    JSAMPARRAY buffer;

    matrix = rb_iv_get(self, "@raw_data");

    if (RTEST(matrix)) {
        return matrix;
    }

    Data_Get_Struct(self, struct rb_jpeg_image, p_jpeg);

    jpeg_create_decompress(p_jpeg->read);

    jpeg_image_s_set_read_source(p_jpeg);

    jpeg_read_header(p_jpeg->read, TRUE);

    jpeg_start_decompress(p_jpeg->read);

    line_size = p_jpeg->read->output_width * p_jpeg->read->out_color_components;
    if ((buffer = (*p_jpeg->read->mem->alloc_sarray)((j_common_ptr) p_jpeg->read, JPOOL_IMAGE, line_size, 1)) == NULL) {
        rb_raise(rb_eJpegError, "Could not allocate memory (%ld bytes) to decode the image", line_size);
    }

    matrix = rb_ary_new();
    while (p_jpeg->read->output_scanline < p_jpeg->read->output_height) {
        jpeg_read_scanlines(p_jpeg->read, buffer , 1);

        line = rb_ary_new();
        if (p_jpeg->read->out_color_components == 3) {
            for (i = 0; i < line_size; i += 3) {
                point = rb_ary_new();
                rb_ary_push(point, rb_int_new(buffer[0][i]));
                rb_ary_push(point, rb_int_new(buffer[0][i + 1]));
                rb_ary_push(point, rb_int_new(buffer[0][i + 2]));
                rb_ary_push(line, point);
            }
        } else {
            for (i = 0; i < line_size; i++) {
                rb_ary_push(line, rb_int_new(buffer[0][i]));
            }
        }

        rb_ary_push(matrix, line);
    }
    jpeg_finish_decompress(p_jpeg->read);

    jpeg_destroy_decompress(p_jpeg->read);

    if (p_jpeg->fp) {
        fclose(p_jpeg->fp);
        p_jpeg->fp = NULL;
    }

    rb_iv_set(self, "@raw_data", matrix);

    return matrix;
}
