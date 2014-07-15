#ifndef TCHANGEPASSWORDREPLYDATA_H
#define TCHANGEPASSWORDREPLYDATA_H

class TChangePasswordReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TChangePasswordReplyData ====================
============================================================================*/

class T_CORE_EXPORT TChangePasswordReplyData : public BBase
{
    B_DECLARE_PRIVATE(TChangePasswordReplyData)
public:
    explicit TChangePasswordReplyData();
    TChangePasswordReplyData(const TChangePasswordReplyData &other);
    ~TChangePasswordReplyData();
public:
    TChangePasswordReplyData &operator =(const TChangePasswordReplyData &other);
    bool operator ==(const TChangePasswordReplyData &other) const;
    bool operator !=(const TChangePasswordReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TChangePasswordReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TChangePasswordReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TChangePasswordReplyData &data);
};

Q_DECLARE_METATYPE(TChangePasswordReplyData)

#endif // TCHANGEPASSWORDREPLYDATA_H
