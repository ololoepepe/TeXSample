#ifndef TAUTHORIZEREQUESTDATA_H
#define TAUTHORIZEREQUESTDATA_H

class TAuthorizeRequestDataPrivate;

class TClientInfo;

class QByteArray;
class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAuthorizeRequestData =======================
============================================================================*/

class T_CORE_EXPORT TAuthorizeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAuthorizeRequestData)
public:
    explicit TAuthorizeRequestData();
    TAuthorizeRequestData(const TAuthorizeRequestData &other);
    ~TAuthorizeRequestData();
public:
    void clear();
    TClientInfo clientInfo() const;
    QString identifier() const;
    bool isValid() const;
    QByteArray password() const;
    void setClientInfo(const TClientInfo &info);
    void setIdentifier(const QString &identifier);
    void setPassword(const QByteArray &password);
public:
    TAuthorizeRequestData &operator =(const TAuthorizeRequestData &other);
    bool operator ==(const TAuthorizeRequestData &other) const;
    bool operator !=(const TAuthorizeRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAuthorizeRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAuthorizeRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAuthorizeRequestData &data);
};

Q_DECLARE_METATYPE(TAuthorizeRequestData)

#endif // TAUTHORIZEREQUESTDATA_H
