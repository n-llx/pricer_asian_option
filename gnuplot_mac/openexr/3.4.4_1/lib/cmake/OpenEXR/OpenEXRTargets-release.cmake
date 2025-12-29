#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenEXR::Iex" for configuration "Release"
set_property(TARGET OpenEXR::Iex APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenEXR::Iex PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libIex-3_4.33.3.4.4.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libIex-3_4.33.dylib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::Iex )
list(APPEND _cmake_import_check_files_for_OpenEXR::Iex "${_IMPORT_PREFIX}/lib/libIex-3_4.33.3.4.4.dylib" )

# Import target "OpenEXR::IlmThread" for configuration "Release"
set_property(TARGET OpenEXR::IlmThread APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenEXR::IlmThread PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libIlmThread-3_4.33.3.4.4.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libIlmThread-3_4.33.dylib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::IlmThread )
list(APPEND _cmake_import_check_files_for_OpenEXR::IlmThread "${_IMPORT_PREFIX}/lib/libIlmThread-3_4.33.3.4.4.dylib" )

# Import target "OpenEXR::OpenEXRCore" for configuration "Release"
set_property(TARGET OpenEXR::OpenEXRCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenEXR::OpenEXRCore PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "libdeflate::libdeflate_shared;openjph"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libOpenEXRCore-3_4.33.3.4.4.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libOpenEXRCore-3_4.33.dylib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::OpenEXRCore )
list(APPEND _cmake_import_check_files_for_OpenEXR::OpenEXRCore "${_IMPORT_PREFIX}/lib/libOpenEXRCore-3_4.33.3.4.4.dylib" )

# Import target "OpenEXR::OpenEXR" for configuration "Release"
set_property(TARGET OpenEXR::OpenEXR APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenEXR::OpenEXR PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libOpenEXR-3_4.33.3.4.4.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libOpenEXR-3_4.33.dylib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::OpenEXR )
list(APPEND _cmake_import_check_files_for_OpenEXR::OpenEXR "${_IMPORT_PREFIX}/lib/libOpenEXR-3_4.33.3.4.4.dylib" )

# Import target "OpenEXR::OpenEXRUtil" for configuration "Release"
set_property(TARGET OpenEXR::OpenEXRUtil APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenEXR::OpenEXRUtil PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libOpenEXRUtil-3_4.33.3.4.4.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libOpenEXRUtil-3_4.33.dylib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::OpenEXRUtil )
list(APPEND _cmake_import_check_files_for_OpenEXR::OpenEXRUtil "${_IMPORT_PREFIX}/lib/libOpenEXRUtil-3_4.33.3.4.4.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
