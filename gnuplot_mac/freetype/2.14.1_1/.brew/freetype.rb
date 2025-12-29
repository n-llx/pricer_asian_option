class Freetype < Formula
  desc "Software library to render fonts"
  homepage "https://www.freetype.org/"
  url "https://downloads.sourceforge.net/project/freetype/freetype2/2.14.1/freetype-2.14.1.tar.xz"
  mirror "https://download.savannah.gnu.org/releases/freetype/freetype-2.14.1.tar.xz"
  sha256 "32427e8c471ac095853212a37aef816c60b42052d4d9e48230bab3bdf2936ccc"
  license "FTL"
  revision 1

  livecheck do
    url :stable
    regex(/url=.*?freetype[._-]v?(\d+(?:\.\d+)+)\.t/i)
  end

  depends_on "gnu-sed" => :build
  depends_on "pkgconf" => :build
  depends_on "libpng"

  uses_from_macos "bzip2"
  uses_from_macos "zlib"

  def install
    # https://gitlab.freedesktop.org/freetype/freetype/-/issues/1358
    ENV.prepend_path "PATH", Formula["gnu-sed"].opt_libexec/"gnubin"

    # This file will be installed to bindir, so we want to avoid embedding the
    # absolute path to the pkg-config shim.
    inreplace "builds/unix/freetype-config.in", "%PKG_CONFIG%", "pkg-config"

    system "./configure", "--prefix=#{prefix}",
                          "--enable-freetype-config",
                          "--without-harfbuzz"
    system "make"
    system "make", "install"

    inreplace [bin/"freetype-config", lib/"pkgconfig/freetype2.pc"],
      prefix, opt_prefix
  end

  test do
    system bin/"freetype-config", "--cflags", "--libs", "--ftversion",
                                  "--exec-prefix", "--prefix"
  end
end
