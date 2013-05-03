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
tsmpLibsOneFolder=
mac:exists($${PWD}/../Frameworks):tsmpLibsPath=$${PWD}/../Frameworks
else:exists($${PWD}/lib):tsmpLibsPath=$${PWD}/lib
else:exists($${OUT_PWD}/$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/../$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../../$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/../../$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../../../$${TSMP_SUBDIR_NAME}/src):tsmpLibsPath=$${OUT_PWD}/../../../$${TSMP_SUBDIR_NAME}/src

win32 {
    #If CONFIG contains "release" or "debug", set special suffix for libs' path
    releaseDebugSuffix=
    CONFIG(release, debug|release):releaseDebugSuffix=/release
    CONFIG(debug, debug|release):releaseDebugSuffix=/debug
    #Set suffix for libraries names
    libNameSuffix=1
}

#Appending the lib to LIBS variable
!isEmpty(tsmpLibsPath) {
    tsmpFinalLibPath=$${tsmpLibsPath}$${releaseDebugSuffix}
    !exists($${tsmpFinalLibPath}):tsmpFinalLibPath=$${tsmpLibsPath}
    mac:contains(CONFIG, lib_bundle) {
        LIBS *= -F$${tsmpFinalLibPath}/ -framework TeXSample
    } else {
        LIBS *= -L$${tsmpFinalLibPath}/ -lTeXSample$${libNameSuffix}
    }
} else {
    mac:LIBS *= -framework TeXSample
    else:LIBS *= -lTeXSample$${libNameSuffix}
}
export(LIBS)

#Appending headers dir to INCLUDEPATH and DEPENDPATH variables
INCLUDEPATH *= $${tsmpHeadersPath}
DEPENDPATH *= $${tsmpHeadersPath}
export(INCLUDEPATH)
export(DEPENDPATH)
