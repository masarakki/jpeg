module Jpeg
  class Image
    def rgb?
      color_info == :rgb
    end

    def gray?
      color_info == :gray
    end
  end
end
