#ifndef TDELETESAMPLEREQUESTDATA_H
#define TDELETESAMPLEREQUESTDATA_H

class TDeleteSampleRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteSampleRequestData ====================
============================================================================*/

class T_CORE_EXPORT TDeleteSampleRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteSampleRequestData)
public:
    explicit TDeleteSampleRequestData();
    TDeleteSampleRequestData(const TDeleteSampleRequestData &other);
    ~TDeleteSampleRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TDeleteSampleRequestData &operator =(const TDeleteSampleRequestData &other);
    bool operator ==(const TDeleteSampleRequestData &other) const;
    bool operator !=(const TDeleteSampleRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteSampleRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteSampleRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteSampleRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteSampleRequestData)

#endif // TDELETESAMPLEREQUESTDATA_H
