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

#ifndef TSERVERSTATE_H
#define TSERVERSTATE_H

class TServerStatePrivate;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TServerState ================================
============================================================================*/

class TServerState : public BBase
{
    B_DECLARE_PRIVATE(TServerState)
public:
    explicit TServerState();
    TServerState(const TServerState &other);
    ~TServerState();
public:
    void clear();
    bool listening() const;
    void setListening(bool listening);
    void setUptime(qint64 msecs);
    qint64 uptime() const;
public:
    TServerState &operator =(const TServerState &other);
    bool operator ==(const TServerState &other) const;
    bool operator !=(const TServerState &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TServerState &data);
    friend QDataStream &operator >>(QDataStream &stream, TServerState &data);
    friend QDebug operator <<(QDebug dbg, const TServerState &data);
};

Q_DECLARE_METATYPE(TServerState)

#endif // TSERVERSTATE_H
