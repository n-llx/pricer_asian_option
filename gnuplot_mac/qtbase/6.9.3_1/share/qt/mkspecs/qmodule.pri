QT_CPU_FEATURES.arm64 = cx16 neon crc32 crypto
QT.global_private.enabled_features = reduce_exports neon arm_crc32 arm_crypto arm_sve localtime_r system-zlib dbus dbus-linked gui network printsupport sql testlib widgets xml openssl dlopen relocatable trivial_auto_var_init_pattern stack_protector libcpp_hardening largefile precompile_header neon arm_crc32 arm_crypto arm_sve
QT.global_private.disabled_features = use_bfd_linker use_gold_linker use_lld_linker use_mold_linker android-style-assets gc_binaries developer-build private_tests doc_snippets debug elf_private_full_version no_direct_extern_access x86intrin sse2 sse3 ssse3 sse4_1 sse4_2 avx f16c avx2 avx512f avx512er avx512cd avx512pf avx512dq avx512bw avx512vl avx512ifma avx512vbmi avx512vbmi2 aesni vaes rdrnd rdseed shani lsx lasx mips_dsp mips_dspr2 localtime_s posix_fallocate force-system-libs force-bundled-libs stdlib-libcpp libudev intelcet glibc_fortify_source stack_clash_protection libstdcpp_assertions relro_now_linker
CONFIG += largefile precompile_header neon arm_crc32 arm_crypto arm_sve
PKG_CONFIG_EXECUTABLE = /opt/homebrew/bin/pkg-config
QT_COORD_TYPE = double
QT_BUILD_PARTS = libs tools

QMAKE_LIBS_ZLIB = -lz
QMAKE_LIBS_ZSTD = -lzstd.7 -lzstd
QMAKE_INCDIR_DBUS = /opt/homebrew/include/dbus-1.0 /opt/homebrew/lib/dbus-1.0/include
QMAKE_LIBS_DBUS = -ldbus-1
