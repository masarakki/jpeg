def sample_file_path(file)
  File.join(File.dirname(__FILE__), 'samples', file)
end

describe 'Jpeg' do
  describe '.open' do
    subject(:image) { Jpeg.open(sample_file_path(filename)) }
    context 'valid jpeg' do
      let(:filename) { 'sample.jpg' }

      it { is_expected.to be_a Jpeg::Image }
      its(:size) { is_expected.to eq [112, 112] }
      its(:width) { is_expected.to eq 112 }
      its(:height) { is_expected.to eq 112 }
      its(:color_info) { is_expected.to eq :rgb }
      it { is_expected.to be_rgb }
      it { is_expected.not_to be_gray }

      it 'should export the decoded data' do
        decoded = subject.raw_data
        expect(decoded.count).to eq 112
        expect(decoded[0].count).to eq 112
        expect(decoded[0][0]).to eq [255, 255, 253]
        expect(decoded[60][50]).to eq [16, 27, 207]
        expect(decoded[111][111]).to eq [255, 255, 255]
      end
    end

    context 'non-exists file' do
      let(:filename) { 'nonexists.jpg' }
      it { expect { subject }.to raise_error(Jpeg::Error) }
    end

    context 'not a correct jpeg file' do
      let(:filename) { 'sample.png' }
      it { expect { subject }.to raise_error(Jpeg::Error) }
    end
  end
  describe :from_string do
    subject { Jpeg.open_buffer(File.read(sample_file_path(filename))) }
    let(:filename) { 'sample.jpg' }
    its(:size) { is_expected.to eq [112, 112] }
  end
end
