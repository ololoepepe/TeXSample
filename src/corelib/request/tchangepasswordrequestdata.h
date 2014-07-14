#ifndef TCHANGEPASSWORDREQUESTDATA_H
#define TCHANGEPASSWORDREQUESTDATA_H

class TChangePasswordRequestDataPrivate;

class QByteArray;
class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TChangePasswordRequestData ==================
============================================================================*/

class T_CORE_EXPORT TChangePasswordRequestData : public BBase
{
    B_DECLARE_PRIVATE(TChangePasswordRequestData)
public:
    explicit TChangePasswordRequestData();
    TChangePasswordRequestData(const TChangePasswordRequestData &other);
    ~TChangePasswordRequestData();
public:
    void clear();
    bool isValid() const;
    QByteArray newPassword() const;
    QByteArray oldPassword() const;
    void setNewPassword(const QString &password);
    void setOldPassword(const QString &password);
public:
    TChangePasswordRequestData &operator =(const TChangePasswordRequestData &other);
    bool operator ==(const TChangePasswordRequestData &other) const;
    bool operator !=(const TChangePasswordRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TChangePasswordRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TChangePasswordRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TChangePasswordRequestData &data);
};

Q_DECLARE_METATYPE(TChangePasswordRequestData)

#endif // TCHANGEPASSWORDREQUESTDATA_H
