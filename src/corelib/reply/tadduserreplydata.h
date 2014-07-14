#ifndef TADDUSERREPLYDATA_H
#define TADDUSERREPLYDATA_H

class TAddUserReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddUserReplyData ===========================
============================================================================*/

class TAddUserReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddUserReplyData)
public:
    explicit TAddUserReplyData();
    TAddUserReplyData(const TAddUserReplyData &other);
    ~TAddUserReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TAddUserReplyData &operator =(const TAddUserReplyData &other);
    bool operator ==(const TAddUserReplyData &other) const;
    bool operator !=(const TAddUserReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddUserReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddUserReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAddUserReplyData &data);
};

Q_DECLARE_METATYPE(TAddUserReplyData)

#endif // TADDUSERREPLYDATA_H
