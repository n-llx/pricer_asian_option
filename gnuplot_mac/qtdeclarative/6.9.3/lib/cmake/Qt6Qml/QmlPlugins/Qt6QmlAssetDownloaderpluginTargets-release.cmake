#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QmlAssetDownloaderplugin" for configuration "Release"
set_property(TARGET Qt6::QmlAssetDownloaderplugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QmlAssetDownloaderplugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/qt/qml/Qt/labs/assetdownloader/libqmlassetdownloaderplugin.a"
  )

list(APPEND _cmake_import_check_targets Qt6::QmlAssetDownloaderplugin )
list(APPEND _cmake_import_check_files_for_Qt6::QmlAssetDownloaderplugin "${_IMPORT_PREFIX}/share/qt/qml/Qt/labs/assetdownloader/libqmlassetdownloaderplugin.a" )

# Import target "Qt6::QmlAssetDownloaderplugin_init" for configuration "Release"
set_property(TARGET Qt6::QmlAssetDownloaderplugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QmlAssetDownloaderplugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/share/qt/qml/Qt/labs/assetdownloader/objects-Release/QmlAssetDownloaderplugin_init/QmlAssetDownloaderplugin_init.cpp.o"
  )

list(APPEND _cmake_import_check_targets Qt6::QmlAssetDownloaderplugin_init )
list(APPEND _cmake_import_check_files_for_Qt6::QmlAssetDownloaderplugin_init "${_IMPORT_PREFIX}/share/qt/qml/Qt/labs/assetdownloader/objects-Release/QmlAssetDownloaderplugin_init/QmlAssetDownloaderplugin_init.cpp.o" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
