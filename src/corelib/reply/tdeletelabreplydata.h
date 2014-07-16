#ifndef TDELETELABREPLYDATA_H
#define TDELETELABREPLYDATA_H

class TDeleteLabReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteLabReplyData =========================
============================================================================*/

class T_CORE_EXPORT TDeleteLabReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteLabReplyData)
public:
    explicit TDeleteLabReplyData();
    TDeleteLabReplyData(const TDeleteLabReplyData &other);
    ~TDeleteLabReplyData();
public:
    TDeleteLabReplyData &operator =(const TDeleteLabReplyData &other);
    bool operator ==(const TDeleteLabReplyData &other) const;
    bool operator !=(const TDeleteLabReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteLabReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteLabReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteLabReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteLabReplyData)

#endif // TDELETELABREPLYDATA_H
