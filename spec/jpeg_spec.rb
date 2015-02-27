require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

def sample_file_path(file)
  File.join(File.dirname(__FILE__), 'samples', file)
end

describe "Jpeg" do
  subject { @jpeg }
  describe :open do
    context "valid jpeg" do
      before { @jpeg = Jpeg.open(sample_file_path("sample.jpg")) }
      it { expect(subject).to be_a Jpeg::Image }
      it { expect(subject.size).to eq [112, 112] }
      it { expect(subject.width).to eq 112 }
      it { expect(subject.height).to eq 112 }
      it { expect(subject.color_info).to eq :rgb }
      it { expect(subject).to be_rgb }
      it { expect(subject).not_to be_gray }
      it "should export the decoded data" do
        decoded = subject.raw_data
        expect(decoded.count).to eq 112
        expect(decoded[0].count).to eq 112
        expect(decoded[0][0]).to eq [255, 255, 253]
        expect(decoded[60][50]).to eq [16, 27, 207]
        expect(decoded[111][111]).to eq [255, 255, 255]
      end
    end

    context "non-exists file" do
      it { expect { Jpeg.open(sample_file_path("nonexists.jpg")) }.to raise_error(Jpeg::Error) }
    end

    context "not a correct jpeg file" do
      it { expect { Jpeg.open(sample_file_path("sample.png")) }.to raise_error(Jpeg::Error) }
    end
  end
  describe :from_string do
    before { @jpeg = Jpeg.open_buffer(File.open(sample_file_path("sample.jpg")).read) }
    it { expect(subject.size).to eq [112, 112] }
  end
end
