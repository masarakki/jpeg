require 'tempfile'
require 'jpeg.so'
class Jpeg
  def self.open_buffer(str)
    tmp = Tempfile::new("ruby-jpeg")
    tmp.puts str
    tmp.rewind
    jpeg = Jpeg.open(tmp.path)
    tmp.close
    jpeg
  end
end
