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
    taccesslevel.h \
    tclientinfo.h \
    tcompilationresult.h \
    tcompiledproject.h \
    tcompilerparameters.h \
    tglobal.h \
    tidlist.h \
    tinviteinfo.h \
    tinviteinfolist.h \
    tmessage.h \
    tnamespace.h \
    toperationresult.h \
    toperationresult_p.h \
    tproject.h \
    tprojectfile.h \
    tprojectfilelist.h \
    tsampleinfo.h \
    tsampleinfolist.h \
    ttexttools.h \
    tuserinfo.h

SOURCES += \
    taccesslevel.cpp \
    tclientinfo.cpp \
    tcompilationresult.cpp \
    tcompiledproject.cpp \
    tcompilerparameters.cpp \
    tglobal.cpp \
    tidlist.cpp \
    tinviteinfo.cpp \
    tinviteinfolist.cpp \
    tmessage.cpp \
    tnamespace.cpp \
    toperationresult.cpp \
    tproject.cpp \
    tprojectfile.cpp \
    tprojectfilelist.cpp \
    tsampleinfo.cpp \
    tsampleinfolist.cpp \
    ttexttools.cpp \
    tuserinfo.cpp

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
