#ifndef TCOREAPPLICATION_H
#define TCOREAPPLICATION_H

#include "tglobal.h"

#include <BCoreApplication>

#include <QString>

#define tApp (static_cast<TCoreApplication *>(BApplicationBase::binstance()))
#if defined(bApp)
#   undef bApp
#endif
#define bApp (static_cast<TApplication *>(BApplicationBase::binstance()))

/*============================================================================
================================ TApplication ================================
============================================================================*/

class T_CORE_EXPORT TCoreApplication : public BCoreApplication
{
    Q_OBJECT
public:
    explicit TCoreApplication(int &argc, char **argv, const QString &applicationName = QString(),
                          const QString &organizationName = QString());
    explicit TCoreApplication(int &argc, char **argv, const InitialSettings &s);
    ~TCoreApplication();
private:
    Q_DISABLE_COPY(TCoreApplication)
};

#endif // TCOREAPPLICATION_H

