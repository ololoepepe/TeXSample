#ifndef TGETGROUPINFOLISTREPLYDATA_H
#define TGETGROUPINFOLISTREPLYDATA_H

class TGetGroupInfoListReplyDataPrivate;

class TGroupInfoList;
class TIdList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetGroupInfoListReplyData ==================
============================================================================*/

class T_CORE_EXPORT TGetGroupInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetGroupInfoListReplyData)
public:
    explicit TGetGroupInfoListReplyData();
    TGetGroupInfoListReplyData(const TGetGroupInfoListReplyData &other);
    ~TGetGroupInfoListReplyData();
public:
    TIdList deletedGroups() const;
    TGroupInfoList newGroups() const;
    void setDeletedGroups(const TIdList &deletedGroups);
    void setNewGroups(const TGroupInfoList &newGroups);
public:
    TGetGroupInfoListReplyData &operator =(const TGetGroupInfoListReplyData &other);
    bool operator ==(const TGetGroupInfoListReplyData &other) const;
    bool operator !=(const TGetGroupInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetGroupInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetGroupInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetGroupInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetGroupInfoListReplyData)

#endif // TGETGROUPINFOLISTREPLYDATA_H
