# frozen_string_literal: true

module Jpeg
  Color = Struct.new(:r, :g, :b) do
    def rgb
      [r, g, b]
    end
    alias_method :to_a, :rgb

    def to_h
      { red: r, green: g, blue: b }
    end

    def to_s
      format '#%<red>02x%<green>02x%<blue>02x', to_h
    end

    def inspect
      format '<Jpeg::Color r=0x%<red>02x g=0x%<green>02x b=0x%<blue>02x>', to_h
    end
  end
end
