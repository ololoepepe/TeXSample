TEMPLATE = lib
TARGET = TeXSample

VERSION = 1.0.0
VER_MAJ = 1
VER_MIN = 0
VER_PAT = 0

CONFIG += release

QT = core
BEQT = core

isEmpty(BEQT_PREFIX) {
    #TODO: Add MacOS support
    mac|unix {
        BEQT_PREFIX=/usr/share/beqt
    } else:win32 {
        BEQT_PREFIX=$$(systemdrive)/PROGRA~1/BeQt
    }
}
include($${BEQT_PREFIX}/depend.pri)

DEFINES += TSMP_BUILD_LIB

HEADERS += \
    tglobal.h \
    tsampleinfo.h

SOURCES += \
    tglobal.cpp \
    tsampleinfo.cpp

TRANSLATIONS += ../translations/texsample_ru.ts

contains(CONFIG, tsmp_builtin_resources) {
    DEFINES += TSMP_BUILTIN_RESOURCES
    RESOURCES += \
        texsample.qrc \
        ../translations/texsample_translations.qrc
}

!contains(CONFIG, tsmp_no_install) {

include(../prefix.pri)

message($${TSMP_LIBS_INSTALLS_PATH})

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(CONFIG, tsmp_no_install)
