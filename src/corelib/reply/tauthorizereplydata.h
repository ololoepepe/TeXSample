#ifndef TAUTHORIZEREPLYDATA_H
#define TAUTHORIZEREPLYDATA_H

class TAuthorizeReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAuthorizeReplyData =========================
============================================================================*/

class T_CORE_EXPORT TAuthorizeReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAuthorizeReplyData)
public:
    explicit TAuthorizeReplyData();
    TAuthorizeReplyData(const TAuthorizeReplyData &other);
    ~TAuthorizeReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TAuthorizeReplyData &operator =(const TAuthorizeReplyData &other);
    bool operator ==(const TAuthorizeReplyData &other) const;
    bool operator !=(const TAuthorizeReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAuthorizeReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAuthorizeReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAuthorizeReplyData &data);
};

Q_DECLARE_METATYPE(TAuthorizeReplyData)

#endif // TAUTHORIZEREPLYDATA_H
