#ifndef TGETUSERINFOADMINREPLYDATA_H
#define TGETUSERINFOADMINREPLYDATA_H

class TGetUserInfoAdminReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoAdminReplyData ==================
============================================================================*/

class TGetUserInfoAdminReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoAdminReplyData)
public:
    explicit TGetUserInfoAdminReplyData();
    TGetUserInfoAdminReplyData(const TGetUserInfoAdminReplyData &other);
    ~TGetUserInfoAdminReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TGetUserInfoAdminReplyData &operator =(const TGetUserInfoAdminReplyData &other);
    bool operator ==(const TGetUserInfoAdminReplyData &other) const;
    bool operator !=(const TGetUserInfoAdminReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoAdminReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoAdminReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoAdminReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoAdminReplyData)

#endif // TGETUSERINFOADMINREPLYDATA_H
