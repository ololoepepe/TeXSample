#ifndef TGETSAMPLISOURCEREQUESTDATA_H
#define TGETSAMPLISOURCEREQUESTDATA_H

class TGetSampleSourceRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleSourceRequestData =================
============================================================================*/

class T_CORE_EXPORT TGetSampleSourceRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleSourceRequestData)
public:
    explicit TGetSampleSourceRequestData();
    TGetSampleSourceRequestData(const TGetSampleSourceRequestData &other);
    ~TGetSampleSourceRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TGetSampleSourceRequestData &operator =(const TGetSampleSourceRequestData &other);
    bool operator ==(const TGetSampleSourceRequestData &other) const;
    bool operator !=(const TGetSampleSourceRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleSourceRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleSourceRequestData &data);
};

Q_DECLARE_METATYPE(TGetSampleSourceRequestData)

#endif // TGETSAMPLISOURCEREQUESTDATA_H
