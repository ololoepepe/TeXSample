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
