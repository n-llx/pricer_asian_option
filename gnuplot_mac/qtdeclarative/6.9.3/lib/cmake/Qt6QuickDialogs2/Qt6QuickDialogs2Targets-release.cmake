#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QuickDialogs2" for configuration "Release"
set_property(TARGET Qt6::QuickDialogs2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QuickDialogs2 PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Qml;Qt6::QuickControls2Impl;Qt6::QuickDialogs2Utils;Qt6::QuickDialogs2QuickImpl;Qt6::QuickTemplates2"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtQuickDialogs2.framework/Versions/A/QtQuickDialogs2"
  IMPORTED_SONAME_RELEASE "@rpath/QtQuickDialogs2.framework/Versions/A/QtQuickDialogs2"
  )

list(APPEND _cmake_import_check_targets Qt6::QuickDialogs2 )
list(APPEND _cmake_import_check_files_for_Qt6::QuickDialogs2 "${_IMPORT_PREFIX}/lib/QtQuickDialogs2.framework/Versions/A/QtQuickDialogs2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
