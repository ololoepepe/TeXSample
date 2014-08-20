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

#include "tgetserverstatereplydata.h"

#include "tserverstate.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetServerStateReplyDataPrivate =============
============================================================================*/

class TGetServerStateReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetServerStateReplyData)
public:
    TServerState serverState;
public:
    explicit TGetServerStateReplyDataPrivate(TGetServerStateReplyData *q);
    ~TGetServerStateReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetServerStateReplyDataPrivate)
};


/*============================================================================
================================ TGetServerStateReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TGetServerStateReplyDataPrivate::TGetServerStateReplyDataPrivate(TGetServerStateReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetServerStateReplyDataPrivate::~TGetServerStateReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetServerStateReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetServerStateReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetServerStateReplyData::TGetServerStateReplyData() :
    BBase(*new TGetServerStateReplyDataPrivate(this))
{
    d_func()->init();
}

TGetServerStateReplyData::TGetServerStateReplyData(const TGetServerStateReplyData &other) :
    BBase(*new TGetServerStateReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetServerStateReplyData::~TGetServerStateReplyData()
{
    //
}

/*============================== Public methods ============================*/

TServerState TGetServerStateReplyData::serverState() const
{
    return d_func()->serverState;
}

void TGetServerStateReplyData::setServerState(const TServerState &state)
{
    d_func()->serverState = state;
}

/*============================== Public operators ==========================*/

TGetServerStateReplyData &TGetServerStateReplyData::operator =(const TGetServerStateReplyData &other)
{
    B_D(TGetServerStateReplyData);
    const TGetServerStateReplyDataPrivate *dd = other.d_func();
    d->serverState = dd->serverState;
    return *this;
}

bool TGetServerStateReplyData::operator ==(const TGetServerStateReplyData &other) const
{
    const B_D(TGetServerStateReplyData);
    const TGetServerStateReplyDataPrivate *dd = other.d_func();
    return d->serverState == dd->serverState;
}

bool TGetServerStateReplyData::operator !=(const TGetServerStateReplyData &other) const
{
    return !(*this == other);
}

TGetServerStateReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetServerStateReplyData &data)
{
    const TGetServerStateReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("server_state", d->serverState);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetServerStateReplyData &data)
{
    TGetServerStateReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->serverState = m.value("server_state").value<TServerState>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetServerStateReplyData &/*data*/)
{
    //const TGetServerStateReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetServerStateReplyData(" << ")";
    return dbg.space();
}
