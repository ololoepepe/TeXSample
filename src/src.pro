CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS = corelib

!contains(TSMP_CONFIG, no_widgets):SUBDIRS += widgets

TRANSLATIONS += ../translations/texsample_ru.ts
