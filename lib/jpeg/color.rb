module Jpeg
  Color = Struct.new(:r, :g, :b) do
    def rgb
      [r, g, b]
    end
    alias_method :to_a, :rgb

    def to_s
      format '#%02x%02x%02x', *rgb
    end

    def inspect
      format '<Jpeg::Color r=0x%02x g=0x%02x b=0x%02x>', *rgb
    end
  end
end
