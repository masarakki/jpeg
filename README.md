jpeg [![Build Status](https://secure.travis-ci.org/masarakki/jpeg.png)](http://travis-ci.org/masarakki/jpeg) [![Dependency Status](https://gemnasium.com/masarakki/jpeg.png)](http://gemnasium.com/masarakki/jpeg)
====
A libjpeg wrapper for ruby
Install
-------
 gem install jpeg

or
 echo 'gem "jpeg"' >> Gemfile
 bundle install

Usage
-----
    jpeg = Jpeg.open('path/to/file')
    jpeg.size # => [1920, 1080]
    jpeg.width # => 1920
    jpeg.height # => 1080
    jpeg.color_info # => :rgb or :gray
    jpeg.rgb? # => true
    jpeg.gray? # => false

What can do
-----------
* get size
* get color_info

Contributing to jpeg
--------------------

* Check out the latest master to make sure the feature hasn't been implemented or the bug hasn't been fixed yet.
* Check out the issue tracker to make sure someone already hasn't requested it and/or contributed it.
* Fork the project.
* Start a feature/bugfix branch.
* Commit and push until you are happy with your contribution.
* Make sure to add tests for it. This is important so I don't break it in a future version unintentionally.
* Please try not to mess with the Rakefile, version, or history. If you want to have your own version, or is otherwise necessary, that is fine, but please isolate to its own commit so I can cherry-pick around it.

Copyright
---------

Copyright (c) 2012 masarakki. See LICENSE.txt for
further details.

