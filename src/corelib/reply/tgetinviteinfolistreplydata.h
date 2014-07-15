#ifndef TGETINVITEINFOLISTREPLYDATA_H
#define TGETINVITEINFOLISTREPLYDATA_H

class TGetInviteInfoListReplyDataPrivate;

class TIdList;
class TInviteInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetInviteInfoListReplyData =================
============================================================================*/

class T_CORE_EXPORT TGetInviteInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetInviteInfoListReplyData)
public:
    explicit TGetInviteInfoListReplyData();
    TGetInviteInfoListReplyData(const TGetInviteInfoListReplyData &other);
    ~TGetInviteInfoListReplyData();
public:
    TIdList deletedInvites() const;
    TInviteInfoList newInvites() const;
    void setDeletedInvites(const TIdList &deletedInvites);
    void setNewInvites(const TInviteInfoList &newInvites);
public:
    TGetInviteInfoListReplyData &operator =(const TGetInviteInfoListReplyData &other);
    bool operator ==(const TGetInviteInfoListReplyData &other) const;
    bool operator !=(const TGetInviteInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetInviteInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetInviteInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetInviteInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetInviteInfoListReplyData)

#endif // TGETINVITEINFOLISTREPLYDATA_H
