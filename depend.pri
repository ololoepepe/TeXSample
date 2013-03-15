#Include this file in your project if you are using TeXSample as an external library set
#No source files will be added to your project

#Defining TeXSample subdir name
isEmpty(TSMP_SUBDIR_NAME):TSMP_SUBDIR_NAME=texsample

#Searching for headers
tsmpHeadersPath=
mac:exists($${PWD}/../Headers):tsmpHeadersPath=$${PWD}/../Headers
else:unix:!mac:exists($${PWD}/../../include/texsample):tsmpHeadersPath=$${PWD}/../../include/texsample
else:exists($${PWD}/include):tsmpHeadersPath=$${PWD}/include
isEmpty(tsmpHeadersPath):error("TeXSample headers not found")
#Searching for libraries
tsmpLibsPath=
mac:exists($${PWD}/../Frameworks):tsmpLibsPath=$${PWD}/../Frameworks
else:exists($${PWD}/lib):tsmpLibsPath=$${PWD}/lib
else:exists($${OUT_PWD}/$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/../$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../../$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/../../$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../../../$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/../../../$${TSMP_SUBDIR_NAME}/src

#If CONFIG contains "release" or "debug", set special suffix for libs' path
win32 {
    releaseDebugSuffix=
    CONFIG(release, debug|release):releaseDebugSuffix=/release
    CONFIG(debug, debug|release):releaseDebugSuffix=/debug
}

#Appending the lib to LIBS variable
!isEmpty(tsmpLibsPath) {
    mac:contains(CONFIG, lib_bundle) {
        LIBS *= -F$${tsmpLibsPath}$${releaseDebugSuffix}/ -framework TeXSample
    } else {
        LIBS *= -L$${tsmpLibsPath}$${releaseDebugSuffix}/ -lTeXSample
    }
} else {
    mac:LIBS *= -framework TeXSample
    else:LIBS *= -lTeXSample
}
export(LIBS)

#Appending headers dir to INCLUDEPATH and DEPENDPATH variables
INCLUDEPATH *= $${tsmpHeadersPath}
DEPENDPATH *= $${tsmpHeadersPath}
export(INCLUDEPATH)
export(DEPENDPATH)
