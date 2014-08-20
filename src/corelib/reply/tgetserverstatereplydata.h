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

#ifndef TGETSERVERSTATEREPLYDATA_H
#define TGETSERVERSTATEREPLYDATA_H

class TGetServerStateReplyDataPrivate;

class TServerState;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetServerStateReplyData ====================
============================================================================*/

class T_CORE_EXPORT TGetServerStateReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetServerStateReplyData)
public:
    explicit TGetServerStateReplyData();
    TGetServerStateReplyData(const TGetServerStateReplyData &other);
    ~TGetServerStateReplyData();
public:
    TServerState serverState() const;
    void setServerState(const TServerState &state);
public:
    TGetServerStateReplyData &operator =(const TGetServerStateReplyData &other);
    bool operator ==(const TGetServerStateReplyData &other) const;
    bool operator !=(const TGetServerStateReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetServerStateReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetServerStateReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetServerStateReplyData &data);
};

Q_DECLARE_METATYPE(TGetServerStateReplyData)

#endif // TGETSERVERSTATEREPLYDATA_H
