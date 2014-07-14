#ifndef TREQUESTRECOVERYCODEREPLYDATA_H
#define TREQUESTRECOVERYCODEREPLYDATA_H

class TRequestRecoveryCodeReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRequestRecoveryCodeReplyData ===============
============================================================================*/

class TRequestRecoveryCodeReplyData : public BBase
{
    B_DECLARE_PRIVATE(TRequestRecoveryCodeReplyData)
public:
    explicit TRequestRecoveryCodeReplyData();
    TRequestRecoveryCodeReplyData(const TRequestRecoveryCodeReplyData &other);
    ~TRequestRecoveryCodeReplyData();
public:
    TRequestRecoveryCodeReplyData &operator =(const TRequestRecoveryCodeReplyData &other);
    bool operator ==(const TRequestRecoveryCodeReplyData &other) const;
    bool operator !=(const TRequestRecoveryCodeReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeReplyData &data);
};

Q_DECLARE_METATYPE(TRequestRecoveryCodeReplyData)

#endif // TREQUESTRECOVERYCODEREPLYDATA_H
