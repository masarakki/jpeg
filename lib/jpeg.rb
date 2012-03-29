require 'tempfile'
require 'jpeg.so'
class Jpeg
  def self.open_buffer(str)
    tmp = Tempfile::new("ruby-jpeg")
    tmp.set_encoding Encoding::BINARY if tmp.respond_to?(:set_encoding)
    tmp.puts str
    tmp.rewind
    jpeg = Jpeg.open(tmp.path)
    tmp.close
    jpeg
  end
end
