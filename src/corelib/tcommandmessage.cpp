/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleCore module of the TeXSample library.
**
** TeXSample is free software: you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** TeXSample is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with TeXSample.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "tcommandmessage.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCommandMessagePrivate ======================
============================================================================*/

class TCommandMessagePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCommandMessage)
public:
    QString extraText;
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
================================ TCommandMessagePrivate ======================
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
================================ TCommandMessage =============================
============================================================================*/

/*============================== Public constructors =======================*/

TCommandMessage::TCommandMessage(int msg) :
    BBase(*new TCommandMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
}

TCommandMessage::TCommandMessage(int msg, const QString &extraText) :
    BBase(*new TCommandMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
    d_func()->extraText = extraText;
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

QString TCommandMessage::extraText() const
{
    return d_func()->extraText;
}

void TCommandMessage::setExtraText(const QString &extraText)
{
    d_func()->extraText = extraText;
}

QString TCommandMessage::text(const QStringList &args) const
{
    if (args.isEmpty())
        return tr(textNoTr().toUtf8().constData());
    QString s = tr(textNoTr().toUtf8().constData());
    foreach (const QString &a, args)
        s = s.arg(a);
    return s;
}

QString TCommandMessage::textNoTr() const
{
    switch (d_func()->message) {
    case FailedToStartServerMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Failed to start server");
    case InternalErrorMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Some internal error");
    case InvalidArgumentCountMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Invalid argument count");
    case InvalidArgumentsMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Invalid arguments");
    case NoSuchUserError:
        return QT_TRANSLATE_NOOP("TCommandMessage", "No such user");
    case OkMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "OK");
    case ServerAlreadyListeningMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "The server is already started");
    case ServerNotListeningMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "The server is not started");
    case UptimeMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Uptime: %1");
    case UserCountMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "User count: %1");
    case UserInfoListMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Users (%1):\n%2");
    case UserInfoMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "User info: %1\n%2");
    case UserKickedMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "User %1 was successfully kicked. Connections closed: %2");
    case UsersConnectedAtMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Users connected at (%1):\n%2");
    case UsersUptimeMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Users uptime (%1):\n%2");
    case UnknownErrorMessage:
        return QT_TRANSLATE_NOOP("TCommandMessage", "Some mysterious error");
    case NoMessage:
    default:
        return "";
    }
}

QString TCommandMessage::textNoTr(const QStringList &args) const
{
    QString s = textNoTr();
    foreach (const QString &a, args)
        s = s.arg(a);
    return s;
}

/*============================== Public operators ==========================*/

TCommandMessage &TCommandMessage::operator =(const TCommandMessage &other)
{
    d_func()->message = other.d_func()->message;
    d_func()->extraText = other.d_func()->extraText;
    return *this;
}

TCommandMessage &TCommandMessage::operator =(int msg)
{
    d_func()->message = enum_cast<Message>(msg, NoMessage, UnknownErrorMessage);
    return *this;
}

bool TCommandMessage::operator ==(const TCommandMessage &other) const
{
    return d_func()->message == other.d_func()->message && d_func()->extraText == other.d_func()->extraText;
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
    m.insert("extra_text", msg.d_func()->extraText);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCommandMessage &msg)
{
    QVariantMap m;
    stream >> m;
    msg.d_func()->message = enum_cast<TCommandMessage::Message>(m.value("message"), TCommandMessage::NoMessage,
                                                                TCommandMessage::UnknownErrorMessage);
    msg.d_func()->extraText = m.value("extra_text").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCommandMessage &msg)
{
    dbg.nospace() << "TCommandMessage(" << msg.textNoTr() << "," << msg.extraText() << ")";
    return dbg.space();
}
