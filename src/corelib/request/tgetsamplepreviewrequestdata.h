#ifndef TGETSAMPLIPREVIEWREQUESTDATA_H
#define TGETSAMPLIPREVIEWREQUESTDATA_H

class TGetSamplePreviewRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSamplePreviewRequestData ================
============================================================================*/

class T_CORE_EXPORT TGetSamplePreviewRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSamplePreviewRequestData)
public:
    explicit TGetSamplePreviewRequestData();
    TGetSamplePreviewRequestData(const TGetSamplePreviewRequestData &other);
    ~TGetSamplePreviewRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TGetSamplePreviewRequestData &operator =(const TGetSamplePreviewRequestData &other);
    bool operator ==(const TGetSamplePreviewRequestData &other) const;
    bool operator !=(const TGetSamplePreviewRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSamplePreviewRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSamplePreviewRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSamplePreviewRequestData &data);
};

Q_DECLARE_METATYPE(TGetSamplePreviewRequestData)

#endif // TGETSAMPLIPREVIEWREQUESTDATA_H
