#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Core5Compat" for configuration "Release"
set_property(TARGET Qt6::Core5Compat APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Core5Compat PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtCore5Compat.framework/Versions/A/QtCore5Compat"
  IMPORTED_SONAME_RELEASE "@rpath/QtCore5Compat.framework/Versions/A/QtCore5Compat"
  )

list(APPEND _cmake_import_check_targets Qt6::Core5Compat )
list(APPEND _cmake_import_check_files_for_Qt6::Core5Compat "${_IMPORT_PREFIX}/lib/QtCore5Compat.framework/Versions/A/QtCore5Compat" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
