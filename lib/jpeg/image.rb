module Jpeg
  class Image
    def at(x, y)
      raise 'invalid position' unless inside? x, y
      dot = raw_data[y][x]
      color? ? Color.new(*dot) : Color.new(dot, dot, dot)
    end

    def rgb?
      color_info == :rgb
    end
    alias color? rgb?

    def gray?
      color_info == :gray
    end

    private

    def inside?(x, y)
      x < width && x >= 0 && y < height && y >= 0
    end
  end
end
