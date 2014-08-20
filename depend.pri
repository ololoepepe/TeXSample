#Include this file in your project if you are using TeXSample as an external library set
#No source files will be added to your project

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

#Defining TeXSample subdir name
isEmpty(TSMP_SUBDIR_NAME):TSMP_SUBDIR_NAME=texsample

#Searching for headers
texsampleHeadersPath=$${PWD}/../../include/$${TSMP_SUBDIR_NAME}
!exists($${texsampleHeadersPath}):error("TeXSample headers not found")

#Searching for libraries
texsampleLibsPath=$${PWD}/../../lib
!exists($${texsampleLibsPath}):error("TeXSample libs not found")

win32 {
    #Set suffix for libraries names
    libNameSuffix=2
}

#Gets short module name, for example "core", "widgets", etc.
#Appends corresponding paths to DEPENDPATH, INCLUDEPATH and LIBS variables
defineTest(addTexsampleModule) {
    shortName=$${1}
    fullName=$$fullTexsampleModuleName($${shortName})
    INCLUDEPATH *= $${texsampleHeadersPath}/$${fullName}
    DEPENDPATH *= $${texsampleHeadersPath}/$${fullName}
    LIBS *= -L$${texsampleLibsPath}/ -l$${fullName}$${libNameSuffix}
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
    greaterThan(QT_MAJOR_VERSION, 4):QT *= concurrent widgets
    BEQT *= core widgets
    TSMP *= core
}
contains(TSMP, networkwidgets) {
    QT *= core gui network
    greaterThan(QT_MAJOR_VERSION, 4):QT *= concurrent widgets
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
