#ifndef TUSERINFO_H
#define TUSERINFO_H

class TUserInfoPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;

class QDataStream;
class QDateTime;
class QDebug;
class QImage;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

class T_CORE_EXPORT TUserInfo : public BBase
{
    B_DECLARE_PRIVATE(TUserInfo)
public:
    explicit TUserInfo();
    TUserInfo(const TUserInfo &other);
    ~TUserInfo();
public:
    TAccessLevel accessLevel() const;
    bool active() const;
    QImage avatar() const;
    void clear();
    bool containsAvatar() const;
    QString email() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    QString login() const;
    QString name() const;
    QString patronymic() const;
    QDateTime registrationDateTime() const;
    TServiceList services() const;
    void setAccessLevel(const TAccessLevel &accessLevel);
    void setActive(bool active);
    void setAvatar(const QImage &avatar);
    void setContainsAvatar(bool contains);
    void setEmail(const QString &email);
    void setGroups(const TIdList &groups);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setLogin(const QString &login);
    void setName(const QString &name);
    void setPatronymic(const QString &partonymic);
    void setRegistrationDateTime(const QDateTime &dt);
    void setServices(const TServiceList &services);
    void setSurename(const QString &surename);
    QString surename() const;
public:
    TUserInfo &operator =(const TUserInfo &other);
    bool operator ==(const TUserInfo &other) const;
    bool operator !=(const TUserInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TUserInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TUserInfo &info);
    friend QDebug operator <<(QDebug dbg, const TUserInfo &info);
};

Q_DECLARE_METATYPE(TUserInfo)

#endif // TUSERINFO_H
