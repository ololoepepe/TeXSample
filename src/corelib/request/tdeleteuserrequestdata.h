#ifndef TDELETEUSERREQUESTDATA_H
#define TDELETEUSERREQUESTDATA_H

class TDeleteUserRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteUserRequestData ======================
============================================================================*/

class T_CORE_EXPORT TDeleteUserRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteUserRequestData)
public:
    explicit TDeleteUserRequestData();
    TDeleteUserRequestData(const TDeleteUserRequestData &other);
    ~TDeleteUserRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TDeleteUserRequestData &operator =(const TDeleteUserRequestData &other);
    bool operator ==(const TDeleteUserRequestData &other) const;
    bool operator !=(const TDeleteUserRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteUserRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteUserRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteUserRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteUserRequestData)

#endif // TDELETEUSERREQUESTDATA_H
