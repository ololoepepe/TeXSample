CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS = src

include(translations/translations.pri)
include(include/include.pri)

!contains(BEQT_CONFIG, no_install) {

#Depend
tsmpInstallsDepend.files=$${PWD}/depend.pri
tsmpInstallsDepend.path=$${TSMP_RESOURCES_INSTALLS_PATH}
INSTALLS += tsmpInstallsDepend

} #end !contains(TSMP_CONFIG, no_install)
