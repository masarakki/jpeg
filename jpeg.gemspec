# frozen_string_literal: true

lib = File.expand_path('lib', __dir__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'jpeg/version'

Gem::Specification.new do |spec|
  spec.name          = 'jpeg'
  spec.version       = Jpeg::VERSION
  spec.authors       = ['masarakki']
  spec.email         = ['masaki182@gmail.com']
  spec.extensions    = ['ext/jpeg/extconf.rb']
  spec.summary       = 'libjpeg wrapper for ruby'
  spec.description   = 'libjpeg wrapper for ruby'
  spec.homepage      = 'http://github.com/masarakki/jpeg'
  spec.license       = 'MIT'

  spec.required_ruby_version = '>= 2.5.0'
  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']

  spec.metadata['rubygems_mfa_required'] = 'true'
end
