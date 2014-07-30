TEMPLATE = lib
TARGET = TeXSampleNetwork

CONFIG += release

BEQT = core network
TSMP = core

include(../module.pri)

DEFINES += TSMP_BUILD_NETWORK_LIB

HEADERS += \
    tnetworkclient.h \
    tnetworkclient_p.h

SOURCES += \
    tnetworkclient.cpp

!contains(TSMP_CONFIG, no_install) {

include(../../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
