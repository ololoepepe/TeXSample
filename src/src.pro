TEMPLATE = subdirs

SUBDIRS = corelib

!contains(TSMP_CONFIG, no_widgets) {
    SUBDIRS += widgets
    widgets.depends = corelib
}

TRANSLATIONS += ../translations/texsample_ru.ts
