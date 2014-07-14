#ifndef TDELETEINVITESREQUESTDATA_H
#define TDELETEINVITESREQUESTDATA_H

class TDeleteInvitesRequestDataPrivate;

class TIdList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteInvitesRequestData ===================
============================================================================*/

class T_CORE_EXPORT TDeleteInvitesRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteInvitesRequestData)
public:
    explicit TDeleteInvitesRequestData();
    TDeleteInvitesRequestData(const TDeleteInvitesRequestData &other);
    ~TDeleteInvitesRequestData();
public:
    void clear();
    TIdList ids() const;
    bool isValid() const;
    void setIds(const TIdList &ids);
public:
    TDeleteInvitesRequestData &operator =(const TDeleteInvitesRequestData &other);
    bool operator ==(const TDeleteInvitesRequestData &other) const;
    bool operator !=(const TDeleteInvitesRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteInvitesRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteInvitesRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteInvitesRequestData)

#endif // TDELETEINVITESREQUESTDATA_H
