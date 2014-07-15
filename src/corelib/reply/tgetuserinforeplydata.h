#ifndef TGETUSERINFOREPLYDATA_H
#define TGETUSERINFOREPLYDATA_H

class TGetUserInfoReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoReplyData =======================
============================================================================*/

class T_CORE_EXPORT TGetUserInfoReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoReplyData)
public:
    explicit TGetUserInfoReplyData();
    TGetUserInfoReplyData(const TGetUserInfoReplyData &other);
    ~TGetUserInfoReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TGetUserInfoReplyData &operator =(const TGetUserInfoReplyData &other);
    bool operator ==(const TGetUserInfoReplyData &other) const;
    bool operator !=(const TGetUserInfoReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoReplyData)

#endif // TGETUSERINFOREPLYDATA_H
