#ifndef TCHECKEMAILAVAILABILITYREQUESTDATA_H
#define TCHECKEMAILAVAILABILITYREQUESTDATA_H

class TCheckEmailAvailabilityRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckEmailAvailabilityRequestData ==========
============================================================================*/

class T_CORE_EXPORT TCheckEmailAvailabilityRequestData : public BBase
{
    B_DECLARE_PRIVATE(TCheckEmailAvailabilityRequestData)
public:
    explicit TCheckEmailAvailabilityRequestData();
    TCheckEmailAvailabilityRequestData(const TCheckEmailAvailabilityRequestData &other);
    ~TCheckEmailAvailabilityRequestData();
public:
    void clear();
    QString email() const;
    bool isValid() const;
    void setEmail(const QString &email);
public:
    TCheckEmailAvailabilityRequestData &operator =(const TCheckEmailAvailabilityRequestData &other);
    bool operator ==(const TCheckEmailAvailabilityRequestData &other) const;
    bool operator !=(const TCheckEmailAvailabilityRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCheckEmailAvailabilityRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCheckEmailAvailabilityRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TCheckEmailAvailabilityRequestData &data);
};

Q_DECLARE_METATYPE(TCheckEmailAvailabilityRequestData)

#endif // TCHECKEMAILAVAILABILITYREQUESTDATA_H
