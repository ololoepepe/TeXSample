#ifndef TRECOVERACCOUNTREQUESTDATA_H
#define TRECOVERACCOUNTREQUESTDATA_H

class TRecoverAccountRequestDataPrivate;

class BUuid;

class QByteArray;
class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRecoverAccountRequestData ==================
============================================================================*/

class T_CORE_EXPORT TRecoverAccountRequestData : public BBase
{
    B_DECLARE_PRIVATE(TRecoverAccountRequestData)
public:
    explicit TRecoverAccountRequestData();
    TRecoverAccountRequestData(const TRecoverAccountRequestData &other);
    ~TRecoverAccountRequestData();
public:
    void clear();
    bool isValid() const;
    QByteArray password() const;
    BUuid recoveryCode() const;
    void setPassword(const QString &password);
    void setRecoveryCode(const QString &code);
public:
    TRecoverAccountRequestData &operator =(const TRecoverAccountRequestData &other);
    bool operator ==(const TRecoverAccountRequestData &other) const;
    bool operator !=(const TRecoverAccountRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRecoverAccountRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRecoverAccountRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TRecoverAccountRequestData &data);
};

Q_DECLARE_METATYPE(TRecoverAccountRequestData)

#endif // TRECOVERACCOUNTREQUESTDATA_H
