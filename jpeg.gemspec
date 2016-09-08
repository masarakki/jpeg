# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'jpeg/version'

Gem::Specification.new do |spec|
  spec.name          = 'jpeg'
  spec.version       = Jpeg::VERSION
  spec.authors       = ['masarakki']
  spec.email         = ['masaki@hisme.net']
  spec.extensions    = ['ext/jpeg/extconf.rb']
  spec.summary       = 'libjpeg wrapper for ruby'
  spec.description   = 'libjpeg wrapper for ruby'
  spec.homepage      = 'http://github.com/masarakki/jpeg'
  spec.license       = 'MIT'

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']

  spec.add_development_dependency 'bundler', '~> 1.6'
  spec.add_development_dependency 'rake'
  spec.add_development_dependency 'rspec'
  spec.add_development_dependency 'pry'
  spec.add_development_dependency 'rake-compiler'
  spec.add_development_dependency 'rspec-its'
  spec.add_development_dependency 'guard'
  spec.add_development_dependency 'guard-rspec'
  spec.add_development_dependency 'guard-rake'
  spec.add_development_dependency 'guard-rubocop'
end
