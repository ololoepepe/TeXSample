#ifndef TINVITEINFO_H
#define TINVITEINFO_H

class TInviteInfoPrivate;

class TIdList;
class TServiceList;

class BUuid;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TInviteInfo =================================
============================================================================*/

class T_CORE_EXPORT TInviteInfo : public BBase
{
    B_DECLARE_PRIVATE(TInviteInfo)
public:
    explicit TInviteInfo();
    TInviteInfo(const TInviteInfo &other);
    ~TInviteInfo();
public:
    void clear();
    BUuid code() const;
    QDateTime creationDateTime() const;
    QDateTime expirationDateTime() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    quint64 ownerId() const;
    QString ownerLogin() const;
    TServiceList services() const;
    void setCode(const BUuid &code);
    void setCreationDateTime(const QDateTime &dt);
    void setExpirationDateTime(const QDateTime &dt);
    void setGroups(const TIdList &groups);
    void setId(quint64 id);
    void setOwnerId(quint64 id);
    void setOwnerLogin(const QString &login);
    void setServices(const TServiceList &services);
public:
    TInviteInfo &operator =(const TInviteInfo &other);
    bool operator ==(const TInviteInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TInviteInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TInviteInfo &info);
    friend QDebug operator <<(QDebug dbg, const TInviteInfo &info);
};

Q_DECLARE_METATYPE(TInviteInfo)

#endif // TINVITEINFO_H
