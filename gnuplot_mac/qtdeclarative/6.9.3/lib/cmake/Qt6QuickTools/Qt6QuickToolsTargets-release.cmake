#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::svgtoqml" for configuration "Release"
set_property(TARGET Qt6::svgtoqml APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::svgtoqml PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/svgtoqml"
  )

list(APPEND _cmake_import_check_targets Qt6::svgtoqml )
list(APPEND _cmake_import_check_files_for_Qt6::svgtoqml "${_IMPORT_PREFIX}/bin/svgtoqml" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
