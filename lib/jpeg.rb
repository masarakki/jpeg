require 'tempfile'
require 'jpeg.so'
class Jpeg
  def self.open_buffer(str)
    tmp = Tempfile::new("ruby-jpeg")
    jpeg = Jpeg.open(tmp.path)
    tmp.close
    jpeg
  end
end
