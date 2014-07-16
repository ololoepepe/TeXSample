#ifndef TADDLABREPLYDATA_H
#define TADDLABREPLYDATA_H

class TAddLabReplyDataPrivate;

class TLabInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddLabReplyData ============================
============================================================================*/

class T_CORE_EXPORT TAddLabReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddLabReplyData)
public:
    explicit TAddLabReplyData();
    TAddLabReplyData(const TAddLabReplyData &other);
    ~TAddLabReplyData();
public:
    TLabInfo labInfo() const;
    void setLabInfo(const TLabInfo &info);
public:
    TAddLabReplyData &operator =(const TAddLabReplyData &other);
    bool operator ==(const TAddLabReplyData &other) const;
    bool operator !=(const TAddLabReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddLabReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddLabReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAddLabReplyData &data);
};

Q_DECLARE_METATYPE(TAddLabReplyData)

#endif // TADDLABREPLYDATA_H
