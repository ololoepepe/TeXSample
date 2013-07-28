TEMPLATE = lib
TARGET = TeXSampleCore

CONFIG += release

QT = core concurrent
BEQT = core
TSMP =

include(../module.pri)

DEFINES += TSMP_BUILD_CORE_LIB

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

contains(TSMP_CONFIG, builtin_resources) {
    DEFINES += TSMP_BUILTIN_RESOURCES
    RESOURCES += \
        texsamplecore.qrc \
        ../../translations/texsample_translations.qrc
}

!contains(TSMP_CONFIG, no_install) {

include(../../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
