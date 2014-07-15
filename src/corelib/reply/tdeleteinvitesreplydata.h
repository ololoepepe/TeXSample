#ifndef TDELETEINVITESREPLYDATA_H
#define TDELETEINVITESREPLYDATA_H

class TDeleteInvitesReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteInvitesReplyData =====================
============================================================================*/

class T_CORE_EXPORT TDeleteInvitesReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteInvitesReplyData)
public:
    explicit TDeleteInvitesReplyData();
    TDeleteInvitesReplyData(const TDeleteInvitesReplyData &other);
    ~TDeleteInvitesReplyData();
public:
    quint32 count() const;
    void setCount(quint32 count);
public:
    TDeleteInvitesReplyData &operator =(const TDeleteInvitesReplyData &other);
    bool operator ==(const TDeleteInvitesReplyData &other) const;
    bool operator !=(const TDeleteInvitesReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteInvitesReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteInvitesReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteInvitesReplyData)

#endif // TDELETEINVITESREPLYDATA_H
