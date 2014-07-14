#include "tapplication.h"

#include <BApplication>

#include <QString>

/*============================================================================
================================ TApplication ================================
============================================================================*/

/*============================== Public constructors =======================*/

TApplication::TApplication(int &argc, char **argv, const QString &applicationName, const QString &organizationName) :
    BApplication(argc, argv, applicationName, organizationName)
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample_translations);
    Q_INIT_RESOURCE(texsamplewidgets);
#endif
    tRegister();
}

TApplication::TApplication(int &argc, char **argv, const InitialSettings &s) :
    BApplication(argc, argv, s)
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample_translations);
    Q_INIT_RESOURCE(texsamplewidgets);
#endif
    tRegister();
}

TApplication::~TApplication()
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_CLEANUP_RESOURCE(texsample_translations);
    Q_CLEANUP_RESOURCE(texsamplewidgets);
#endif
}
