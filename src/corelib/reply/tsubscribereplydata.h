#ifndef TSUBSCRIBEREPLYDATA_H
#define TSUBSCRIBEREPLYDATA_H

class TSubscribeReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TSubscribeReplyData =========================
============================================================================*/

class T_CORE_EXPORT TSubscribeReplyData : public BBase
{
    B_DECLARE_PRIVATE(TSubscribeReplyData)
public:
    explicit TSubscribeReplyData();
    TSubscribeReplyData(const TSubscribeReplyData &other);
    ~TSubscribeReplyData();
public:
    TSubscribeReplyData &operator =(const TSubscribeReplyData &other);
    bool operator ==(const TSubscribeReplyData &other) const;
    bool operator !=(const TSubscribeReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSubscribeReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TSubscribeReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TSubscribeReplyData &data);
};

Q_DECLARE_METATYPE(TSubscribeReplyData)

#endif // TSUBSCRIBEREPLYDATA_H
