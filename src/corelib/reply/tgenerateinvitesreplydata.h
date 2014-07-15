#ifndef TGENERATEINVITESREPLYDATA_H
#define TGENERATEINVITESREPLYDATA_H

class TGenerateInvitesReplyDataPrivate;

class TInviteInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGenerateInvitesReplyData ===================
============================================================================*/

class T_CORE_EXPORT TGenerateInvitesReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGenerateInvitesReplyData)
public:
    explicit TGenerateInvitesReplyData();
    TGenerateInvitesReplyData(const TGenerateInvitesReplyData &other);
    ~TGenerateInvitesReplyData();
public:
    TInviteInfoList generatedInvites() const;
    void setGeneratedInvites(const TInviteInfoList &generatedInvites);
public:
    TGenerateInvitesReplyData &operator =(const TGenerateInvitesReplyData &other);
    bool operator ==(const TGenerateInvitesReplyData &other) const;
    bool operator !=(const TGenerateInvitesReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGenerateInvitesReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGenerateInvitesReplyData &data);
};

Q_DECLARE_METATYPE(TGenerateInvitesReplyData)

#endif // TGENERATEINVITESREPLYDATA_H
