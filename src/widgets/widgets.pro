TEMPLATE = lib
TARGET = TeXSampleWidgets

CONFIG += release

BEQT = core widgets
TSMP = core

include(../module.pri)

DEFINES += TSMP_BUILD_WIDGETS_LIB

HEADERS += \
    tapplication.h \
    tauthorinfowidget.h \
    tauthorinfowidget_p.h \
    tauthorlistwidget.h \
    tauthorlistwidget_p.h \
    tconfirmationwidget.h \
    tconfirmationwidget_p.h \
    tgrouplistwidget.h \
    tgrouplistwidget_p.h \
    tinviteinfowidget.h \
    tinviteinfowidget_p.h \
    tservicewidget.h \
    tservicewidget_p.h \
    ttagwidget.h \
    ttagwidget_p.h

SOURCES += \
    tapplication.cpp \
    tauthorinfowidget.cpp \
    tauthorlistwidget.cpp \
    tconfirmationwidget.cpp \
    tgrouplistwidget.cpp \
    tinviteinfowidget.cpp \
    tservicewidget.cpp \
    ttagwidget.cpp

contains(TSMP_CONFIG, builtin_resources) {
    DEFINES += TSMP_BUILTIN_RESOURCES
    RESOURCES += \
        texsamplewidgets.qrc
}

!contains(TSMP_CONFIG, no_install) {

include(../../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
