QT.network.VERSION = 6.9.3
QT.network.name = QtNetwork
QT.network.module = QtNetwork
QT.network.libs = $$QT_MODULE_LIB_BASE
QT.network.ldflags = 
QT.network.includes = $$QT_MODULE_LIB_BASE/QtNetwork.framework/Headers
QT.network.frameworks = $$QT_MODULE_LIB_BASE
QT.network.bins = $$QT_MODULE_BIN_BASE
QT.network.plugin_types = networkaccess networkinformation tls
QT.network.depends =  core
QT.network.uses = 
QT.network.module_config = v2 lib_bundle
QT.network.DEFINES = QT_NETWORK_LIB
QT.network.enabled_features = getifaddrs ipv6ifname securetransport ssl dtls ocsp http udpsocket networkproxy socks5 networkinterface networkdiskcache brotli localserver dnslookup gssapi topleveldomain
QT.network.disabled_features = schannel sctp sspi
QT_CONFIG += getifaddrs ipv6ifname securetransport ssl dtls ocsp http udpsocket networkproxy socks5 networkinterface networkdiskcache brotli localserver dnslookup gssapi topleveldomain
QT_MODULES += network

