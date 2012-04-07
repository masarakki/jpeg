require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

def sample_file_path(file)
  File.join(File.dirname(__FILE__), 'samples', file)
end

describe "Jpeg" do
  subject { @jpeg }
  describe :open do
    context "valid jpeg" do
      before { @jpeg = Jpeg.open(sample_file_path("sample.jpg")) }
      its(:size) { should == [112, 112] }
      its(:width) { should == 112 }
      its(:height) { should == 112 }
      its(:color_info) { should == :rgb }
      its(:rgb?) { should be_true }
      its(:gray?) { should be_false }
    end
    context "non-exists file" do
      it {
        lambda {
          Jpeg.open(sample_file_path("nonexists.jpg"))
        }.should raise_error
      }
    end

    context "not a correct jpeg file" do
      it {
        lambda {
          Jpeg.open(sample_file_path("sample.png"))
        }.should raise_error
      }
    end
  end
  describe :from_string do
    before { @jpeg = Jpeg.open_buffer(File.open(sample_file_path("sample.jpg")).read) }
    its(:size) { should == [112, 112] }
  end
end
