TEMPLATE = subdirs

SUBDIRS = corelib

!contains(TSMP_CONFIG, no_network) {
    SUBDIRS += network
    network.depends = corelib
}

!contains(TSMP_CONFIG, no_widgets) {
    SUBDIRS += widgets
    widgets.depends = corelib
}

!contains(TSMP_CONFIG, no_network):!contains(TSMP_CONFIG, no_widgets):!contains(TSMP_CONFIG, no_networkwidgets) {
    SUBDIRS += networkwidgets
    networkwidgets.depends = corelib network widgets
}

TRANSLATIONS += ../translations/texsample_ru.ts
