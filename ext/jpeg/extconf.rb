# frozen_string_literal: true

require 'mkmf'

dir_config('jpeglib')
create_makefile('jpeg/jpeg') if have_header('jpeglib.h') && have_library('jpeg')
