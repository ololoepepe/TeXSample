#ifndef TSERVICE_H
#define TSERVICE_H

class TServicePrivate;

class QDataStream;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>

/*============================================================================
================================ TService ====================================
============================================================================*/

class T_CORE_EXPORT TService : public BBase
{
    B_DECLARE_PRIVATE(TService)
    Q_DECLARE_TR_FUNCTIONS(TService)
public:
    enum Service
    {
        NoService = 0,
        TexsampleService,
        ClabService
    };
public:
    static QString serviceToString(Service srv);
    static QString serviceToStringNoTr(Service srv);
public:
    TService(int srv = NoService);
    TService(const TService &other);
    ~TService();
public:
    QString toString() const;
    QString toStringNoTr() const;
public:
    TService &operator =(const TService &other);
    TService &operator =(int srv);
    bool operator ==(const TService &other) const;
    bool operator !=(const TService &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TService &srv);
    friend QDataStream &operator >>(QDataStream &stream, TService &srv);
    friend QDebug operator <<(QDebug dbg, const TService &srv);
};

Q_DECLARE_METATYPE(TService)

#endif // TSERVICE_H
