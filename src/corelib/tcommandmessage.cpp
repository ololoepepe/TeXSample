#include "tcommandmessage.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCommandMessagePrivate ======================
============================================================================*/

class TCommandMessagePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCommandMessage)
public:
    TCommandMessage::Message message;
public:
   explicit TCommandMessagePrivate(TCommandMessage *q);
    ~TCommandMessagePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCommandMessagePrivate)
};

/*============================================================================
================================ TCommandMessagePrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TCommandMessagePrivate::TCommandMessagePrivate(TCommandMessage *q) :
    BBasePrivate(q)
{
    //
}

TCommandMessagePrivate::~TCommandMessagePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCommandMessagePrivate::init()
{
    message = TCommandMessage::NoMessage;
}

/*============================================================================
================================ TCommandMessage ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TCommandMessage::TCommandMessage(int msg) :
    BBase(*new TCommandMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
}

TCommandMessage::TCommandMessage(const TCommandMessage &other) :
    BBase(*new TCommandMessagePrivate(this))
{
    d_func()->init();
    *this = other;
}

TCommandMessage::~TCommandMessage()
{
    //
}

/*============================== Protected constructors ====================*/


TCommandMessage::TCommandMessage(TCommandMessagePrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

QString TCommandMessage::text() const
{
    return tr(textNoTr().toUtf8().constData());
}

QString TCommandMessage::textNoTr() const
{
    switch (d_func()->message)
    {
    case NoMessage:
    default:
        return "";
    }
}

/*============================== Public operators ==========================*/

TCommandMessage &TCommandMessage::operator =(const TCommandMessage &other)
{
    d_func()->message = other.d_func()->message;
    return *this;
}

TCommandMessage &TCommandMessage::operator =(int msg)
{
    d_func()->message = enum_cast<Message>(msg, NoMessage, NoMessage); //TODO
    return *this;
}

bool TCommandMessage::operator ==(const TCommandMessage &other) const
{
    return d_func()->message == other.d_func()->message;
}

bool TCommandMessage::operator !=(const TCommandMessage &other) const
{
    return !(*this == other);
}

TCommandMessage::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TCommandMessage::operator QString() const
{
    return text();
}

TCommandMessage::operator int() const
{
    return d_func()->message;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCommandMessage &msg)
{
    QVariantMap m;
    m.insert("message", (int) msg.d_func()->message);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCommandMessage &msg)
{
    QVariantMap m;
    stream >> m;
    msg.d_func()->message = enum_cast<TCommandMessage::Message>(m.value("message"), TCommandMessage::NoMessage,
                                                                TCommandMessage::NoMessage); //TODO
    return stream;
}

QDebug operator <<(QDebug dbg, const TCommandMessage &msg)
{
    dbg.nospace() << "TCommandMessage(" << msg.textNoTr() << ")";
    return dbg.space();
}
