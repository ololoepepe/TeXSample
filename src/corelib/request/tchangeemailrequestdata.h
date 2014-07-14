#ifndef TCHANGEEMAILREQUESTDATA_H
#define TCHANGEEMAILREQUESTDATA_H

class TChangeEmailRequestDataPrivate;

class QByteArray;
class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TChangeEmailRequestData =====================
============================================================================*/

class T_CORE_EXPORT TChangeEmailRequestData : public BBase
{
    B_DECLARE_PRIVATE(TChangeEmailRequestData)
public:
    explicit TChangeEmailRequestData();
    TChangeEmailRequestData(const TChangeEmailRequestData &other);
    ~TChangeEmailRequestData();
public:
    void clear();
    QString email() const;
    bool isValid() const;
    QByteArray password() const;
    void setEmail(const QString &email);
    void setPassword(const QString &password);
public:
    TChangeEmailRequestData &operator =(const TChangeEmailRequestData &other);
    bool operator ==(const TChangeEmailRequestData &other) const;
    bool operator !=(const TChangeEmailRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TChangeEmailRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TChangeEmailRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TChangeEmailRequestData &data);
};

Q_DECLARE_METATYPE(TChangeEmailRequestData)

#endif // TCHANGEEMAILREQUESTDATA_H
