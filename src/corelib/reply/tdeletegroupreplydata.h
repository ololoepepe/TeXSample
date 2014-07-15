#ifndef TDELETEGROUPREPLYDATA_H
#define TDELETEGROUPREPLYDATA_H

class TDeleteGroupReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteGroupReplyData =======================
============================================================================*/

class T_CORE_EXPORT TDeleteGroupReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteGroupReplyData)
public:
    explicit TDeleteGroupReplyData();
    TDeleteGroupReplyData(const TDeleteGroupReplyData &other);
    ~TDeleteGroupReplyData();
public:
    TDeleteGroupReplyData &operator =(const TDeleteGroupReplyData &other);
    bool operator ==(const TDeleteGroupReplyData &other) const;
    bool operator !=(const TDeleteGroupReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteGroupReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteGroupReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteGroupReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteGroupReplyData)

#endif // TDELETEGROUPREPLYDATA_H
