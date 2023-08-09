# frozen_string_literal: true

$LOAD_PATH.unshift File.expand_path('../lib', __dir__)
require 'jpeg'
require 'pry'
require 'rspec/its'

def sample_file_path(file)
  File.join(File.dirname(__FILE__), 'samples', file)
end
