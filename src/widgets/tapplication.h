#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <TeXSampleCore/TeXSampleGlobal>

#include <BApplication>

#include <QString>

#if defined(tApp)
#   undef tApp
#endif
#define tApp (static_cast<TApplication *>(BApplicationBase::binstance()))
#if defined(bApp)
#   undef bApp
#endif
#define bApp (static_cast<TApplication *>(BApplicationBase::binstance()))

/*============================================================================
================================ TApplication ================================
============================================================================*/

class T_WIDGETS_EXPORT TApplication : public BApplication
{
    Q_OBJECT
public:
    explicit TApplication(int &argc, char **argv, const QString &applicationName = QString(),
                          const QString &organizationName = QString());
    explicit TApplication(int &argc, char **argv, const InitialSettings &s);
    ~TApplication();
private:
    Q_DISABLE_COPY(TApplication)
};

#endif // TAPPLICATION_H

