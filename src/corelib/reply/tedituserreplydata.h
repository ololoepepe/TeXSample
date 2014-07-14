#ifndef TEDITUSERREPLYDATA_H
#define TEDITUSERREPLYDATA_H

class TEditUserReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditUserReplyData ==========================
============================================================================*/

class TEditUserReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditUserReplyData)
public:
    explicit TEditUserReplyData();
    TEditUserReplyData(const TEditUserReplyData &other);
    ~TEditUserReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TEditUserReplyData &operator =(const TEditUserReplyData &other);
    bool operator ==(const TEditUserReplyData &other) const;
    bool operator !=(const TEditUserReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditUserReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditUserReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditUserReplyData &data);
};

Q_DECLARE_METATYPE(TEditUserReplyData)

#endif // TEDITUSERREPLYDATA_H
