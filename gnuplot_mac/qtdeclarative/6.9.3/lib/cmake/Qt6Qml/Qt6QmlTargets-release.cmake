#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Qml" for configuration "Release"
set_property(TARGET Qt6::Qml APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Qml PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtQml.framework/Versions/A/QtQml"
  IMPORTED_SONAME_RELEASE "@rpath/QtQml.framework/Versions/A/QtQml"
  )

list(APPEND _cmake_import_check_targets Qt6::Qml )
list(APPEND _cmake_import_check_files_for_Qt6::Qml "${_IMPORT_PREFIX}/lib/QtQml.framework/Versions/A/QtQml" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
