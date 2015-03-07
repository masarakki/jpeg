require 'tempfile'
require 'jpeg/version'
require 'jpeg/jpeg'
require 'jpeg/image'

module Jpeg
  def self.open_buffer(str)
    Jpeg::Image.open_buffer(str)
  end

  def self.open(file)
    Jpeg::Image.open(file)
  end
end
