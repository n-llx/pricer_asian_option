#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QmlLocalStorage" for configuration "Release"
set_property(TARGET Qt6::QmlLocalStorage APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QmlLocalStorage PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Qml"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/QtQmlLocalStorage.framework/Versions/A/QtQmlLocalStorage"
  IMPORTED_SONAME_RELEASE "@rpath/QtQmlLocalStorage.framework/Versions/A/QtQmlLocalStorage"
  )

list(APPEND _cmake_import_check_targets Qt6::QmlLocalStorage )
list(APPEND _cmake_import_check_files_for_Qt6::QmlLocalStorage "${_IMPORT_PREFIX}/lib/QtQmlLocalStorage.framework/Versions/A/QtQmlLocalStorage" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
