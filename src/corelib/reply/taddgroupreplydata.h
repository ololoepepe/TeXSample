#ifndef TADDGROUPREPLYDATA_H
#define TADDGROUPREPLYDATA_H

class TAddGroupReplyDataPrivate;

class TGroupInfo;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddGroupReplyData ==========================
============================================================================*/

class TAddGroupReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddGroupReplyData)
public:
    explicit TAddGroupReplyData();
    TAddGroupReplyData(const TAddGroupReplyData &other);
    ~TAddGroupReplyData();
public:
    TGroupInfo groupInfo() const;
    void setGroupInfo(const TGroupInfo &info);
public:
    TAddGroupReplyData &operator =(const TAddGroupReplyData &other);
    bool operator ==(const TAddGroupReplyData &other) const;
    bool operator !=(const TAddGroupReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddGroupReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddGroupReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAddGroupReplyData &data);
};

Q_DECLARE_METATYPE(TAddGroupReplyData)

#endif // TADDGROUPREPLYDATA_H
