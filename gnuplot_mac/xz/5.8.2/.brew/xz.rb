class Xz < Formula
  desc "General-purpose data compression with high compression ratio"
  homepage "https://tukaani.org/xz/"
  url "https://github.com/tukaani-project/xz/releases/download/v5.8.2/xz-5.8.2.tar.gz"
  mirror "https://downloads.sourceforge.net/project/lzmautils/xz-5.8.2.tar.gz"
  mirror "http://downloads.sourceforge.net/project/lzmautils/xz-5.8.2.tar.gz"
  sha256 "ce09c50a5962786b83e5da389c90dd2c15ecd0980a258dd01f70f9e7ce58a8f1"
  license all_of: [
    "0BSD",
    "GPL-2.0-or-later",
  ]
  version_scheme 1

  deny_network_access! [:build, :postinstall]

  def install
    system "./configure", *std_configure_args, "--disable-silent-rules", "--disable-nls"
    system "make", "check"
    system "make", "install"
  end

  test do
    path = testpath/"data.txt"
    original_contents = "." * 1000
    path.write original_contents

    # compress: data.txt -> data.txt.xz
    system bin/"xz", path
    refute_path_exists path

    # decompress: data.txt.xz -> data.txt
    system bin/"xz", "-d", "#{path}.xz"
    assert_equal original_contents, path.read

    # Check that http mirror works
    xz_tar = testpath/"xz.tar.gz"
    stable.mirrors.each do |mirror|
      next if mirror.start_with?("https")

      xz_tar.unlink if xz_tar.exist?

      # Set fake CA Cert to block any HTTPS redirects.
      system "curl", "--location", mirror, "--cacert", "/fake", "--output", xz_tar
      assert_equal stable.checksum.hexdigest, xz_tar.sha256
    end
  end
end
