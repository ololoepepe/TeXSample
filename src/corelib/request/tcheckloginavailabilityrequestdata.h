#ifndef TCHECKLOGINAVAILABILITYREQUESTDATA_H
#define TCHECKLOGINAVAILABILITYREQUESTDATA_H

class TCheckLoginAvailabilityRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckLoginAvailabilityRequestData ==========
============================================================================*/

class T_CORE_EXPORT TCheckLoginAvailabilityRequestData : public BBase
{
    B_DECLARE_PRIVATE(TCheckLoginAvailabilityRequestData)
public:
    explicit TCheckLoginAvailabilityRequestData();
    TCheckLoginAvailabilityRequestData(const TCheckLoginAvailabilityRequestData &other);
    ~TCheckLoginAvailabilityRequestData();
public:
    void clear();
    bool isValid() const;
    QString login() const;
    void setLogin(const QString &login);
public:
    TCheckLoginAvailabilityRequestData &operator =(const TCheckLoginAvailabilityRequestData &other);
    bool operator ==(const TCheckLoginAvailabilityRequestData &other) const;
    bool operator !=(const TCheckLoginAvailabilityRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityRequestData &data);
};

Q_DECLARE_METATYPE(TCheckLoginAvailabilityRequestData)

#endif // TCHECKLOGINAVAILABILITYREQUESTDATA_H
