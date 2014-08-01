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

#include "tmessage.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TMessagePrivate =============================
============================================================================*/

class TMessagePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TMessage)
public:
    QString extraText;
    TMessage::Message message;
public:
   explicit TMessagePrivate(TMessage *q);
    ~TMessagePrivate();
public:
    void init();
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

/*============================== Public constructors =======================*/

TMessage::TMessage(int msg) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
}

TMessage::TMessage(int msg, const QString &extraText) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
    d_func()->extraText = extraText;
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

QString TMessage::extraText() const
{
    return d_func()->extraText;
}

void TMessage::setExtraText(const QString &extraText)
{
    d_func()->extraText = extraText;
}

QString TMessage::text() const
{
    return tr(textNoTr().toUtf8().constData());
}

QString TMessage::textNoTr() const
{
    switch (d_func()->message) {
    case AlreadyAuthorizedMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Already authorized");
    case AlreadyDeletedMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The resource is already deleted");
    case AlreadyExistsMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The resource already exists");
    case ConnectionTimeoutMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The connection timed out");
    case InternalErrorMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Some internal error");
    case InvalidCommandMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The command is invalid");
    case InvalidDataMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The data is invalid");
    case InvalidIdentifierMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The identifier is invalid");
    case InvalidUsernameOrPasswordMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Either the username or the password is invalid");
    case NoAccessToServiceMessage:
        return QT_TRANSLATE_NOOP("TMessage", "No access to this service");
    case NotAuthorizedMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Not authorized");
    case NotEnoughRightsMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Not enough rights for this operation");
    case NotModifiableMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Unable to edit non-modifiable resource");
    case OperationCanceledMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The operation was canceled");
    case OperationErrorMessage:
        return QT_TRANSLATE_NOOP("TMessage", "An operation error occured");
    case OperationTimeoutMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The operation timed out");
    case UnknownErrorMessage:
        return QT_TRANSLATE_NOOP("TMessage", "Some mysterious error");
    case NoMessage:
    default:
        return "";
    }
}

/*============================== Public operators ==========================*/

TMessage &TMessage::operator =(const TMessage &other)
{
    d_func()->message = other.d_func()->message;
    d_func()->extraText = other.d_func()->extraText;
    return *this;
}

TMessage &TMessage::operator =(int msg)
{
    d_func()->message = enum_cast<Message>(msg, NoMessage, UnknownErrorMessage);
    d_func()->extraText.clear();
    return *this;
}

bool TMessage::operator ==(const TMessage &other) const
{
    return d_func()->message == other.d_func()->message && d_func()->extraText == other.d_func()->extraText;
}

bool TMessage::operator !=(const TMessage &other) const
{
    return !(*this == other);
}

TMessage::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TMessage::operator QString() const
{
    return text();
}

TMessage::operator int() const
{
    return d_func()->message;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TMessage &msg)
{
    QVariantMap m;
    m.insert("message", (int) msg.d_func()->message);
    m.insert("extra_text", msg.d_func()->extraText);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TMessage &msg)
{
    QVariantMap m;
    stream >> m;
    msg.d_func()->message = enum_cast<TMessage::Message>(m.value("message"), TMessage::NoMessage,
                                                         TMessage::UnknownErrorMessage);
    msg.d_func()->extraText = m.value("extra_text").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TMessage &msg)
{
    dbg.nospace() << "TMessage(" << msg.textNoTr() << "," << msg.extraText() << ")";
    return dbg.space();
}
