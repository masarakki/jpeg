require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

def sample_file_path(file)
  File.join(File.dirname(__FILE__), 'samples', file)
end

describe "Jpeg" do
  subject { @jpeg }
  context "valid jpeg" do
    before { @jpeg = Jpeg.open(sample_file_path("sample.jpg")) }
    its(:size) { should == [112, 112] }
    its(:width) { should == 112 }
    its(:height) { should == 112 }
  end
end
