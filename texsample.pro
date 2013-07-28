CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS = src

##############################################################################
################################ Generating translations #####################
##############################################################################

#Gets a file name
#Returns the given file name.
#On Windows slash characters will be replaced by backslashes
defineReplace(nativeFileName) {
    fileName=$${1}
    win32:fileName=$$replace(fileName, "/", "\\")
    return($${fileName})
}

tsmpTranslationsTs=$$files($${PWD}/translations/*.ts)
for(fileName, tsmpTranslationsTs) {
    system(lrelease $$nativeFileName($${fileName}))
}

##############################################################################
################################ Installing ##################################
##############################################################################

!contains(TSMP_CONFIG, no_install) {

include(prefix.pri)

##############################################################################
################################ Headers #####################################
##############################################################################

#Gets contents of an .h header
#Returns the corresponding actual header path
defineReplace(getActualHeaderInternal) {
    headerContents=$${1}
    actualHeader=$$replace(headerContents, "$${LITERAL_HASH}include", "")
    actualHeader=$$replace(actualHeader, "\\.\\./\\.\\./", "")
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
    } else:!equals(headerContents, $$replace(headerContents, "\\.\\./\\.\\./", "")) {
        headerPath=$$getActualHeaderInternal($${headerContents})
    } else:!equals(headerContents, $$replace(headerContents, "\\.\\./", "")) {
        #Getting corresponding header in another include subdirectory
        headerPath=$$replace(headerContents, "$${LITERAL_HASH}include", "")
        headerPath=$$replace(headerPath, "\\.\\./", "")
        headerPath=$$replace(headerPath, "\"", "")
        #Getting the actual header
        headerContents=$$cat($${PWD}/include/$${headerPath})
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
    } else:!equals(headerContents, $$replace(headerContents, "\\.\\./\\.\\./\\.\\./", "")) {
        headerPath=$$replace(headerContents, "$${LITERAL_HASH}include", "")
        headerPath=$$replace(headerPath, "\\.\\./\\.\\./\\.\\./", "")
        headerPath=$$replace(headerPath, "\"", "")
        headerPath=$${PWD}/$${headerPath}
    }
    return($${headerPath})
}

#Gets include subdirectory name
#Returns a list of actual headers' paths to which headers in the given subdir point
defineReplace(getActualHeaders) {
    subdirName=$${1}
    headerPaths=$$files($${PWD}/include/$${subdirName}/*)
    actualHeaderPaths=
    for(headerPath, headerPaths) {
        actualHeaderPath=$$getActualHeader($${headerPath})
        !isEmpty(actualHeaderPath):!equals(actualHeaderPath, $${PWD}/):actualHeaderPaths+=$${actualHeaderPath}
    }
    return($${actualHeaderPaths})
}

#Gets include subdirectory name
#Returns a list of actual private headers' paths to which headers in the given subdir point
defineReplace(getActualPrivateHeaders) {
    subdirName=$${1}
    headerPaths=$$files($${PWD}/include/$${subdirName}/private/*)
    actualHeaderPaths=
    for(headerPath, headerPaths) {
        actualHeaderPath=$$getActualPrivateHeader($${headerPath})
        !isEmpty(actualHeaderPath):!equals(actualHeaderPath, $${PWD}/):actualHeaderPaths+=$${actualHeaderPath}
    }
    return($${actualHeaderPaths})
}

!contains(TSMP_CONFIG, no_headers) {
    #Global
    tsmpInstallsHeadersGlobal.files=$$getActualHeaders(TeXSample)
    tsmpInstallsHeadersGlobal.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSample
    INSTALLS += tsmpInstallsHeadersGlobal
    #Core
    tsmpInstallsHeadersCore.files=$$getActualHeaders(TeXSampleCore)
    tsmpInstallsHeadersCore.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleCore
    INSTALLS += tsmpInstallsHeadersCore
    contains(TSMP_CONFIG, private_headers) {
        tsmpInstallsPrivateHeadersCore.files=$$getActualPrivateHeaders(TeXSampleCore)
        tsmpInstallsPrivateHeadersCore.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleCore/private
        INSTALLS += tsmpInstallsPrivateHeadersCore
    }
    #Widgets
    !contains(TSMP_CONFIG, no_widgets) {
        tsmpInstallsHeadersWidgets.files=$$getActualHeaders(TeXSampleWidgets)
        tsmpInstallsHeadersWidgets.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleWidgets
        INSTALLS += tsmpInstallsHeadersWidgets
        contains(TSMP_CONFIG, private_headers) {
            tsmpInstallsPrivateHeadersWidgets.files=$$getActualPrivateHeaders(TeXSample)
            tsmpInstallsPrivateHeadersWidgets.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleWidgets/private
            INSTALLS += tsmpInstallsPrivateHeadersWidgets
        }
    }
    #Depend
    tsmpInstallsDepend.files=depend.pri
    tsmpInstallsDepend.path=$${TSMP_RESOURCES_INSTALLS_PATH}
    INSTALLS += tsmpInstallsDepend
}

##############################################################################
################################ Translations ################################
##############################################################################

!contains(TSMP_CONFIG, builtin_resources) {
    tsmpInstallsTranslations.files=$$files($${PWD}/translations/*.qm)
    tsmpInstallsTranslations.path=$${TSMP_RESOURCES_INSTALLS_PATH}/translations
    INSTALLS += tsmpInstallsTranslations
}

} #end !contains(TSMP_CONFIG, no_install)
