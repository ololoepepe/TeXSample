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

#include "tcheckloginavailabilityreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCheckLoginAvailabilityReplyDataPrivate =====
============================================================================*/

class TCheckLoginAvailabilityReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCheckLoginAvailabilityReplyData)
public:
    bool available;
public:
    explicit TCheckLoginAvailabilityReplyDataPrivate(TCheckLoginAvailabilityReplyData *q);
    ~TCheckLoginAvailabilityReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCheckLoginAvailabilityReplyDataPrivate)
};

/*============================================================================
================================ TCheckLoginAvailabilityReplyDataPrivate =====
============================================================================*/

/*============================== Public constructors =======================*/

TCheckLoginAvailabilityReplyDataPrivate::TCheckLoginAvailabilityReplyDataPrivate(TCheckLoginAvailabilityReplyData *q) :
    BBasePrivate(q)
{
    //
}

TCheckLoginAvailabilityReplyDataPrivate::~TCheckLoginAvailabilityReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCheckLoginAvailabilityReplyDataPrivate::init()
{
    available = false;
}

/*============================================================================
================================ TCheckLoginAvailabilityReplyData ============
============================================================================*/

/*============================== Public constructors =======================*/

TCheckLoginAvailabilityReplyData::TCheckLoginAvailabilityReplyData() :
    BBase(*new TCheckLoginAvailabilityReplyDataPrivate(this))
{
    d_func()->init();
}

TCheckLoginAvailabilityReplyData::TCheckLoginAvailabilityReplyData(const TCheckLoginAvailabilityReplyData &other) :
    BBase(*new TCheckLoginAvailabilityReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCheckLoginAvailabilityReplyData::~TCheckLoginAvailabilityReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TCheckLoginAvailabilityReplyData::setAvailable(bool available)
{
    d_func()->available = available;
}

bool TCheckLoginAvailabilityReplyData::available() const
{
    return d_func()->available;
}

/*============================== Public operators ==========================*/

TCheckLoginAvailabilityReplyData &TCheckLoginAvailabilityReplyData::operator =(
        const TCheckLoginAvailabilityReplyData &other)
{
    B_D(TCheckLoginAvailabilityReplyData);
    const TCheckLoginAvailabilityReplyDataPrivate *dd = other.d_func();
    d->available = dd->available;
    return *this;
}

bool TCheckLoginAvailabilityReplyData::operator ==(const TCheckLoginAvailabilityReplyData &other) const
{
    const B_D(TCheckLoginAvailabilityReplyData);
    const TCheckLoginAvailabilityReplyDataPrivate *dd = other.d_func();
    return d->available == dd->available;
}

bool TCheckLoginAvailabilityReplyData::operator !=(const TCheckLoginAvailabilityReplyData &other) const
{
    return !(*this == other);
}

TCheckLoginAvailabilityReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityReplyData &data)
{
    const TCheckLoginAvailabilityReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("available", d->available);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityReplyData &data)
{
    TCheckLoginAvailabilityReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->available = m.value("available").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityReplyData &/*data*/)
{
    //const TCheckLoginAvailabilityReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TCheckLoginAvailabilityReplyData(" << ")";
    return dbg.space();
}
