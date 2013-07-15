#include "tmessage.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QVariantMap>

/*============================================================================
================================ TMessagePrivate =============================
============================================================================*/

class TSMP_EXPORT TMessagePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TMessage)
public:
   explicit TMessagePrivate(TMessage *q);
    ~TMessagePrivate();
public:
    void init();
public:
    TMessage::Message message;
private:
    Q_DISABLE_COPY(TMessagePrivate)
};

/*============================================================================
================================ TMessagePrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TMessagePrivate::TMessagePrivate(TMessage *q) :
    BBasePrivate(q)
{
    //
}

TMessagePrivate::~TMessagePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TMessagePrivate::init()
{
    message = TMessage::NoMessage;
}

/*============================================================================
================================ TMessage ====================================
============================================================================*/

/*============================== Static public methods =====================*/

TMessage::Message TMessage::messageFromInt(int msg)
{
    static const QList<int> messages = bRangeD(NoMessage, NoMessage);
    return messages.contains(msg) ? static_cast<Message>(msg) : NoMessage;
}

QString TMessage::messageToString(int msg)
{
    switch (msg)
    {
    case NoMessage:
    default:
        return "";
    }
}

QString TMessage::messageToStringNoTr(int msg)
{
    switch (msg)
    {
    case NoMessage:
    default:
        return "";
    }
}

/*============================== Public constructors =======================*/

TMessage::TMessage(int msg) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    setMessage(msg);
}

TMessage::TMessage(const TMessage &other) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    *this = other;
}

TMessage::~TMessage()
{
    //
}

/*============================== Protected constructors ====================*/


TMessage::TMessage(TMessagePrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

void TMessage::setMessage(int msg)
{
    d_func()->message = messageFromInt(msg);
}

TMessage::Message TMessage::message() const
{
    return d_func()->message;
}

QString TMessage::messageString() const
{
    return messageToString(d_func()->message);
}

QString TMessage::messageStringNoTr() const
{
    return messageToStringNoTr(d_func()->message);
}

/*============================== Public operators ==========================*/

TMessage &TMessage::operator =(const TMessage &other)
{
    B_D(TMessage);
    const TMessagePrivate *dd = other.d_func();
    d->message = dd->message;
    return *this;
}

bool TMessage::operator ==(const TMessage &other) const
{
    const B_D(TMessage);
    const TMessagePrivate *dd = other.d_func();
    return d->message == dd->message;
}

TMessage::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TMessage &msg)
{
    QVariantMap m;
    m.insert("message", (int) msg.d_func()->message);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TMessage &msg)
{
    QVariantMap m;
    stream >> m;
    msg.d_func()->message = TMessage::messageFromInt(m.value("message").toInt());
    return stream;
}

QDebug operator <<(QDebug dbg, const TMessage &msg)
{
    dbg.nospace() << "TMessage(" << msg.messageStringNoTr() << ")";
    return dbg.space();
}
