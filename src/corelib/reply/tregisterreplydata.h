#ifndef TREGISTERREPLYDATA_H
#define TREGISTERREPLYDATA_H

class TRegisterReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRegisterReplyData ==========================
============================================================================*/

class TRegisterReplyData : public BBase
{
    B_DECLARE_PRIVATE(TRegisterReplyData)
public:
    explicit TRegisterReplyData();
    TRegisterReplyData(const TRegisterReplyData &other);
    ~TRegisterReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TRegisterReplyData &operator =(const TRegisterReplyData &other);
    bool operator ==(const TRegisterReplyData &other) const;
    bool operator !=(const TRegisterReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRegisterReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRegisterReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TRegisterReplyData &data);
};

Q_DECLARE_METATYPE(TRegisterReplyData)

#endif // TREGISTERREPLYDATA_H
