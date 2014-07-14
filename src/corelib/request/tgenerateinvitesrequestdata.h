#ifndef TGENERATEINVITESREQUESTDATA_H
#define TGENERATEINVITESREQUESTDATA_H

class TGenerateInvitesRequestDataPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;

class QDataStream;
class QDateTime;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGenerateInvitesRequestData =================
============================================================================*/

class T_CORE_EXPORT TGenerateInvitesRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGenerateInvitesRequestData)
public:
    explicit TGenerateInvitesRequestData();
    TGenerateInvitesRequestData(const TGenerateInvitesRequestData &other);
    ~TGenerateInvitesRequestData();
public:
    TAccessLevel accessLevel() const;
    void clear();
    quint16 count() const;
    QDateTime expirationDateTime() const;
    TIdList groups() const;
    bool isValid() const;
    TServiceList services() const;
    void setAccessLevel(const TAccessLevel &accessLevel);
    void setCount(quint16 count);
    void setExpirationDateTime(const QDateTime &dt);
    void setGroups(const TIdList &groups);
    void setServices(const TServiceList &services);
public:
    TGenerateInvitesRequestData &operator =(const TGenerateInvitesRequestData &other);
    bool operator ==(const TGenerateInvitesRequestData &other) const;
    bool operator !=(const TGenerateInvitesRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGenerateInvitesRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGenerateInvitesRequestData &data);
};

Q_DECLARE_METATYPE(TGenerateInvitesRequestData)

#endif // TGENERATEINVITESREQUESTDATA_H
