TEMPLATE = lib
TARGET = TeXSampleNetworkWidgets

CONFIG += release

BEQT = core network widgets
TSMP = core network widgets

include(../module.pri)

DEFINES += TSMP_BUILD_NETWORKWIDGETS_LIB

HEADERS += \
    tgroupwidget.h \
    tgroupwidget_p.h \
    tinvitewidget.h \
    tinvitewidget_p.h \
    trecoverywidget.h \
    trecoverywidget_p.h \
    tuserinfowidget.h \
    tuserinfowidget_p.h \
    tuserwidget.h \
    tuserwidget_p.h

SOURCES += \
    tgroupwidget.cpp \
    tinvitewidget.cpp \
    trecoverywidget.cpp \
    tuserinfowidget.cpp \
    tuserwidget.cpp

!contains(TSMP_CONFIG, no_install) {

include(../../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
