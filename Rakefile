require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

task default: :spec

require 'rake/extensiontask'

Rake::ExtensionTask.new('jpeg') do |ext|
  ext.lib_dir = 'lib/jpeg'
end
