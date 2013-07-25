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

#CImg defines
DEFINES += "cimg_file_separator=\\\'/\\\'"
DEFINES += "cimg_verbosity=0"
DEFINES += "cimg_display=0"

HEADERS += \
    cimg/CImg.h \
    taccesslevel.h \
    tclientinfo.h \
    tcompilationresult.h \
    tcompiledproject.h \
    tcompilerparameters.h \
    tglobal.h \
    tidlist.h \
    tinviteinfo.h \
    tinviteinfolist.h \
    tlabinfo.h \
    tlabinfolist.h \
    tlabproject.h \
    tmessage.h \
    tnamespace.h \
    toperationresult.h \
    toperationresult_p.h \
    tprojectfile.h \
    tprojectfilelist.h \
    tsampleinfo.h \
    tsampleinfolist.h \
    tservice.h \
    tservicelist.h \
    ttexproject.h \
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
    tlabinfo.cpp \
    tlabinfolist.cpp \
    tlabproject.cpp \
    tmessage.cpp \
    tnamespace.cpp \
    toperationresult.cpp \
    tprojectfile.cpp \
    tprojectfilelist.cpp \
    tsampleinfo.cpp \
    tsampleinfolist.cpp \
    tservice.cpp \
    tservicelist.cpp \
    ttexproject.cpp \
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
