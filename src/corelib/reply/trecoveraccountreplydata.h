#ifndef TRECOVERACCOUNTREPLYDATA_H
#define TRECOVERACCOUNTREPLYDATA_H

class TRecoverAccountReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRecoverAccountReplyData ====================
============================================================================*/

class T_CORE_EXPORT TRecoverAccountReplyData : public BBase
{
    B_DECLARE_PRIVATE(TRecoverAccountReplyData)
public:
    explicit TRecoverAccountReplyData();
    TRecoverAccountReplyData(const TRecoverAccountReplyData &other);
    ~TRecoverAccountReplyData();
public:
    TRecoverAccountReplyData &operator =(const TRecoverAccountReplyData &other);
    bool operator ==(const TRecoverAccountReplyData &other) const;
    bool operator !=(const TRecoverAccountReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRecoverAccountReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRecoverAccountReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TRecoverAccountReplyData &data);
};

Q_DECLARE_METATYPE(TRecoverAccountReplyData)

#endif // TRECOVERACCOUNTREPLYDATA_H
