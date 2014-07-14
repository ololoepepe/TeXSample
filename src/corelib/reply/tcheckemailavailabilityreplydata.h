#ifndef TCHECKEMAILAVAILABILITYREPLYDATA_H
#define TCHECKEMAILAVAILABILITYREPLYDATA_H

class TCheckEmailAvailabilityReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckEmailAvailabilityReplyData ============
============================================================================*/

class TCheckEmailAvailabilityReplyData : public BBase
{
    B_DECLARE_PRIVATE(TCheckEmailAvailabilityReplyData)
public:
    explicit TCheckEmailAvailabilityReplyData();
    TCheckEmailAvailabilityReplyData(const TCheckEmailAvailabilityReplyData &other);
    ~TCheckEmailAvailabilityReplyData();
public:
    void setAvailable(bool available);
    bool available() const;
public:
    TCheckEmailAvailabilityReplyData &operator =(const TCheckEmailAvailabilityReplyData &other);
    bool operator ==(const TCheckEmailAvailabilityReplyData &other) const;
    bool operator !=(const TCheckEmailAvailabilityReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCheckEmailAvailabilityReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCheckEmailAvailabilityReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TCheckEmailAvailabilityReplyData &data);
};

Q_DECLARE_METATYPE(TCheckEmailAvailabilityReplyData)

#endif // TCHECKEMAILAVAILABILITYREPLYDATA_H
