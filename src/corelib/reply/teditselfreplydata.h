#ifndef TEDITSELFREPLYDATA_H
#define TEDITSELFREPLYDATA_H

class TEditSelfReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSelfReplyData ==========================
============================================================================*/

class T_CORE_EXPORT TEditSelfReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditSelfReplyData)
public:
    explicit TEditSelfReplyData();
    TEditSelfReplyData(const TEditSelfReplyData &other);
    ~TEditSelfReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TEditSelfReplyData &operator =(const TEditSelfReplyData &other);
    bool operator ==(const TEditSelfReplyData &other) const;
    bool operator !=(const TEditSelfReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSelfReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSelfReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSelfReplyData &data);
};

Q_DECLARE_METATYPE(TEditSelfReplyData)

#endif // TEDITSELFREPLYDATA_H
