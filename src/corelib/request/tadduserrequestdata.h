#ifndef TADDUSERREQUESTDATA_H
#define TADDUSERREQUESTDATA_H

class TAddUserRequestDataPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;

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
================================ TAddUserRequestData =========================
============================================================================*/

class T_CORE_EXPORT TAddUserRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddUserRequestData)
public:
    explicit TAddUserRequestData();
    TAddUserRequestData(const TAddUserRequestData &other);
    ~TAddUserRequestData();
public:
    TAccessLevel accessLevel() const;
    QImage avatar() const;
    void clear();
    QString email() const;
    QByteArray encryptedPassword() const;
    TIdList groups() const;
    bool isValid() const;
    QString login() const;
    QString name() const;
    QString patronymic() const;
    TServiceList services() const;
    void setAccesslevel(const TAccessLevel &accessLevel);
    void setAvatar(const QImage &avatar);
    void setEmail(const QString &email);
    void setGroups(const TIdList &groups);
    void setLogin(const QString &login);
    void setName(const QString &name);
    void setPassword(const QString &password);
    void setPatronymic(const QString &patronymic);
    void setServices(const TServiceList &services);
    void setSurename(const QString &surename);
    QString surename() const;
public:
    TAddUserRequestData &operator =(const TAddUserRequestData &other);
    bool operator ==(const TAddUserRequestData &other) const;
    bool operator !=(const TAddUserRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddUserRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddUserRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAddUserRequestData &data);
};

Q_DECLARE_METATYPE(TAddUserRequestData)

#endif // TADDUSERREQUESTDATA_H
