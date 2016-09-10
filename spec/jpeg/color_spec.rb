describe Jpeg::Color do
  let(:g) { 0x00 }
  let(:rgb) { [0xcc, g, 0xff] }
  subject { Jpeg::Color.new(*rgb) }

  its(:g) { is_expected.to eq g }
  its(:rgb) { is_expected.to eq rgb }
  its(:to_s) { is_expected.to eq '#cc00ff' }
end
