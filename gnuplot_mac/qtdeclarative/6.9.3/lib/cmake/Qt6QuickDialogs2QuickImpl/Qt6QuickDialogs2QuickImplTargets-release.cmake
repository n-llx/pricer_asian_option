#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QuickDialogs2QuickImpl" for configuration "Release"
set_property(TARGET Qt6::QuickDialogs2QuickImpl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QuickDialogs2QuickImpl PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Qml;Qt6::QuickControls2Impl;Qt6::QuickDialogs2Utils;Qt6::QuickTemplates2"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtQuickDialogs2QuickImpl.framework/Versions/A/QtQuickDialogs2QuickImpl"
  IMPORTED_SONAME_RELEASE "@rpath/QtQuickDialogs2QuickImpl.framework/Versions/A/QtQuickDialogs2QuickImpl"
  )

list(APPEND _cmake_import_check_targets Qt6::QuickDialogs2QuickImpl )
list(APPEND _cmake_import_check_files_for_Qt6::QuickDialogs2QuickImpl "${_IMPORT_PREFIX}/lib/QtQuickDialogs2QuickImpl.framework/Versions/A/QtQuickDialogs2QuickImpl" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
