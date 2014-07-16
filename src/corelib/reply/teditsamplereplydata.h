#ifndef TEDITSAMPLEREPLYDATA_H
#define TEDITSAMPLEREPLYDATA_H

class TEditSampleReplyDataPrivate;

class TSampleInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSampleReplyData ========================
============================================================================*/

class T_CORE_EXPORT TEditSampleReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleReplyData)
public:
    explicit TEditSampleReplyData();
    TEditSampleReplyData(const TEditSampleReplyData &other);
    ~TEditSampleReplyData();
public:
    TSampleInfo sampleInfo() const;
    void setSampleInfo(const TSampleInfo &info);
public:
    TEditSampleReplyData &operator =(const TEditSampleReplyData &other);
    bool operator ==(const TEditSampleReplyData &other) const;
    bool operator !=(const TEditSampleReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSampleReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSampleReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSampleReplyData &data);
};

Q_DECLARE_METATYPE(TEditSampleReplyData)

#endif // TEDITSAMPLEREPLYDATA_H
