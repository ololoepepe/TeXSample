#ifndef TEDITUSERREQUESTDATA_H
#define TEDITUSERREQUESTDATA_H

class TEditUserRequestDataPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;
class TUserIdentifier;

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
================================ TEditUserRequestData ========================
============================================================================*/

class T_CORE_EXPORT TEditUserRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditUserRequestData)
public:
    explicit TEditUserRequestData();
    TEditUserRequestData(const TEditUserRequestData &other);
    ~TEditUserRequestData();
public:
    TAccessLevel accessLevel() const;
    QImage avatar() const;
    void clear();
    bool editAvatar() const;
    bool editEmail() const;
    bool editPassword() const;
    QString email() const;
    QByteArray encryptedPassword() const;
    TIdList groups() const;
    TUserIdentifier identifier() const;
    bool active() const;
    bool isValid() const;
    QString name() const;
    QString patronymic() const;
    TServiceList services() const;
    void setAccesslevel(const TAccessLevel &accessLevel);
    void setActive(bool active);
    void setAvatar(const QImage &avatar);
    void setEditAvatar(bool edit);
    void setEditEmail(bool edit);
    void setEditPassword(bool edit);
    void setEmail(const QString &email);
    void setGroups(const TIdList &groups);
    void setIdentifier(const TUserIdentifier &identifier);
    void setName(const QString &name);
    void setPassword(const QString &password);
    void setPatronymic(const QString &patronymic);
    void setServices(const TServiceList &services);
    void setSurename(const QString &surename);
    QString surename() const;
public:
    TEditUserRequestData &operator =(const TEditUserRequestData &other);
    bool operator ==(const TEditUserRequestData &other) const;
    bool operator !=(const TEditUserRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditUserRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditUserRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditUserRequestData &data);
};

Q_DECLARE_METATYPE(TEditUserRequestData)

#endif // TEDITUSERREQUESTDATA_H
