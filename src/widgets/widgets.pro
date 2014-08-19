TEMPLATE = lib
TARGET = TeXSampleWidgets

CONFIG += release

BEQT = core widgets
TSMP = core

include(../module.pri)

DEFINES += TSMP_BUILD_WIDGETS_LIB

HEADERS += \
    tapplication.h \
    tlistwidget_p.h \
    tlistwidget.h \
    ttagwidget.h \
    ttagwidget_p.h

SOURCES += \
    tapplication.cpp \
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
