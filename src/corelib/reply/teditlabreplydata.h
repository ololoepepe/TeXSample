#ifndef TEDITLABREPLYDATA_H
#define TEDITLABREPLYDATA_H

class TEditLabReplyDataPrivate;

class TLabInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditLabReplyData ===========================
============================================================================*/

class T_CORE_EXPORT TEditLabReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditLabReplyData)
public:
    explicit TEditLabReplyData();
    TEditLabReplyData(const TEditLabReplyData &other);
    ~TEditLabReplyData();
public:
    TLabInfo labInfo() const;
    void setLabInfo(const TLabInfo &info);
public:
    TEditLabReplyData &operator =(const TEditLabReplyData &other);
    bool operator ==(const TEditLabReplyData &other) const;
    bool operator !=(const TEditLabReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditLabReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditLabReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditLabReplyData &data);
};

Q_DECLARE_METATYPE(TEditLabReplyData)

#endif // TEDITLABREPLYDATA_H
