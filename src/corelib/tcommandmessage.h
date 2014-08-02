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

#ifndef TCOMMANDMESSAGE_H
#define TCOMMANDMESSAGE_H

class TCommandMessagePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>
#include <QStringList>

/*============================================================================
================================ TCommandMessage =============================
============================================================================*/

class T_CORE_EXPORT TCommandMessage : public BBase
{
    B_DECLARE_PRIVATE(TCommandMessage)
    Q_DECLARE_TR_FUNCTIONS(TCommandMessage)
public:
    enum Message
    {
        NoMessage = 0,
        FailedToStartServerMessage,
        InternalErrorMessage,
        InvalidArgumentCountMessage,
        InvalidArgumentsMessage,
        NoSuchUserError,
        OkMessage,
        ServerAlreadyListeningMessage,
        ServerNotListeningMessage,
        UptimeMessage,
        UserCountMessage,
        UserInfoListMessage,
        UserInfoMessage,
        UserKickedMessage,
        UsersConnectedAtMessage,
        UsersUptimeMessage,
        UnknownErrorMessage
    };
public:
    TCommandMessage(int msg = NoMessage);
    explicit TCommandMessage(int msg, const QString &extraText);
    TCommandMessage(const TCommandMessage &other);
    ~TCommandMessage();
protected:
    explicit TCommandMessage(TCommandMessagePrivate &d);
public:
    QString extraText() const;
    void setExtraText(const QString &extraText);
    QString text(const QStringList &args = QStringList()) const;
    QString textNoTr() const;
    QString textNoTr(const QStringList &args) const;
public:
    TCommandMessage &operator =(const TCommandMessage &other);
    TCommandMessage &operator =(int msg);
    bool operator ==(const TCommandMessage &other) const;
    bool operator !=(const TCommandMessage &other) const;
    operator QVariant() const;
    operator QString() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCommandMessage &msg);
    friend QDataStream &operator >>(QDataStream &stream, TCommandMessage &msg);
    friend QDebug operator <<(QDebug dbg, const TCommandMessage &msg);
};

Q_DECLARE_METATYPE(TCommandMessage)

#endif // TCOMMANDMESSAGE_H
