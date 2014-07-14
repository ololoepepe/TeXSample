#ifndef TGETGROUPINFOLISTREQUESTDATA_H
#define TGETGROUPINFOLISTREQUESTDATA_H

class TGetGroupInfoListRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetGroupInfoListRequestData ================
============================================================================*/

class T_CORE_EXPORT TGetGroupInfoListRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetGroupInfoListRequestData)
public:
    explicit TGetGroupInfoListRequestData();
    TGetGroupInfoListRequestData(const TGetGroupInfoListRequestData &other);
    ~TGetGroupInfoListRequestData();
public:
    TGetGroupInfoListRequestData &operator =(const TGetGroupInfoListRequestData &other);
    bool operator ==(const TGetGroupInfoListRequestData &other) const;
    bool operator !=(const TGetGroupInfoListRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetGroupInfoListRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetGroupInfoListRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetGroupInfoListRequestData &data);
};

Q_DECLARE_METATYPE(TGetGroupInfoListRequestData)

#endif // TGETGROUPINFOLISTREQUESTDATA_H
