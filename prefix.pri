isEmpty(TSMP_PREFIX) {
    mac|unix {
        TSMP_PREFIX=/usr/local
    } else:win32 {
        TSMP_PREFIX=$$(systemdrive)/PROGRA~1/TeXSample
    }
    export(TSMP_PREFIX)
}

isEmpty(TSMP_HEADERS_INSTALLS_PATH) {
    TSMP_HEADERS_INSTALLS_PATH=$${TSMP_PREFIX}/include/texsample
    export(TSMP_HEADERS_INSTALLS_PATH)
}

isEmpty(TSMP_LIBS_INSTALLS_PATH) {
    TSMP_LIBS_INSTALLS_PATH=$${TSMP_PREFIX}/lib
    export(TSMP_LIBS_INSTALLS_PATH)
}

isEmpty(TSMP_RESOURCES_INSTALLS_PATH) {
    TSMP_RESOURCES_INSTALLS_PATH=$${TSMP_PREFIX}/share/texsample
    export(TSMP_RESOURCES_INSTALLS_PATH)
}
