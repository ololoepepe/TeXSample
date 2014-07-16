#ifndef TDELETESAMPLEREPLYDATA_H
#define TDELETESAMPLEREPLYDATA_H

class TDeleteSampleReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteSampleReplyData ======================
============================================================================*/

class T_CORE_EXPORT TDeleteSampleReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteSampleReplyData)
public:
    explicit TDeleteSampleReplyData();
    TDeleteSampleReplyData(const TDeleteSampleReplyData &other);
    ~TDeleteSampleReplyData();
public:
    TDeleteSampleReplyData &operator =(const TDeleteSampleReplyData &other);
    bool operator ==(const TDeleteSampleReplyData &other) const;
    bool operator !=(const TDeleteSampleReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteSampleReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteSampleReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteSampleReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteSampleReplyData)

#endif // TDELETESAMPLEREPLYDATA_H
