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

HEADERS += \
    src/tglobal.h \
    src/tsampleinfo.h

SOURCES += \
    src/tglobal.cpp \
    src/tsampleinfo.cpp

#mac {
    #isEmpty(TSMP_PREFIX):TSMP_PREFIX=/Library
    #TODO: Add ability to create bundles
#} else:unix:!mac {
#TODO: Add MacOS support
mac|unix {
    isEmpty(TSMP_PREFIX):TSMP_PREFIX=/usr
    equals(TSMP_PREFIX, "/")|equals(TSMP_PREFIX, "/usr")|equals(TSMP_PREFIX, "/usr/local") {
        isEmpty(TSMP_HEADERS_INSTALLS_PATH):TSMP_HEADERS_INSTALLS_PATH=$${TSMP_PREFIX}/include/texsample
        isEmpty(TSMP_LIBS_INSTALLS_PATH):TSMP_LIBS_INSTALLS_PATH=$${TSMP_PREFIX}/lib
        isEmpty(TSMP_RESOURCES_INSTALLS_PATH):TSMP_RESOURCES_INSTALLS_PATH=$${TSMP_PREFIX}/share/texsample
    } else {
        isEmpty(TSMP_HEADERS_INSTALLS_PATH):TSMP_HEADERS_INSTALLS_PATH=$${TSMP_PREFIX}/include
        isEmpty(TSMP_LIBS_INSTALLS_PATH):TSMP_LIBS_INSTALLS_PATH=$${TSMP_PREFIX}/lib
        isEmpty(TSMP_RESOURCES_INSTALLS_PATH):TSMP_RESOURCES_INSTALLS_PATH=$${TSMP_PREFIX}
    }
} else:win32 {
    isEmpty(TSMP_PREFIX):TSMP_PREFIX=$$(systemdrive)/PROGRA~1/TeXSample
    isEmpty(TSMP_HEADERS_INSTALLS_PATH):TSMP_HEADERS_INSTALLS_PATH=$${TSMP_PREFIX}/include
    isEmpty(TSMP_LIBS_INSTALLS_PATH):TSMP_LIBS_INSTALLS_PATH=$${TSMP_PREFIX}/lib
    isEmpty(TSMP_RESOURCES_INSTALLS_PATH):TSMP_RESOURCES_INSTALLS_PATH=$${TSMP_PREFIX}
}

##############################################################################
################################ Installing ##################################
##############################################################################

!contains(CONFIG, tsmp_no_install) {

target.path = $${TSMP_LIBS_INSTALLS_PATH}
INSTALLS = target

##############################################################################
################################ Headers #####################################
##############################################################################

#Gets contents of an .h header
#Returns the corresponding actual header path
defineReplace(getActualHeaderInternal) {
    headerContents=$${1}
    actualHeader=$$replace(headerContents, "$${LITERAL_HASH}include", "")
    actualHeader=$$replace(actualHeader, "\\.\\./", "")
    actualHeader=$$replace(actualHeader, "\"", "")
    return($${PWD}/$${actualHeader})
}

#Gets path to a header (either .h or with no extension)
#Returns corresponding actual header path
defineReplace(getActualHeader) {
    headerPath=$${1}
    headerContents=$$cat($${headerPath})
    isEmpty(headerContents) {
        headerPath=
    } else:!equals(headerContents, $$replace(headerContents, "\\.\\./", "")) {
        headerPath=$$getActualHeaderInternal($${headerContents})
    }
    return($${headerPath})
}

#Gets path to a private header
#Returns corresponding actual private header path
defineReplace(getActualPrivateHeader) {
    headerPath=$${1}
    headerContents=$$cat($${headerPath})
    isEmpty(headerContents) {
        headerPath=
    } else:!equals(headerContents, $$replace(headerContents, "\\.\\./\\.\\./", "")) {
        headerPath=$$replace(headerContents, "$${LITERAL_HASH}include", "")
        headerPath=$$replace(headerPath, "\\.\\./\\.\\./", "")
        headerPath=$$replace(headerPath, "\"", "")
        headerPath=$${PWD}/$${headerPath}
    }
    return($${headerPath})
}

#Returns a list of actual headers' paths to which headers point
defineReplace(getActualHeaders) {
    headerPaths=$$files($${PWD}/include/*)
    actualHeaderPaths=
    for(headerPath, headerPaths) {
        actualHeaderPath=$$getActualHeader($${headerPath})
        !isEmpty(actualHeaderPath):!equals(actualHeaderPath, $${PWD}/):actualHeaderPaths+=$${actualHeaderPath}
    }
    return($${actualHeaderPaths})
}

#Returns a list of actual private headers' paths to which headers point
defineReplace(getActualPrivateHeaders) {
    headerPaths=$$files($${PWD}/include/private/*)
    actualHeaderPaths=
    for(headerPath, headerPaths) {
        actualHeaderPath=$$getActualPrivateHeader($${headerPath})
        !isEmpty(actualHeaderPath):!equals(actualHeaderPath, $${PWD}/):actualHeaderPaths+=$${actualHeaderPath}
    }
    return($${actualHeaderPaths})
}

!contains(CONFIG, tsmp_no_headers) {
    #Global
    tsmpInstallsHeaders.files=$$getActualHeaders()
    tsmpInstallsHeaders.path=$${TSMP_HEADERS_INSTALLS_PATH}
    INSTALLS += tsmpInstallsHeaders
    contains(CONFIG, tsmp_private_headers) {
        tsmpInstallsPrivateHeaders.files=$$getActualPrivateHeaders()
        tsmpInstallsPrivateHeaders.path=$${TSMP_HEADERS_INSTALLS_PATH}/private
        INSTALLS += tsmpInstallsPrivateHeaders
    }
    #Depend
    tsmpInstallsDepend.files=depend.pri
    tsmpInstallsDepend.path=$${TSMP_RESOURCES_INSTALLS_PATH}
    INSTALLS += tsmpInstallsDepend
}

} #end !contains(CONFIG, tsmp_no_install)
