QT.opengl.VERSION = 6.9.3
QT.opengl.name = QtOpenGL
QT.opengl.module = QtOpenGL
QT.opengl.libs = $$QT_MODULE_LIB_BASE
QT.opengl.ldflags = 
QT.opengl.includes = $$QT_MODULE_LIB_BASE/QtOpenGL.framework/Headers
QT.opengl.frameworks = $$QT_MODULE_LIB_BASE
QT.opengl.bins = $$QT_MODULE_BIN_BASE
QT.opengl.depends =  core gui
QT.opengl.uses = vulkan/nolink
QT.opengl.module_config = v2 lib_bundle
QT.opengl.DEFINES = QT_OPENGL_LIB
QT.opengl.enabled_features = 
QT.opengl.disabled_features = 
QT_CONFIG += 
QT_MODULES += opengl

