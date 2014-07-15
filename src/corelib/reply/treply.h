#ifndef TREPLY_H
#define TREPLY_H

class TReplyPrivate;

class TMessage;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TReply ======================================
============================================================================*/

class T_CORE_EXPORT TReply : public BBase
{
    B_DECLARE_PRIVATE(TReply)
public:
    explicit TReply();
    TReply(const TReply &other);
    ~TReply();
public:
    bool cacheUpToDate() const;
    void clear();
    QVariant data() const;
    TMessage message() const;
    QString messageText() const;
    QString messageTextNoTr() const;
    QDateTime requestDateTime() const;
    void setCacheUpToDate(bool upToDate);
    void setData(const QVariant &data);
    void setMessage(const TMessage &message);
    void setRequestDateTime(const QDateTime &dt);
    void setSuccess(bool success);
    bool success() const;
public:
    TReply &operator =(const TReply &other);
    bool operator ==(const TReply &other) const;
    bool operator !=(const TReply &other) const;
    operator QVariant() const;
    operator bool() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TReply &data);
    friend QDataStream &operator >>(QDataStream &stream, TReply &data);
    friend QDebug operator <<(QDebug dbg, const TReply &data);
};

Q_DECLARE_METATYPE(TReply)

#endif // TREPLY_H
