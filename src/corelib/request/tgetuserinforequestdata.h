#ifndef TGETUSERINFOREQUESTDATA_H
#define TGETUSERINFOREQUESTDATA_H

class TGetUserInfoRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoRequestData =====================
============================================================================*/

class T_CORE_EXPORT TGetUserInfoRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoRequestData)
public:
    explicit TGetUserInfoRequestData();
    TGetUserInfoRequestData(const TGetUserInfoRequestData &other);
    ~TGetUserInfoRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TGetUserInfoRequestData &operator =(const TGetUserInfoRequestData &other);
    bool operator ==(const TGetUserInfoRequestData &other) const;
    bool operator !=(const TGetUserInfoRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoRequestData)

#endif // TGETUSERINFOREQUESTDATA_H
