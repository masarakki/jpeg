#!/usr/bin/env ruby

$LOAD_PATH.unshift File.expand_path('../lib', File.dirname(__FILE__))
require 'jpeg'

puts Process.pid
file = File.expand_path('samples/sample.jpg', File.dirname(__FILE__))

[10, 100, 1000].each do |n|
  n.times do
    @jpeg = Jpeg.open(file).raw_data
  end
  @jpeg = nil
  GC.start
  puts "#{n} times"
  puts `pmap -x #{Process.pid} | tail -n 1`
  # puts `lsof -p #{Process.pid}`
end
