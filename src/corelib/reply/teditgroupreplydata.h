#ifndef TEDITGROUPREPLYDATA_H
#define TEDITGROUPREPLYDATA_H

class TEditGroupReplyDataPrivate;

class TGroupInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditGroupReplyData =========================
============================================================================*/

class T_CORE_EXPORT TEditGroupReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditGroupReplyData)
public:
    explicit TEditGroupReplyData();
    TEditGroupReplyData(const TEditGroupReplyData &other);
    ~TEditGroupReplyData();
public:
    TGroupInfo groupInfo() const;
    void setGroupInfo(const TGroupInfo &info);
public:
    TEditGroupReplyData &operator =(const TEditGroupReplyData &other);
    bool operator ==(const TEditGroupReplyData &other) const;
    bool operator !=(const TEditGroupReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditGroupReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditGroupReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditGroupReplyData &data);
};

Q_DECLARE_METATYPE(TEditGroupReplyData)

#endif // TEDITGROUPREPLYDATA_H
