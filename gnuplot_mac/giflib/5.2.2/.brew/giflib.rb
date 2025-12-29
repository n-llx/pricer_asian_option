class Giflib < Formula
  desc "Library and utilities for processing GIFs"
  homepage "https://giflib.sourceforge.net/"
  url "https://downloads.sourceforge.net/project/giflib/giflib-5.2.2.tar.gz"
  sha256 "be7ffbd057cadebe2aa144542fd90c6838c6a083b5e8a9048b8ee3b66b29d5fb"
  license "MIT"

  livecheck do
    url :stable
    regex(%r{url=.*?/giflib[._-]v?(\d+(?:\.\d+)+)\.t}i)
  end

  # Move logo resizing to be a prereq for giflib website only, so that imagemagick is not required to build package
  # Remove this patch once the upstream fix is released:
  # https://sourceforge.net/p/giflib/code/ci/d54b45b0240d455bbaedee4be5203d2703e59967/
  patch :DATA

  def install
    system "make", "all"
    system "make", "install", "PREFIX=#{prefix}"
  end

  test do
    output = shell_output("#{bin}/giftext #{test_fixtures("test.gif")}")
    assert_match "Screen Size - Width = 1, Height = 1", output
  end
end

__END__
diff --git a/doc/Makefile b/doc/Makefile
index d9959d5..91b0b37 100644
--- a/doc/Makefile
+++ b/doc/Makefile
@@ -46,13 +46,13 @@ giflib-logo.gif: ../pic/gifgrid.gif
 	convert $^ -resize 50x50 $@
 
 # Philosophical choice: the website gets the internal manual pages
-allhtml: $(XMLALL:.xml=.html) giflib-logo.gif
+allhtml: $(XMLALL:.xml=.html)
 
 manpages: $(XMLMAN1:.xml=.1) $(XMLMAN7:.xml=.7) $(XMLINTERNAL:.xml=.1)
 
 # Prepare the website directory to deliver an update.
 # ImageMagick and asciidoc are required.
-website: allhtml
+website: allhtml giflib-logo.gif
 	rm -fr staging; mkdir staging; 
 	cp -r $(XMLALL:.xml=.html) gifstandard whatsinagif giflib-logo.gif staging
 	cp index.html.in staging/index.html
