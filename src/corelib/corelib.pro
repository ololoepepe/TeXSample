TEMPLATE = lib
TARGET = TeXSampleCore

CONFIG += release

QT = gui
BEQT = core
TSMP =

include(../module.pri)

DEFINES += TSMP_BUILD_CORE_LIB

HEADERS += \
    taccesslevel.h \
    tauthorinfo.h \
    tauthorinfolist.h \
    tbinaryfile.h \
    tbinaryfilelist.h \
    tclientinfo.h \
    tcoreapplication.h \
    tfileinfo.h \
    tfileinfolist.h \
    tglobal.h \
    tgroupinfo.h \
    tgroupinfolist.h \
    tgroupmodel.h \
    tidlist.h \
    tinviteinfo.h \
    tinviteinfolist.h \
    tinvitemodel.h \
    tlab.h \
    tlabinfo.h \
    tlabinfolist.h \
    tmessage.h \
    tnamespace.h \
    toperation.h \
    tproject.h \
    tprojectinfo.h \
    tprojectinfolist.h \
    tprojecttype.h \
    tsampleinfo.h \
    tsampleinfolist.h \
    tsampletype.h \
    tservice.h \
    tservicelist.h \
    ttexcompiler.h \
    ttexfile.h \
    ttexfilelist.h \
    ttexproject.h \
    tuseridentifier.h \
    tuserinfo.h \
    tuserinfolist.h \
    tusermodel.h

SOURCES += \
    taccesslevel.cpp \
    tauthorinfo.cpp \
    tauthorinfolist.cpp \
    tbinaryfile.cpp \
    tbinaryfilelist.cpp \
    tclientinfo.cpp \
    tcoreapplication.cpp \
    tfileinfo.cpp \
    tfileinfolist.cpp \
    tglobal.cpp \
    tgroupinfo.cpp \
    tgroupinfolist.cpp \
    tgroupmodel.cpp \
    tidlist.cpp \
    tinviteinfo.cpp \
    tinviteinfolist.cpp \
    tinvitemodel.cpp \
    tlab.cpp \
    tlabinfo.cpp \
    tlabinfolist.cpp \
    tmessage.cpp \
    tnamespace.cpp \
    tproject.cpp \
    tprojectinfo.cpp \
    tprojectinfolist.cpp \
    tprojecttype.cpp \
    tsampleinfo.cpp \
    tsampleinfolist.cpp \
    tsampletype.cpp \
    tservice.cpp \
    tservicelist.cpp \
    ttexcompiler.cpp \
    ttexfile.cpp \
    ttexfilelist.cpp \
    ttexproject.cpp \
    tuseridentifier.cpp \
    tuserinfo.cpp \
    tuserinfolist.cpp \
    tusermodel.cpp

include(reply/reply.pri)
include(request/request.pri)

contains(TSMP_CONFIG, builtin_resources) {
    DEFINES += TSMP_BUILTIN_RESOURCES
    RESOURCES += \
        ../../translations/texsample_translations.qrc
}

!contains(TSMP_CONFIG, no_install) {

include(../../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
