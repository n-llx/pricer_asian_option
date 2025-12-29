#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QuickControls2UniversalStyleImpl" for configuration "Release"
set_property(TARGET Qt6::QuickControls2UniversalStyleImpl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QuickControls2UniversalStyleImpl PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Core;Qt6::Gui;Qt6::Qml;Qt6::QuickControls2Impl;Qt6::Quick;Qt6::QuickTemplates2"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtQuickControls2UniversalStyleImpl.framework/Versions/A/QtQuickControls2UniversalStyleImpl"
  IMPORTED_SONAME_RELEASE "@rpath/QtQuickControls2UniversalStyleImpl.framework/Versions/A/QtQuickControls2UniversalStyleImpl"
  )

list(APPEND _cmake_import_check_targets Qt6::QuickControls2UniversalStyleImpl )
list(APPEND _cmake_import_check_files_for_Qt6::QuickControls2UniversalStyleImpl "${_IMPORT_PREFIX}/lib/QtQuickControls2UniversalStyleImpl.framework/Versions/A/QtQuickControls2UniversalStyleImpl" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
