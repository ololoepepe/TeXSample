#ifndef TGETUSERAVATARREQUESTDATA_H
#define TGETUSERAVATARREQUESTDATA_H

class TGetUserAvatarRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserAvatarRequestData ===================
============================================================================*/

class T_CORE_EXPORT TGetUserAvatarRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserAvatarRequestData)
public:
    explicit TGetUserAvatarRequestData();
    TGetUserAvatarRequestData(const TGetUserAvatarRequestData &other);
    ~TGetUserAvatarRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TGetUserAvatarRequestData &operator =(const TGetUserAvatarRequestData &other);
    bool operator ==(const TGetUserAvatarRequestData &other) const;
    bool operator !=(const TGetUserAvatarRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserAvatarRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserAvatarRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserAvatarRequestData)

#endif // TGETUSERAVATARREQUESTDATA_H
