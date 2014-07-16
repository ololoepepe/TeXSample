#ifndef TGETSAMPLEINFOLISTREQUESTDATA_H
#define TGETSAMPLEINFOLISTREQUESTDATA_H

class TGetSampleInfoListRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleInfoListRequestData ===============
============================================================================*/

class T_CORE_EXPORT TGetSampleInfoListRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleInfoListRequestData)
public:
    explicit TGetSampleInfoListRequestData();
    TGetSampleInfoListRequestData(const TGetSampleInfoListRequestData &other);
    ~TGetSampleInfoListRequestData();
public:
    TGetSampleInfoListRequestData &operator =(const TGetSampleInfoListRequestData &other);
    bool operator ==(const TGetSampleInfoListRequestData &other) const;
    bool operator !=(const TGetSampleInfoListRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleInfoListRequestData &data);
};

Q_DECLARE_METATYPE(TGetSampleInfoListRequestData)

#endif // TGETSAMPLEINFOLISTREQUESTDATA_H
