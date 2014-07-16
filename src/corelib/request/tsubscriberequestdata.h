#ifndef TSUBSCRIBEREQUESTDATA_H
#define TSUBSCRIBEREQUESTDATA_H

class TSubscribeRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TSubscribeRequestData =======================
============================================================================*/

class T_CORE_EXPORT TSubscribeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TSubscribeRequestData)
public:
    explicit TSubscribeRequestData();
    TSubscribeRequestData(const TSubscribeRequestData &other);
    ~TSubscribeRequestData();
public:
    void setSubscribedTLog(bool subscribed);
    bool subscribedToLog() const;
public:
    TSubscribeRequestData &operator =(const TSubscribeRequestData &other);
    bool operator ==(const TSubscribeRequestData &other) const;
    bool operator !=(const TSubscribeRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSubscribeRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TSubscribeRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TSubscribeRequestData &data);
};

Q_DECLARE_METATYPE(TSubscribeRequestData)

#endif // TSUBSCRIBEREQUESTDATA_H
