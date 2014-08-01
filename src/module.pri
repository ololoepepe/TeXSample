VERSION = 2.0.0
VER_MAJ = 2
VER_MIN = 0
VER_PAT = 0

#Gets module short name, for example "core", "widgets", etc.
#Returns corresponding full module name, for example "TeXSampleCore", "TeXSampleWidgets", etc.
defineReplace(fullTexsampleModuleName) {
    shortName=$${1}
    fullName=
    equals(shortName, core):fullName=TeXSampleCore
    equals(shortName, network):fullName=TeXSampleNetwork
    equals(shortName, widgets):fullName=TeXSampleWidgets
    equals(shortName, networkwidgets):fullName=TeXSampleNetworkWidgets
    return($${fullName})
}

#Gets short module name, for example "core", "widgets", etc.
#Returns corresponding module subdir, for example "corelib", "widgets", etc.
defineReplace(texsampleModuleSubdir) {
    fullName=$${1}
    moduleSubdir=
    equals(fullName, core):moduleSubdir=corelib
    equals(fullName, network):moduleSubdir=network
    equals(fullName, widgets):moduleSubdir=widgets
    equals(fullName, networkwidgets):moduleSubdir=networkwidgets
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
    LIBS *= -L$${libFinalPath} -l$${fullName}$${libNameSuffix}
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
        network \
        widgets \
        networkwidgets
}

#Adds required Qt, BeQt and TeXSample modules (on which other included modules depend)
contains(TSMP, core) {
    QT *= core gui
    greaterThan(QT_MAJOR_VERSION, 4):QT *= concurrent
    BEQT *= core
}
contains(TSMP, network) {
    QT *= core gui network
    greaterThan(QT_MAJOR_VERSION, 4):QT *= concurrent
    BEQT *= core network
}
contains(TSMP, widgets) {
    QT *= core gui
    greaterThan(QT_MAJOR_VERSION, 4):QT *= widgets concurrent
    BEQT *= core widgets
    TSMP *= core
}
contains(TSMP, networkwidgets) {
    QT *= core gui network
    greaterThan(QT_MAJOR_VERSION, 4):QT *= widgets concurrent
    BEQT *= core network widgets networkwidgets
    TSMP *= core network widgets
}

#Workaround for proper linking when building statically
contains(TSMP, networkwidgets):TSMP_ORDERED += networkwidgets
contains(TSMP, widgets):TSMP_ORDERED += widgets
contains(TSMP, network):TSMP_ORDERED += network
contains(TSMP, core):TSMP_ORDERED += core

#Adds corresponding headers' and libs' paths for each valid TeXSample module contained in TSMP variable
for(shortName, TSMP_ORDERED) {
    addTexsampleModule($${shortName})
}

isEmpty(BEQT_PREFIX) {
    mac|unix {
        BEQT_PREFIX=/usr
    } else:win32 {
        BEQT_PREFIX=$$(systemdrive)/PROGRA~1/BeQt
    }
}
include($${BEQT_PREFIX}/share/beqt/depend.pri)
