#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QuickControls2MacOSStyleImpl" for configuration "Release"
set_property(TARGET Qt6::QuickControls2MacOSStyleImpl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QuickControls2MacOSStyleImpl PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Qml;Qt6::Core"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtQuickControls2MacOSStyleImpl.framework/Versions/A/QtQuickControls2MacOSStyleImpl"
  IMPORTED_SONAME_RELEASE "@rpath/QtQuickControls2MacOSStyleImpl.framework/Versions/A/QtQuickControls2MacOSStyleImpl"
  )

list(APPEND _cmake_import_check_targets Qt6::QuickControls2MacOSStyleImpl )
list(APPEND _cmake_import_check_files_for_Qt6::QuickControls2MacOSStyleImpl "${_IMPORT_PREFIX}/lib/QtQuickControls2MacOSStyleImpl.framework/Versions/A/QtQuickControls2MacOSStyleImpl" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
