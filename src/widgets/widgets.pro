TEMPLATE = lib
TARGET = TeXSampleWidgets

CONFIG += release

QT = core concurrent gui widgets
BEQT = core widgets
TSMP = core

include(../module.pri)

DEFINES += TSMP_BUILD_WIDGETS_LIB

HEADERS += \
    trecoverydialog.h \
    trecoverydialog_p.h \
    ttagswidget.h \
    ttagswidget_p.h \
    tuserwidget.h \
    tuserwidget_p.h \
    tlistwidget_p.h \
    tlistwidget.h

SOURCES += \
    trecoverydialog.cpp \
    ttagswidget.cpp \
    tuserwidget.cpp \
    tlistwidget.cpp

!contains(TSMP_CONFIG, no_install) {

include(../../prefix.pri)

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

} #end !contains(TSMP_CONFIG, no_install)
