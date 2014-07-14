#ifndef TCHECKLOGINAVAILABILITYREPLYDATA_H
#define TCHECKLOGINAVAILABILITYREPLYDATA_H

class TCheckLoginAvailabilityReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckLoginAvailabilityReplyData ============
============================================================================*/

class TCheckLoginAvailabilityReplyData : public BBase
{
    B_DECLARE_PRIVATE(TCheckLoginAvailabilityReplyData)
public:
    explicit TCheckLoginAvailabilityReplyData();
    TCheckLoginAvailabilityReplyData(const TCheckLoginAvailabilityReplyData &other);
    ~TCheckLoginAvailabilityReplyData();
public:
    void setAvailable(bool available);
    bool available() const;
public:
    TCheckLoginAvailabilityReplyData &operator =(const TCheckLoginAvailabilityReplyData &other);
    bool operator ==(const TCheckLoginAvailabilityReplyData &other) const;
    bool operator !=(const TCheckLoginAvailabilityReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityReplyData &data);
};

Q_DECLARE_METATYPE(TCheckLoginAvailabilityReplyData)

#endif // TCHECKLOGINAVAILABILITYREPLYDATA_H
