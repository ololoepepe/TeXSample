#ifndef TGETSAMPLEINFOLISTREPLYDATA_H
#define TGETSAMPLEINFOLISTREPLYDATA_H

class TGetSampleInfoListReplyDataPrivate;

class TIdList;
class TSampleInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleInfoListReplyData =================
============================================================================*/

class T_CORE_EXPORT TGetSampleInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleInfoListReplyData)
public:
    explicit TGetSampleInfoListReplyData();
    TGetSampleInfoListReplyData(const TGetSampleInfoListReplyData &other);
    ~TGetSampleInfoListReplyData();
public:
    TIdList deletedSamples() const;
    TSampleInfoList newSamples() const;
    void setDeletedSamples(const TIdList &deletedSamples);
    void setNewSamples(const TSampleInfoList &newSamples);
public:
    TGetSampleInfoListReplyData &operator =(const TGetSampleInfoListReplyData &other);
    bool operator ==(const TGetSampleInfoListReplyData &other) const;
    bool operator !=(const TGetSampleInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetSampleInfoListReplyData)

#endif // TGETSAMPLEINFOLISTREPLYDATA_H
