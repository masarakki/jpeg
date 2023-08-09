# frozen_string_literal: true

describe Jpeg::Image do
  subject(:image) { Jpeg.open(sample_file_path('zoi.jpg')) }
  its(:width) { is_expected.to eq 630 }
  its(:height) { is_expected.to eq 427 }

  describe '#inside?' do
    subject { image.send(:inside?, *pos) }
    context [0, 0] do
      let(:pos) { [0, 0] }
      it { is_expected.to eq true }
    end

    context [629, 426] do
      let(:pos) { [629, 426] }
      it { is_expected.to eq true }
    end

    [[630, 0], [-1, 0], [0, 427], [0, -1]].each do |pos|
      context pos do
        let(:pos) { pos }
        it { is_expected.to eq false }
      end
    end
  end

  context 'color image' do
    subject { image }
    it { is_expected.to be_rgb }
    it { is_expected.to be_color }
    it { is_expected.not_to be_gray }

    describe '#at' do
      subject { image.at(450, 200) }
      it { is_expected.to be_a Jpeg::Color }
      its(:rgb) { is_expected.to eq [0x99, 0x86, 0xbe] }
      context 'invalid position' do
        it { expect { image.at(630, 0) }.to raise_error 'invalid position' }
      end
    end
  end

  context 'gray image' do
    subject(:image) { Jpeg.open(sample_file_path('gray.jpg')) }
    it { is_expected.to be_gray }
    it { is_expected.not_to be_color }

    describe '#at' do
      subject { image.at(50, 60) }
      it { is_expected.to be_a Jpeg::Color }
      its(:to_a) { is_expected.to eq [37, 37, 37] }
    end
  end
end
