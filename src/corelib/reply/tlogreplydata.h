#ifndef TLOGREPLYDATA_H
#define TLOGREPLYDATA_H

class TLogReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TLogReplyData ===============================
============================================================================*/

class T_CORE_EXPORT TLogReplyData : public BBase
{
    B_DECLARE_PRIVATE(TLogReplyData)
public:
    explicit TLogReplyData();
    TLogReplyData(const TLogReplyData &other);
    ~TLogReplyData();
public:
    TLogReplyData &operator =(const TLogReplyData &other);
    bool operator ==(const TLogReplyData &other) const;
    bool operator !=(const TLogReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLogReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TLogReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TLogReplyData &data);
};

Q_DECLARE_METATYPE(TLogReplyData)

#endif // TLOGREPLYDATA_H
