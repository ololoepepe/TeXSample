#ifndef TGETUSERINFOLISTADMINREQUESTDATA_H
#define TGETUSERINFOLISTADMINREQUESTDATA_H

class TGetUserInfoListAdminRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoListAdminRequestData ============
============================================================================*/

class T_CORE_EXPORT TGetUserInfoListAdminRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoListAdminRequestData)
public:
    explicit TGetUserInfoListAdminRequestData();
    TGetUserInfoListAdminRequestData(const TGetUserInfoListAdminRequestData &other);
    ~TGetUserInfoListAdminRequestData();
public:
    TGetUserInfoListAdminRequestData &operator =(const TGetUserInfoListAdminRequestData &other);
    bool operator ==(const TGetUserInfoListAdminRequestData &other) const;
    bool operator !=(const TGetUserInfoListAdminRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoListAdminRequestData)

#endif // TGetUserInfoListAdminRequestData_H
