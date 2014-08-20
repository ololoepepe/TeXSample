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

#include "tsetserverstatereplydata.h"

#include "tserverstate.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSetServerStateReplyDataPrivate =============
============================================================================*/

class TSetServerStateReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSetServerStateReplyData)
public:
    TServerState serverState;
public:
    explicit TSetServerStateReplyDataPrivate(TSetServerStateReplyData *q);
    ~TSetServerStateReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSetServerStateReplyDataPrivate)
};


/*============================================================================
================================ TSetServerStateReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TSetServerStateReplyDataPrivate::TSetServerStateReplyDataPrivate(TSetServerStateReplyData *q) :
    BBasePrivate(q)
{
    //
}

TSetServerStateReplyDataPrivate::~TSetServerStateReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSetServerStateReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TSetServerStateReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TSetServerStateReplyData::TSetServerStateReplyData() :
    BBase(*new TSetServerStateReplyDataPrivate(this))
{
    d_func()->init();
}

TSetServerStateReplyData::TSetServerStateReplyData(const TSetServerStateReplyData &other) :
    BBase(*new TSetServerStateReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSetServerStateReplyData::~TSetServerStateReplyData()
{
    //
}

/*============================== Public methods ============================*/

TServerState TSetServerStateReplyData::serverState() const
{
    return d_func()->serverState;
}

void TSetServerStateReplyData::setServerState(const TServerState &state)
{
    d_func()->serverState = state;
}

/*============================== Public operators ==========================*/

TSetServerStateReplyData &TSetServerStateReplyData::operator =(const TSetServerStateReplyData &other)
{
    B_D(TSetServerStateReplyData);
    const TSetServerStateReplyDataPrivate *dd = other.d_func();
    d->serverState = dd->serverState;
    return *this;
}

bool TSetServerStateReplyData::operator ==(const TSetServerStateReplyData &other) const
{
    const B_D(TSetServerStateReplyData);
    const TSetServerStateReplyDataPrivate *dd = other.d_func();
    return d->serverState == dd->serverState;
}

bool TSetServerStateReplyData::operator !=(const TSetServerStateReplyData &other) const
{
    return !(*this == other);
}

TSetServerStateReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSetServerStateReplyData &data)
{
    const TSetServerStateReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("server_state", d->serverState);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSetServerStateReplyData &data)
{
    TSetServerStateReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->serverState = m.value("server_state").value<TServerState>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSetServerStateReplyData &/*data*/)
{
    //const TSetServerStateReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TSetServerStateReplyData(" << ")";
    return dbg.space();
}
