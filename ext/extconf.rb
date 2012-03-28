require "mkmf"

dir_config('jpeglib')
if have_header('jpeglib.h') and have_library('jpeg')
  create_makefile('jpeg')
end
