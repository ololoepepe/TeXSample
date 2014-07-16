#ifndef TGETSAMPLESOURCEREPLYDATA_H
#define TGETSAMPLESOURCEREPLYDATA_H

class TGetSampleSourceReplyDataPrivate;

class TTexProject;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleSourceReplyData ===================
============================================================================*/

class T_CORE_EXPORT TGetSampleSourceReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleSourceReplyData)
public:
    explicit TGetSampleSourceReplyData();
    TGetSampleSourceReplyData(const TGetSampleSourceReplyData &other);
    ~TGetSampleSourceReplyData();
public:
    TTexProject &project();
    const TTexProject &project() const;
    void setProject(const TTexProject &project);
public:
    TGetSampleSourceReplyData &operator =(const TGetSampleSourceReplyData &other);
    bool operator ==(const TGetSampleSourceReplyData &other) const;
    bool operator !=(const TGetSampleSourceReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleSourceReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleSourceReplyData &data);
};

Q_DECLARE_METATYPE(TGetSampleSourceReplyData)

#endif // TGETSAMPLESOURCEREPLYDATA_H
