#Gets a file name
#Returns the given file name.
#On Windows slash characters will be replaced by backslashes
defineReplace(nativeFileName) {
    fileName=$${1}
    win32:fileName=$$replace(fileName, "/", "\\")
    return($${fileName})
}

tsmpTranslationsTs=$$files($${PWD}/*.ts)
for(fileName, tsmpTranslationsTs) {
    system(lrelease $$nativeFileName($${fileName}))
}

!contains(TSMP_CONFIG, builtin_resources) {

include(../prefix.pri)
tsmpInstallsTranslations.files=$$files($${PWD}/*.qm)
tsmpInstallsTranslations.path=$${TSMP_RESOURCES_INSTALLS_PATH}/translations
INSTALLS += tsmpInstallsTranslations

}  #end !contains(TSMP_CONFIG, builtin_resources)
