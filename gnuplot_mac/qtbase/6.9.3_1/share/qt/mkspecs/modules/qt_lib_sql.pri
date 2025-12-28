QT.sql.VERSION = 6.9.3
QT.sql.name = QtSql
QT.sql.module = QtSql
QT.sql.libs = $$QT_MODULE_LIB_BASE
QT.sql.ldflags = 
QT.sql.includes = $$QT_MODULE_LIB_BASE/QtSql.framework/Headers
QT.sql.frameworks = $$QT_MODULE_LIB_BASE
QT.sql.bins = $$QT_MODULE_BIN_BASE
QT.sql.plugin_types = sqldrivers
QT.sql.depends =  core
QT.sql.uses = 
QT.sql.module_config = v2 lib_bundle
QT.sql.DEFINES = QT_SQL_LIB
QT.sql.enabled_features = sqlmodel
QT.sql.disabled_features = 
QT_CONFIG += sqlmodel
QT_MODULES += sql

