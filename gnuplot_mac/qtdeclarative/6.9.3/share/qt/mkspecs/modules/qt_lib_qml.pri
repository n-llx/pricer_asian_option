QT.qml.VERSION = 6.9.3
QT.qml.name = QtQml
QT.qml.module = QtQml
QT.qml.libs = $$QT_MODULE_LIB_BASE
QT.qml.ldflags = 
QT.qml.includes = $$QT_MODULE_LIB_BASE/QtQml.framework/Headers
QT.qml.frameworks = $$QT_MODULE_LIB_BASE
QT.qml.bins = $$QT_MODULE_BIN_BASE
QT.qml.plugin_types = qmltooling
QT.qml.depends =  core qmlintegration network
QT.qml.uses = 
QT.qml.module_config = v2 lib_bundle
QT.qml.DEFINES = QT_QML_LIB
QT.qml.enabled_features = qml-network qml-ssl qml-debug
QT.qml.disabled_features = 
QT_CONFIG += qml-network qml-ssl qml-debug
QT_MODULES += qml

