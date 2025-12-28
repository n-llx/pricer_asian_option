#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hwy::hwy" for configuration "Release"
set_property(TARGET hwy::hwy APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hwy::hwy PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhwy.1.3.0.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libhwy.1.dylib"
  )

list(APPEND _cmake_import_check_targets hwy::hwy )
list(APPEND _cmake_import_check_files_for_hwy::hwy "${_IMPORT_PREFIX}/lib/libhwy.1.3.0.dylib" )

# Import target "hwy::hwy_contrib" for configuration "Release"
set_property(TARGET hwy::hwy_contrib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hwy::hwy_contrib PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhwy_contrib.1.3.0.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libhwy_contrib.1.dylib"
  )

list(APPEND _cmake_import_check_targets hwy::hwy_contrib )
list(APPEND _cmake_import_check_files_for_hwy::hwy_contrib "${_IMPORT_PREFIX}/lib/libhwy_contrib.1.3.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
