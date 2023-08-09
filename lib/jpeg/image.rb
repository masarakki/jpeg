# frozen_string_literal: true

module Jpeg
  class Image
    def at(pos_x, pos_y)
      raise 'invalid position' unless inside? pos_x, pos_y

      dot = raw_data[pos_y][pos_x]
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

    def inside?(pos_x, pos_y)
      pos_x < width && pos_x >= 0 && pos_y < height && pos_y >= 0
    end
  end
end
