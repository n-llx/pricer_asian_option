#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::LabsPlatform" for configuration "Release"
set_property(TARGET Qt6::LabsPlatform APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::LabsPlatform PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Core;Qt6::Gui;Qt6::Qml;Qt6::Quick;Qt6::QuickTemplates2;Qt6::Widgets"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtLabsPlatform.framework/Versions/A/QtLabsPlatform"
  IMPORTED_SONAME_RELEASE "@rpath/QtLabsPlatform.framework/Versions/A/QtLabsPlatform"
  )

list(APPEND _cmake_import_check_targets Qt6::LabsPlatform )
list(APPEND _cmake_import_check_files_for_Qt6::LabsPlatform "${_IMPORT_PREFIX}/lib/QtLabsPlatform.framework/Versions/A/QtLabsPlatform" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
