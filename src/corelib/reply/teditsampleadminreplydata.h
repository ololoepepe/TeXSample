#ifndef TEDITSAMPLEADMINREPLYDATA_H
#define TEDITSAMPLEADMINREPLYDATA_H

class TEditSampleAdminReplyDataPrivate;

class TSampleInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSampleAdminReplyData ===================
============================================================================*/

class T_CORE_EXPORT TEditSampleAdminReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleAdminReplyData)
public:
    explicit TEditSampleAdminReplyData();
    TEditSampleAdminReplyData(const TEditSampleAdminReplyData &other);
    ~TEditSampleAdminReplyData();
public:
    TSampleInfo sampleInfo() const;
    void setSampleInfo(const TSampleInfo &info);
public:
    TEditSampleAdminReplyData &operator =(const TEditSampleAdminReplyData &other);
    bool operator ==(const TEditSampleAdminReplyData &other) const;
    bool operator !=(const TEditSampleAdminReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSampleAdminReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSampleAdminReplyData &data);
};

Q_DECLARE_METATYPE(TEditSampleAdminReplyData)

#endif // TEDITSAMPLEADMINREPLYDATA_H
