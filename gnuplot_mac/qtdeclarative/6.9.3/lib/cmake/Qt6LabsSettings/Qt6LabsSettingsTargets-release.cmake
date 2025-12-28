#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::LabsSettings" for configuration "Release"
set_property(TARGET Qt6::LabsSettings APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::LabsSettings PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtLabsSettings.framework/Versions/A/QtLabsSettings"
  IMPORTED_SONAME_RELEASE "@rpath/QtLabsSettings.framework/Versions/A/QtLabsSettings"
  )

list(APPEND _cmake_import_check_targets Qt6::LabsSettings )
list(APPEND _cmake_import_check_files_for_Qt6::LabsSettings "${_IMPORT_PREFIX}/lib/QtLabsSettings.framework/Versions/A/QtLabsSettings" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
