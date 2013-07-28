#Include this file in your project if you are using TeXSample as an external library set
#No source files will be added to your project

#Gets module short name, for example "core", "widgets", etc.
#Returns corresponding full module name, for example "TeXSampleCore", "TeXSampleWidgets", etc.
defineReplace(fullTexsampleModuleName) {
    shortName=$${1}
    fullName=
    equals(shortName, core):fullName=TeXSampleCore
    equals(shortName, widgets):fullName=TeXSampleWidgets
    return($${fullName})
}

#Gets short module name, for example "core", "widgets", etc.
#Returns corresponding module subdir, for example "corelib", "widgets", etc.
defineReplace(texsampleModuleSubdir) {
    fullName=$${1}
    moduleSubdir=
    equals(fullName, core):moduleSubdir=corelib
    else:equals(fullName, widgets):moduleSubdir=widgets
    return($${moduleSubdir})
}

#Defining TeXSample subdir name
isEmpty(TSMP_SUBDIR_NAME):TSMP_SUBDIR_NAME=texsample

#Searching for headers
texsampleHeadersPath=
mac:exists($${PWD}/../Headers):texsampleHeadersPath=$${PWD}/../Headers
else:unix:!mac:exists($${PWD}/../../include/texsample):texsampleHeadersPath=$${PWD}/../../include/texsample
else:exists($${PWD}/include):texsampleHeadersPath=$${PWD}/include
isEmpty(texsampleHeadersPath):error("TeXSample headers not found")
#Searching for libraries
texsampleLibsPath=
texsampleLibsOneFolder=
mac:exists($${PWD}/../Frameworks) {
    texsampleLibsPath=$${PWD}/../Frameworks
    texsampleLibsOneFolder=true
}
else:exists($${PWD}/lib) {
    texsampleLibsPath=$${PWD}/lib
    texsampleLibsOneFolder=true
}
else:exists($${OUT_PWD}/$${TSMP_SUBDIR_NAME}/src):texsampleLibsPath=$${OUT_PWD}/$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../$${TSMP_SUBDIR_NAME}/src):texsampleLibsPath=$${OUT_PWD}/../$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../../$${TSMP_SUBDIR_NAME}/src):texsampleLibsPath=$${OUT_PWD}/../../$${TSMP_SUBDIR_NAME}/src
else:exists($${OUT_PWD}/../../../$${TSMP_SUBDIR_NAME}/src) {
    texsampleLibsPath=$${OUT_PWD}/../../../$${TSMP_SUBDIR_NAME}/src
}
else:texsampleLibsOneFolder=true

win32 {
    #If CONFIG contains "release" or "debug", set special suffix for libs' path
    releaseDebugSuffix=
    CONFIG(release, debug|release):releaseDebugSuffix=/release
    CONFIG(debug, debug|release):releaseDebugSuffix=/debug
    #Set suffix for libraries names
    libNameSuffix=1
}

#Gets short module name, for example "core", "widgets", etc.
#Appends corresponding paths to DEPENDPATH, INCLUDEPATH and LIBS variables
defineTest(addTexsampleModule) {
    shortName=$${1}
    fullName=$$fullTexsampleModuleName($${shortName})
    INCLUDEPATH *= $${texsampleHeadersPath}/$${fullName}
    DEPENDPATH *= $${texsampleHeadersPath}/$${fullName}
    !isEmpty(texsampleLibsPath) {
        texsampleModuleSubdir=
        isEmpty(texsampleLibsOneFolder):texsampleModuleSubdir=/$$texsampleModuleSubdir($${shortName})
        texsampleFinalLibPath=$${texsampleLibsPath}$${texsampleModuleSubdir}$${releaseDebugSuffix}
        !exists($${texsampleFinalLibPath}):texsampleFinalLibPath=$${texsampleLibsPath}$${texsampleModuleSubdir}
        mac:contains(CONFIG, lib_bundle) {
            LIBS *= -F$${texsampleFinalLibPath}/ -framework $${fullName}
        } else {
            LIBS *= -L$${texsampleFinalLibPath}/ -l$${fullName}$${libNameSuffix}
        }
    } else {
        mac:LIBS *= -framework $${fullName}
        else:LIBS *= -l$${fullName}$${libNameSuffix}
    }
    export(INCLUDEPATH)
    export(DEPENDPATH)
    export(LIBS)
}

#Appending headers base dir to INCLUDEPATH and DEPENDPATH variables
INCLUDEPATH *= $${texsampleHeadersPath}
DEPENDPATH *= $${texsampleHeadersPath}

#Replaces "all" meta-module with the list of all TeXSample modules
contains(TSMP, all) {
    TSMP *= \
        core \
        widgets
}

#Adds required Qt, BeQt and TeXSample modules (on which other included modules depend)
contains(TSMP, core) {
    QT *= core concurrent
    BEQT *= core
}
contains(TSMP, widgets) {
    QT *= core concurrent gui widgets 
    BEQT *= core widgets
    TSMP *= core
}

#Workaround for proper linking when building statically
contains(TSMP, widgets):TSMP_ORDERED += widgets
contains(TSMP, core):TSMP_ORDERED += core

#Adds corresponding headers' and libs' paths for each valid TeXSample module contained in TSMP variable
for(shortName, TSMP_ORDERED) {
    addTexsampleModule($${shortName})
}
