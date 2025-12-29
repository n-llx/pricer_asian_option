#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cerf::cerfcpp" for configuration "Release"
set_property(TARGET cerf::cerfcpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cerf::cerfcpp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcerfcpp.3.1.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libcerfcpp.3.dylib"
  )

list(APPEND _cmake_import_check_targets cerf::cerfcpp )
list(APPEND _cmake_import_check_files_for_cerf::cerfcpp "${_IMPORT_PREFIX}/lib/libcerfcpp.3.1.dylib" )

# Import target "cerf::cerf" for configuration "Release"
set_property(TARGET cerf::cerf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cerf::cerf PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcerf.3.1.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libcerf.3.dylib"
  )

list(APPEND _cmake_import_check_targets cerf::cerf )
list(APPEND _cmake_import_check_files_for_cerf::cerf "${_IMPORT_PREFIX}/lib/libcerf.3.1.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
