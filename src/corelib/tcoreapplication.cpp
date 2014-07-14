#include "tcoreapplication.h"

#include <BCoreApplication>

#include <QString>

/*============================================================================
================================ TCoreApplication ============================
============================================================================*/

/*============================== Public constructors =======================*/

TCoreApplication::TCoreApplication(int &argc, char **argv, const QString &applicationName,
                                   const QString &organizationName) :
    BCoreApplication(argc, argv, applicationName, organizationName)
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample_translations);
#endif
    tRegister();
}

TCoreApplication::TCoreApplication(int &argc, char **argv, const InitialSettings &s) :
    BCoreApplication(argc, argv, s)
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample_translations);
#endif
    tRegister();
}

TCoreApplication::~TCoreApplication()
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_CLEANUP_RESOURCE(texsample_translations);
#endif
}
