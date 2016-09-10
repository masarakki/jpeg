[![Build Status](https://secure.travis-ci.org/masarakki/jpeg.png)](http://travis-ci.org/masarakki/jpeg)
[![Dependency Status](https://gemnasium.com/masarakki/jpeg.png)](http://gemnasium.com/masarakki/jpeg)

# Jpeg

A libjpeg wrapper for ruby

## Installation

Add this line to your application's Gemfile:

    gem 'jpeg'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install jpeg

## Usage

- get size
- get color_info

```ruby
jpeg = Jpeg.open('path/to/file')
jpeg.size # => [1920, 1080]
jpeg.width # => 1920
jpeg.height # => 1080
jpeg.color_info # => :rgb or :gray
jpeg.rgb? # => true
jpeg.gray? # => false


dot = jpeg.at(1920, 500)   #=> <Jpeg::Color r=0x00 g=0xaa b=0xff>
dot.rgb    #=> [0, 170, 255]
dot.to_s   #=> '#00aaff'
```

## Contributing

1. Fork it ( https://github.com/[my-github-username]/jpeg/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request
