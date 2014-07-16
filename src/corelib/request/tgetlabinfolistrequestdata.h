#ifndef TGETLABINFOLISTREQUESTDATA_H
#define TGETLABINFOLISTREQUESTDATA_H

class TGetLabInfoListRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabInfoListRequestData ==================
============================================================================*/

class T_CORE_EXPORT TGetLabInfoListRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabInfoListRequestData)
public:
    explicit TGetLabInfoListRequestData();
    TGetLabInfoListRequestData(const TGetLabInfoListRequestData &other);
    ~TGetLabInfoListRequestData();
public:
    TGetLabInfoListRequestData &operator =(const TGetLabInfoListRequestData &other);
    bool operator ==(const TGetLabInfoListRequestData &other) const;
    bool operator !=(const TGetLabInfoListRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabInfoListRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabInfoListRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabInfoListRequestData &data);
};

Q_DECLARE_METATYPE(TGetLabInfoListRequestData)

#endif // TGETLABINFOLISTREQUESTDATA_H
