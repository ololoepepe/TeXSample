TEMPLATE = lib
TARGET = TeXSample

VERSION = 0.2.2
VER_MAJ = 0
VER_MIN = 2
VER_PAT = 2

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
    tsampleinfo.h \
    tprojectfile.h \
    tprojectfilelist.h \
    tproject.h \
    ttexttools.h \
    tuserinfo.h \
    tinviteinfo.h \
    tcompilerparameters.h \
    tcompilationresult.h \
    tcompiledproject.h \
    toperationresult.h \
    toperationresult_p.h \
    tclientinfo.h \
    tnamespace.h \
    taccesslevel.h

SOURCES += \
    tglobal.cpp \
    tsampleinfo.cpp \
    tprojectfile.cpp \
    tproject.cpp \
    ttexttools.cpp \
    tuserinfo.cpp \
    tinviteinfo.cpp \
    tcompilerparameters.cpp \
    tcompilationresult.cpp \
    tcompiledproject.cpp \
    toperationresult.cpp \
    tclientinfo.cpp \
    tnamespace.cpp \
    taccesslevel.cpp

TRANSLATIONS += ../translations/texsample_ru.ts

contains(TSMP_CONFIG, builtin_resources) {
    DEFINES += TSMP_BUILTIN_RESOURCES
    RESOURCES += \
        texsample.qrc \
        ../translations/texsample_translations.qrc
}

!contains(TSMP_CONFIG, no_install) {

include(../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
