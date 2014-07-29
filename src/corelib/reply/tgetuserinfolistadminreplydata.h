#ifndef TGETUSERINFOLISTADMINREPLYDATA_H
#define TGETUSERINFOLISTADMINREPLYDATA_H

class TGetUserInfoListAdminReplyDataPrivate;

class TIdList;
class TUserInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoListAdminReplyData ==============
============================================================================*/

class T_CORE_EXPORT TGetUserInfoListAdminReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoListAdminReplyData)
public:
    explicit TGetUserInfoListAdminReplyData();
    TGetUserInfoListAdminReplyData(const TGetUserInfoListAdminReplyData &other);
    ~TGetUserInfoListAdminReplyData();
public:
    TIdList deletedUsers() const;
    TUserInfoList newUsers() const;
    void setDeletedUsers(const TIdList &deletedUsers);
    void setNewUsers(const TUserInfoList &newUsers);
public:
    TGetUserInfoListAdminReplyData &operator =(const TGetUserInfoListAdminReplyData &other);
    bool operator ==(const TGetUserInfoListAdminReplyData &other) const;
    bool operator !=(const TGetUserInfoListAdminReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoListAdminReplyData)

#endif // TGETUSERINFOLISTADMINREPLYDATA_H
