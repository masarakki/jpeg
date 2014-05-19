require 'tempfile'
require 'jpeg/version'
require 'jpeg/jpeg'
require 'jpeg/image'

module Jpeg
  def self.open_buffer(str)
    tmp = Tempfile::new("ruby-jpeg")
    tmp.set_encoding Encoding::BINARY if tmp.respond_to?(:set_encoding)
    tmp.puts str
    tmp.rewind
    jpeg = Jpeg::Image.open(tmp.path)
    tmp.close
    jpeg
  end

  def self.open(file)
    Jpeg::Image.open(file)
  end
end
