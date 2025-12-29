class Md4c < Formula
  desc "C Markdown parser. Fast. SAX-like interface"
  homepage "https://github.com/mity/md4c"
  url "https://github.com/mity/md4c/archive/refs/tags/release-0.5.2.tar.gz"
  sha256 "55d0111d48fb11883aaee91465e642b8b640775a4d6993c2d0e7a8092758ef21"
  license "MIT"

  depends_on "cmake" => :build

  def install
    system "cmake", "-S", ".", "-B", "build", *std_cmake_args, "-DCMAKE_INSTALL_RPATH=#{rpath}"
    system "cmake", "--build", "build"
    system "cmake", "--install", "build"
  end

  test do
    # test md2html
    (testpath/"test_md.md").write <<~EOS
      # Title
      some text
    EOS
    system bin/"md2html", "./test_md.md"

    # test libmd4c
    (testpath/"test_program.c").write <<~EOS
      #include <stddef.h>
      #include <md4c.h>

      MD_CHAR* text = "# Title\\nsome text";

      int test_block(MD_BLOCKTYPE type, void* detail, void* data) { return 0; }
      int test_span(MD_SPANTYPE type, void* detail, void* data) { return 0; }
      int test_text(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata) { return 0; }
      int main() {
        MD_PARSER parser = {
          .enter_block = test_block,
          .leave_block = test_block,
          .enter_span = test_span,
          .leave_span = test_span,
          .text = test_text
        };
        int result = md_parse(text, sizeof(text), &parser, NULL);
        return result;
      }
    EOS
    system ENV.cc, "test_program.c", "-L#{lib}", "-lmd4c", "-o", "test_program"
    system "./test_program"
  end
end
