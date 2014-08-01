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

#ifndef TMESSAGE_H
#define TMESSAGE_H

class TMessagePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TMessage ====================================
============================================================================*/

class T_CORE_EXPORT TMessage : public BBase
{
    B_DECLARE_PRIVATE(TMessage)
    Q_DECLARE_TR_FUNCTIONS(TMessage)
public:
    enum Message
    {
        NoMessage = 0,
        AlreadyAuthorizedMessage,
        AlreadyDeletedMessage,
        AlreadyExistsMessage,
        ConnectionTimeoutMessage,
        InternalErrorMessage,
        InvalidCommandMessage,
        InvalidDataMessage,
        InvalidIdentifierMessage,
        InvalidUsernameOrPasswordMessage,
        NoAccessToServiceMessage,
        NotAuthorizedMessage,
        NotEnoughRightsMessage,
        NotModifiableMessage,
        OperationCanceledMessage,
        OperationErrorMessage,
        OperationTimeoutMessage,
        UnknownErrorMessage
    };
public:
    TMessage(int msg = NoMessage);
    explicit TMessage(int msg, const QString &extraText);
    TMessage(const TMessage &other);
    ~TMessage();
protected:
    explicit TMessage(TMessagePrivate &d);
public:
    QString extraText() const;
    void setExtraText(const QString &extraText);
    QString text() const;
    QString textNoTr() const;
public:
    TMessage &operator =(const TMessage &other);
    TMessage &operator =(int msg);
    bool operator ==(const TMessage &other) const;
    bool operator !=(const TMessage &other) const;
    operator QVariant() const;
    operator QString() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TMessage &msg);
    friend QDataStream &operator >>(QDataStream &stream, TMessage &msg);
    friend QDebug operator <<(QDebug dbg, const TMessage &msg);
};

Q_DECLARE_METATYPE(TMessage)

#endif // TMESSAGE_H
