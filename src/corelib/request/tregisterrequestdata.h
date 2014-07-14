#ifndef TREGISTERREQUESTDATA_H
#define TREGISTERREQUESTDATA_H

class TRegisterRequestDataPrivate;

class BUuid;

class QByteArray;
class QDataStream;
class QDebug;
class QImage;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRegisterRequestData ========================
============================================================================*/

class T_CORE_EXPORT TRegisterRequestData : public BBase
{
    B_DECLARE_PRIVATE(TRegisterRequestData)
public:
    explicit TRegisterRequestData();
    TRegisterRequestData(const TRegisterRequestData &other);
    ~TRegisterRequestData();
public:
    QImage avatar() const;
    void clear();
    QString email() const;
    QByteArray encryptedPassword() const;
    BUuid inviteCode() const;
    bool isValid() const;
    QString login() const;
    QString name() const;
    QString patronymic() const;
    void setAvatar(const QImage &avatar);
    void setEmail(const QString &email);
    void setInviteCode(const QString &inviteCode);
    void setLogin(const QString &login);
    void setName(const QString &name);
    void setPassword(const QString &password);
    void setPatronymic(const QString &patronymic);
    void setSurename(const QString &surename);
    QString surename() const;
public:
    TRegisterRequestData &operator =(const TRegisterRequestData &other);
    bool operator ==(const TRegisterRequestData &other) const;
    bool operator !=(const TRegisterRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRegisterRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRegisterRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TRegisterRequestData &data);
};

Q_DECLARE_METATYPE(TRegisterRequestData)

#endif // TREGISTERREQUESTDATA_H
