VERSION = 1.0.2
VER_MAJ = 1
VER_MIN = 0
VER_PAT = 2

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

texsampleHeadersPath=$${PWD}/../include
texsampleLibsPath=$${OUT_PWD}/..

win32 {
    #If CONFIG contains "release" or "debug", set special suffix for libs' path
    releaseDebugSuffix=
    CONFIG(release, debug|release):releaseDebugSuffix=/release
    CONFIG(debug, debug|release):releaseDebugSuffix=/debug
    #Set suffix for libraries names
    libNameSuffix=$${VER_MAJ}
}

#Gets short module name, for example "core", "widgets", etc.
#Appends corresponding paths to DEPENDPATH, INCLUDEPATH and LIBS variables
defineTest(addTexsampleModule) {
    shortName=$${1}
    fullName=$$fullTexsampleModuleName($${shortName})
    INCLUDEPATH *= $${texsampleHeadersPath}/$${fullName}
    DEPENDPATH *= $${texsampleHeadersPath}/$${fullName}
    libFinalPath=$${texsampleLibsPath}/$$texsampleModuleSubdir($${shortName})$${releaseDebugSuffix}/
    mac:contains(CONFIG, lib_bundle) {
        LIBS *= -F$${libFinalPath} -framework $${fullName}
    } else {
        LIBS *= -L$${libFinalPath} -l$${fullName}$${libNameSuffix}
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
contains(TSMP,core) {
    QT *= core concurrent
    BEQT *= core
}
contains(TSMP, widgets) {
    QT *= core gui widgets concurrent
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

isEmpty(BEQT_PREFIX) {
    #TODO: Add MacOS support
    mac|unix {
        BEQT_PREFIX=/usr/share/beqt
    } else:win32 {
        BEQT_PREFIX=$$(systemdrive)/PROGRA~1/BeQt
    }
}
include($${BEQT_PREFIX}/depend.pri)
