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

#include "tserverstate.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TServerStatePrivate =========================
============================================================================*/

class TServerStatePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TServerState)
public:
    bool listening;
    qint64 uptime;
public:
    explicit TServerStatePrivate(TServerState *q);
    ~TServerStatePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TServerStatePrivate)
};


/*============================================================================
================================ TServerStatePrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TServerStatePrivate::TServerStatePrivate(TServerState *q) :
    BBasePrivate(q)
{
    //
}

TServerStatePrivate::~TServerStatePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TServerStatePrivate::init()
{
    uptime = 0;
}

/*============================================================================
================================ TServerState ================================
============================================================================*/

/*============================== Public constructors =======================*/

TServerState::TServerState() :
    BBase(*new TServerStatePrivate(this))
{
    d_func()->init();
}

TServerState::TServerState(const TServerState &other) :
    BBase(*new TServerStatePrivate(this))
{
    d_func()->init();
    *this = other;
}

TServerState::~TServerState()
{
    //
}

/*============================== Public methods ============================*/

void TServerState::clear()
{
    B_D(TServerState);
    d->listening = false;
    d->uptime = 0;
}

bool TServerState::listening() const
{
    return d_func()->listening;
}

void TServerState::setListening(bool listening)
{
    d_func()->listening = listening;
}

void TServerState::setUptime(qint64 msecs)
{
    d_func()->uptime = (msecs > 0) ? msecs : 0;
}

qint64 TServerState::uptime() const
{
    return d_func()->uptime;
}

/*============================== Public operators ==========================*/

TServerState &TServerState::operator =(const TServerState &other)
{
    B_D(TServerState);
    const TServerStatePrivate *dd = other.d_func();
    d->listening = dd->listening;
    d->uptime = dd->uptime;
    return *this;
}

bool TServerState::operator ==(const TServerState &other) const
{
    const B_D(TServerState);
    const TServerStatePrivate *dd = other.d_func();
    return d_func()->listening == dd->listening && d->uptime == dd->uptime;
}

bool TServerState::operator !=(const TServerState &other) const
{
    return !(*this == other);
}

TServerState::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TServerState &data)
{
    const TServerStatePrivate *d = data.d_func();
    QVariantMap m;
    m.insert("listening", d->listening);
    m.insert("uptime", d->uptime);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TServerState &data)
{
    TServerStatePrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->listening = m.value("listening").toBool();
    d->uptime = m.value("uptime").toLongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TServerState &/*data*/)
{
    //const TServerStatePrivate *d = data.d_func();
    dbg.nospace() << "TServerState(" << ")";
    return dbg.space();
}
