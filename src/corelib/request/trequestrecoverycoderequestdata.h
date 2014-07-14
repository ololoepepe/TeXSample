#ifndef TREQUESTRECOVERYCODEREQUESTDATA_H
#define TREQUESTRECOVERYCODEREQUESTDATA_H

class TRequestRecoveryCodeRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRequestRecoveryCodeRequestData =============
============================================================================*/

class T_CORE_EXPORT TRequestRecoveryCodeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TRequestRecoveryCodeRequestData)
public:
    explicit TRequestRecoveryCodeRequestData();
    TRequestRecoveryCodeRequestData(const TRequestRecoveryCodeRequestData &other);
    ~TRequestRecoveryCodeRequestData();
public:
    void clear();
    QString email() const;
    bool isValid() const;
    void setEmail(const QString &email);
public:
    TRequestRecoveryCodeRequestData &operator =(const TRequestRecoveryCodeRequestData &other);
    bool operator ==(const TRequestRecoveryCodeRequestData &other) const;
    bool operator !=(const TRequestRecoveryCodeRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeRequestData &data);
};

Q_DECLARE_METATYPE(TRequestRecoveryCodeRequestData)

#endif // TREQUESTRECOVERYCODEREQUESTDATA_H
