#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AOM::aom" for configuration "Release"
set_property(TARGET AOM::aom APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AOM::aom PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libaom.3.13.1.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libaom.3.dylib"
  )

list(APPEND _cmake_import_check_targets AOM::aom )
list(APPEND _cmake_import_check_files_for_AOM::aom "${_IMPORT_PREFIX}/lib/libaom.3.13.1.dylib" )

# Import target "AOM::aom_static" for configuration "Release"
set_property(TARGET AOM::aom_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AOM::aom_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libaom.a"
  )

list(APPEND _cmake_import_check_targets AOM::aom_static )
list(APPEND _cmake_import_check_files_for_AOM::aom_static "${_IMPORT_PREFIX}/lib/libaom.a" )

# Import target "AOM::aomdec" for configuration "Release"
set_property(TARGET AOM::aomdec APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AOM::aomdec PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/aomdec"
  )

list(APPEND _cmake_import_check_targets AOM::aomdec )
list(APPEND _cmake_import_check_files_for_AOM::aomdec "${_IMPORT_PREFIX}/bin/aomdec" )

# Import target "AOM::aomenc" for configuration "Release"
set_property(TARGET AOM::aomenc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AOM::aomenc PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/aomenc"
  )

list(APPEND _cmake_import_check_targets AOM::aomenc )
list(APPEND _cmake_import_check_files_for_AOM::aomenc "${_IMPORT_PREFIX}/bin/aomenc" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
