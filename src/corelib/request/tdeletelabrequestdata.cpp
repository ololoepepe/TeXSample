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

#include "tdeletelabrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteLabRequestDataPrivate ================
============================================================================*/

class TDeleteLabRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteLabRequestData)
public:
    quint64 id;
public:
    explicit TDeleteLabRequestDataPrivate(TDeleteLabRequestData *q);
    ~TDeleteLabRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteLabRequestDataPrivate)
};

/*============================================================================
================================ TDeleteLabRequestDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteLabRequestDataPrivate::TDeleteLabRequestDataPrivate(TDeleteLabRequestData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteLabRequestDataPrivate::~TDeleteLabRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteLabRequestDataPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TDeleteLabRequestData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteLabRequestData::TDeleteLabRequestData() :
    BBase(*new TDeleteLabRequestDataPrivate(this))
{
    d_func()->init();
}

TDeleteLabRequestData::TDeleteLabRequestData(const TDeleteLabRequestData &other) :
    BBase(*new TDeleteLabRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteLabRequestData::~TDeleteLabRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteLabRequestData::clear()
{
    d_func()->id = 0;
}

quint64 TDeleteLabRequestData::id() const
{
    return d_func()->id;
}

bool TDeleteLabRequestData::isValid() const
{
    return d_func()->id;
}

void TDeleteLabRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

/*============================== Public operators ==========================*/

TDeleteLabRequestData &TDeleteLabRequestData::operator =(const TDeleteLabRequestData &other)
{
    B_D(TDeleteLabRequestData);
    const TDeleteLabRequestDataPrivate *dd = other.d_func();
    d->id = dd->id;
    return *this;
}

bool TDeleteLabRequestData::operator ==(const TDeleteLabRequestData &other) const
{
    const B_D(TDeleteLabRequestData);
    const TDeleteLabRequestDataPrivate *dd = other.d_func();
    return d->id == dd->id;
}

bool TDeleteLabRequestData::operator !=(const TDeleteLabRequestData &other) const
{
    return !(*this == other);
}

TDeleteLabRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteLabRequestData &data)
{
    const TDeleteLabRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteLabRequestData &data)
{
    TDeleteLabRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteLabRequestData &/*data*/)
{
    //const TDeleteLabRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteLabRequestData(" << ")";
    return dbg.space();
}
