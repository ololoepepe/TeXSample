#ifndef TGETSELFINFOREPLYDATA_H
#define TGETSELFINFOREPLYDATA_H

class TGetSelfInfoReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSelfInfoReplyData =======================
============================================================================*/

class T_CORE_EXPORT TGetSelfInfoReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSelfInfoReplyData)
public:
    explicit TGetSelfInfoReplyData();
    TGetSelfInfoReplyData(const TGetSelfInfoReplyData &other);
    ~TGetSelfInfoReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TGetSelfInfoReplyData &operator =(const TGetSelfInfoReplyData &other);
    bool operator ==(const TGetSelfInfoReplyData &other) const;
    bool operator !=(const TGetSelfInfoReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSelfInfoReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSelfInfoReplyData &data);
};

Q_DECLARE_METATYPE(TGetSelfInfoReplyData)

#endif // TGETSELFINFOREPLYDATA_H
