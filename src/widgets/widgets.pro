TEMPLATE = lib
TARGET = TeXSampleWidgets

CONFIG += release

BEQT = core widgets
TSMP = core

include(../module.pri)

DEFINES += TSMP_BUILD_WIDGETS_LIB

HEADERS += \
    tabstractlistwidgetitemdelegate.h \
    tapplication.h \
    tauthorinfolistwidgetitemdelegate.h \
    tauthorinfolistwidgetitemdelegate_p.h \
    tauthorinfowidget.h \
    tauthorinfowidget_p.h \
    tconfirmationwidget.h \
    tconfirmationwidget_p.h \
    tlistwidget_p.h \
    tlistwidget.h \
    ttagwidget.h \
    ttagwidget_p.h

SOURCES += \
    tabstractlistwidgetitemdelegate.cpp \
    tapplication.cpp \
    tauthorinfolistwidgetitemdelegate.cpp \
    tauthorinfowidget.cpp \
    tconfirmationwidget.cpp \
    tlistwidget.cpp \
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
