!contains(TSMP_CONFIG, no_install):!contains(TSMP_CONFIG, no_headers) {

include(../prefix.pri)

#Gets contents of an .h header
#Returns the corresponding actual header path
defineReplace(getActualHeaderPathInternal) {
    headerContents=$${1}
    actualHeader=$$replace(headerContents, "$${LITERAL_HASH}include", "")
    actualHeader=$$replace(actualHeader, "\\.\\./\\.\\./", "")
    actualHeader=$$replace(actualHeader, "\"", "")
    return($${PWD}/../$${actualHeader})
}

#Gets include subdirectory name
#Returns a list of actual headers' paths to which headers in the given subdir point
defineReplace(getActualHeaderPaths) {
    subdirName=$${1}
    headerPaths=$$files($${PWD}/$${subdirName}/*)
    actualHeaderPaths=
    for(headerPath, headerPaths) {
        headerContents=$$cat($${headerPath})
        !isEmpty(headerContents) {
            !equals(headerContents, $$replace(headerContents, "\\.\\./\\.\\./", "")) {
                headerPath=$$getActualHeaderPathInternal($${headerContents})
            } else:!equals(headerContents, $$replace(headerContents, "\\.\\./", "")) {
                #Getting corresponding header in another include subdirectory
                headerPath=$$replace(headerContents, "$${LITERAL_HASH}include", "")
                headerPath=$$replace(headerPath, "\\.\\./", "")
                headerPath=$$replace(headerPath, "\"", "")
                #Getting the actual header
                headerContents=$$cat($${PWD}/../$${headerPath})
                headerPath=$$getActualHeaderPathInternal($${headerContents})
            }
            #TODO: !equals(headerPath, $${PWD}/../) it dirty! Fix it
            !isEmpty(headerPath):!equals(headerPath, $${PWD}/../):actualHeaderPaths+=$${headerPath}
        }
    }
    return($${actualHeaderPaths})
}

#Gets include subdirectory name
#Returns a list of actual private headers' paths to which headers in the given subdir point
defineReplace(getActualPrivateHeaderPaths) {
    subdirName=$${1}
    headerPaths=$$files($${PWD}/$${subdirName}/private/*)
    actualHeaderPaths=
    for(headerPath, headerPaths) {
        headerContents=$$cat($${headerPath})
        !isEmpty(headerContents):!equals(headerContents, $$replace(headerContents, "\\.\\./\\.\\./\\.\\./", "")) {
            headerPath=$$replace(headerContents, "$${LITERAL_HASH}include", "")
            headerPath=$$replace(headerPath, "\\.\\./\\.\\./\\.\\./", "")
            headerPath=$$replace(headerPath, "\"", "")
            headerPath=$${PWD}/../$${headerPath}
            #TODO: !equals(headerPath, $${PWD}/../) it dirty! Fix it
            !equals(headerPath, $${PWD}/../):actualHeaderPaths+=$${headerPath}
        }
    }
    return($${actualHeaderPaths})
}

#Global
tsmpInstallsHeadersGlobal.files=$$getActualHeaderPaths(TeXSample)
tsmpInstallsHeadersGlobal.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSample
INSTALLS += tsmpInstallsHeadersGlobal

#Core
tsmpInstallsHeadersCore.files=$$getActualHeaderPaths(TeXSampleCore)
tsmpInstallsHeadersCore.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleCore
INSTALLS += tsmpInstallsHeadersCore
contains(TSMP_CONFIG, private_headers) {
    tsmpInstallsPrivateHeadersCore.files=$$getActualPrivateHeaderPaths(TeXSampleCore)
    tsmpInstallsPrivateHeadersCore.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleCore/private
    INSTALLS += tsmpInstallsPrivateHeadersCore
}

#Widgets
!contains(TSMP_CONFIG, no_widgets) {
    tsmpInstallsHeadersWidgets.files=$$getActualHeaderPaths(TeXSampleWidgets)
    tsmpInstallsHeadersWidgets.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleWidgets
    INSTALLS += tsmpInstallsHeadersWidgets
    contains(TSMP_CONFIG, private_headers) {
        tsmpInstallsPrivateHeadersWidgets.files=$$getActualPrivateHeaderPaths(TeXSampleWidgets)
        tsmpInstallsPrivateHeadersWidgets.path=$${TSMP_HEADERS_INSTALLS_PATH}/TeXSampleWidgets/private
        INSTALLS += tsmpInstallsPrivateHeadersWidgets
    }
}

} #end !contains(TSMP_CONFIG, no_install):!contains(TSMP_CONFIG, no_headers)
