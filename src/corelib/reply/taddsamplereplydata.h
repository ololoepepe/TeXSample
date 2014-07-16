#ifndef TADDSAMPLEREPLYDATA_H
#define TADDSAMPLEREPLYDATA_H

class TAddSampleReplyDataPrivate;

class TSampleInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddSampleReplyData =========================
============================================================================*/

class T_CORE_EXPORT TAddSampleReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddSampleReplyData)
public:
    explicit TAddSampleReplyData();
    TAddSampleReplyData(const TAddSampleReplyData &other);
    ~TAddSampleReplyData();
public:
    TSampleInfo sampleInfo() const;
    void setSampleInfo(const TSampleInfo &info);
public:
    TAddSampleReplyData &operator =(const TAddSampleReplyData &other);
    bool operator ==(const TAddSampleReplyData &other) const;
    bool operator !=(const TAddSampleReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddSampleReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddSampleReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAddSampleReplyData &data);
};

Q_DECLARE_METATYPE(TAddSampleReplyData)

#endif // TADDSAMPLEREPLYDATA_H
