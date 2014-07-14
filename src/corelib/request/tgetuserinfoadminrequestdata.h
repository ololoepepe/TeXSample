#ifndef TGETUSERINFOADMINREQUESTDATA_H
#define TGETUSERINFOADMINREQUESTDATA_H

class TGetUserInfoAdminRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoAdminRequestData ================
============================================================================*/

class T_CORE_EXPORT TGetUserInfoAdminRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoAdminRequestData)
public:
    explicit TGetUserInfoAdminRequestData();
    TGetUserInfoAdminRequestData(const TGetUserInfoAdminRequestData &other);
    ~TGetUserInfoAdminRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TGetUserInfoAdminRequestData &operator =(const TGetUserInfoAdminRequestData &other);
    bool operator ==(const TGetUserInfoAdminRequestData &other) const;
    bool operator !=(const TGetUserInfoAdminRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoAdminRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoAdminRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoAdminRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoAdminRequestData)

#endif // TGETUSERINFOADMINREQUESTDATA_H
