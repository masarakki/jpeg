require "mkmf"

if have_header('jpeglib.h')
  create_makefile('jpeg')
end
