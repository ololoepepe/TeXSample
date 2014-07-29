#ifndef TEXECUTECOMMANDREPLYDATA_H
#define TEXECUTECOMMANDREPLYDATA_H

class TExecuteCommandReplyDataPrivate;

class TCommandMessage;

class QDataStream;
class QDebug;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TExecuteCommandReplyData ====================
============================================================================*/

class T_CORE_EXPORT TExecuteCommandReplyData : public BBase
{
    B_DECLARE_PRIVATE(TExecuteCommandReplyData)
public:
    explicit TExecuteCommandReplyData();
    TExecuteCommandReplyData(const TExecuteCommandReplyData &other);
    ~TExecuteCommandReplyData();
public:
    QStringList arguments() const;
    TCommandMessage message() const;
    void setArguments(const QStringList &arguments);
    void setMessage(const TCommandMessage &message);
public:
    TExecuteCommandReplyData &operator =(const TExecuteCommandReplyData &other);
    bool operator ==(const TExecuteCommandReplyData &other) const;
    bool operator !=(const TExecuteCommandReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TExecuteCommandReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TExecuteCommandReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TExecuteCommandReplyData &data);
};

Q_DECLARE_METATYPE(TExecuteCommandReplyData)

#endif // TEXECUTECOMMANDREPLYDATA_H
