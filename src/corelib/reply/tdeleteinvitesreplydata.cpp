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

#include "tdeleteinvitesreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteInvitesReplyDataPrivate ==============
============================================================================*/

class TDeleteInvitesReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteInvitesReplyData)
public:
    quint32 count;
public:
    explicit TDeleteInvitesReplyDataPrivate(TDeleteInvitesReplyData *q);
    ~TDeleteInvitesReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteInvitesReplyDataPrivate)
};

/*============================================================================
================================ TDeleteInvitesReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesReplyDataPrivate::TDeleteInvitesReplyDataPrivate(TDeleteInvitesReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteInvitesReplyDataPrivate::~TDeleteInvitesReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteInvitesReplyDataPrivate::init()
{
    count = 0;
}

/*============================================================================
================================ TDeleteInvitesReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesReplyData::TDeleteInvitesReplyData() :
    BBase(*new TDeleteInvitesReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteInvitesReplyData::TDeleteInvitesReplyData(const TDeleteInvitesReplyData &other) :
    BBase(*new TDeleteInvitesReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteInvitesReplyData::~TDeleteInvitesReplyData()
{
    //
}

/*============================== Public methods ============================*/

quint32 TDeleteInvitesReplyData::count() const
{
    return d_func()->count;
}

void TDeleteInvitesReplyData::setCount(quint32 count)
{
    d_func()->count = count;
}

/*============================== Public operators ==========================*/

TDeleteInvitesReplyData &TDeleteInvitesReplyData::operator =(const TDeleteInvitesReplyData &other)
{
    B_D(TDeleteInvitesReplyData);
    const TDeleteInvitesReplyDataPrivate *dd = other.d_func();
    d->count = dd->count;
    return *this;
}

bool TDeleteInvitesReplyData::operator ==(const TDeleteInvitesReplyData &other) const
{
    const B_D(TDeleteInvitesReplyData);
    const TDeleteInvitesReplyDataPrivate *dd = other.d_func();
    return d->count == dd->count;
}

bool TDeleteInvitesReplyData::operator !=(const TDeleteInvitesReplyData &other) const
{
    return !(*this == other);
}

TDeleteInvitesReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesReplyData &data)
{
    const TDeleteInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("count", d->count);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteInvitesReplyData &data)
{
    TDeleteInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->count = m.value("count").toUInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteInvitesReplyData &/*data*/)
{
    //const TDeleteInvitesReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteInvitesReplyData(" << ")";
    return dbg.space();
}
