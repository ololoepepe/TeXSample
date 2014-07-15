#ifndef TGETSELFINFOREPLYDATA_H
#define TGETSELFINFOREPLYDATA_H

class TGetDelfInfoReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetDelfInfoReplyData =======================
============================================================================*/

class T_CORE_EXPORT TGetDelfInfoReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetDelfInfoReplyData)
public:
    explicit TGetDelfInfoReplyData();
    TGetDelfInfoReplyData(const TGetDelfInfoReplyData &other);
    ~TGetDelfInfoReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TGetDelfInfoReplyData &operator =(const TGetDelfInfoReplyData &other);
    bool operator ==(const TGetDelfInfoReplyData &other) const;
    bool operator !=(const TGetDelfInfoReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetDelfInfoReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetDelfInfoReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetDelfInfoReplyData &data);
};

Q_DECLARE_METATYPE(TGetDelfInfoReplyData)

#endif // TGETSELFINFOREPLYDATA_H
