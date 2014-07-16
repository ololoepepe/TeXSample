#ifndef TGETLABINFOLISTREPLYDATA_H
#define TGETLABINFOLISTREPLYDATA_H

class TGetLabInfoListReplyDataPrivate;

class TIdList;
class TLabInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabInfoListReplyData ====================
============================================================================*/

class T_CORE_EXPORT TGetLabInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabInfoListReplyData)
public:
    explicit TGetLabInfoListReplyData();
    TGetLabInfoListReplyData(const TGetLabInfoListReplyData &other);
    ~TGetLabInfoListReplyData();
public:
    TIdList deletedLabs() const;
    TLabInfoList newLabs() const;
    void setDeletedLabs(const TIdList &deletedLabs);
    void setNewLabs(const TLabInfoList &newLabs);
public:
    TGetLabInfoListReplyData &operator =(const TGetLabInfoListReplyData &other);
    bool operator ==(const TGetLabInfoListReplyData &other) const;
    bool operator !=(const TGetLabInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetLabInfoListReplyData)

#endif // TGETLABINFOLISTREPLYDATA_H
