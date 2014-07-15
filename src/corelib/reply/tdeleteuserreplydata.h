#ifndef TDELETEUSERREPLYDATA_H
#define TDELETEUSERREPLYDATA_H

class TDeleteUserReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteUserReplyData ========================
============================================================================*/

class T_CORE_EXPORT TDeleteUserReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteUserReplyData)
public:
    explicit TDeleteUserReplyData();
    TDeleteUserReplyData(const TDeleteUserReplyData &other);
    ~TDeleteUserReplyData();
public:
    TDeleteUserReplyData &operator =(const TDeleteUserReplyData &other);
    bool operator ==(const TDeleteUserReplyData &other) const;
    bool operator !=(const TDeleteUserReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteUserReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteUserReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteUserReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteUserReplyData)

#endif // TDELETEUSERREPLYDATA_H
