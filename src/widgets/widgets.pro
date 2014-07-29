TEMPLATE = lib
TARGET = TeXSampleWidgets

CONFIG += release

BEQT = core widgets
TSMP = core

include(../module.pri)

DEFINES += TSMP_BUILD_WIDGETS_LIB

HEADERS += \
    tapplication.h \
    tgroupwidget.h \
    tgroupwidget_p.h \
    tinvitewidget.h \
    tinvitewidget_p.h \
    tlistwidget_p.h \
    tlistwidget.h \
    trecoverywidget.h \
    trecoverywidget_p.h \
    ttagswidget.h \
    ttagswidget_p.h \
    tuserinfowidget.h \
    tuserinfowidget_p.h

SOURCES += \
    tapplication.cpp \
    tgroupwidget.cpp \
    tinvitewidget.cpp \
    tlistwidget.cpp \
    trecoverywidget.cpp \
    ttagswidget.cpp \
    tuserinfowidget.cpp

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
