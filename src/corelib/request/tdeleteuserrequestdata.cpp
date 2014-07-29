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

#include "tdeleteuserrequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteUserRequestDataPrivate ===============
============================================================================*/

class TDeleteUserRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteUserRequestData)
public:
    TUserIdentifier identifier;
public:
    explicit TDeleteUserRequestDataPrivate(TDeleteUserRequestData *q);
    ~TDeleteUserRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteUserRequestDataPrivate)
};

/*============================================================================
================================ TDeleteUserRequestDataPrivate ===============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserRequestDataPrivate::TDeleteUserRequestDataPrivate(TDeleteUserRequestData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteUserRequestDataPrivate::~TDeleteUserRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteUserRequestData ======================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserRequestData::TDeleteUserRequestData() :
    BBase(*new TDeleteUserRequestDataPrivate(this))
{
    d_func()->init();
}

TDeleteUserRequestData::TDeleteUserRequestData(const TDeleteUserRequestData &other) :
    BBase(*new TDeleteUserRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteUserRequestData::~TDeleteUserRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserRequestData::clear()
{
    d_func()->identifier.clear();
}

TUserIdentifier TDeleteUserRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TDeleteUserRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TDeleteUserRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

/*============================== Public operators ==========================*/

TDeleteUserRequestData &TDeleteUserRequestData::operator =(const TDeleteUserRequestData &other)
{
    B_D(TDeleteUserRequestData);
    const TDeleteUserRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    return *this;
}

bool TDeleteUserRequestData::operator ==(const TDeleteUserRequestData &other) const
{
    const B_D(TDeleteUserRequestData);
    const TDeleteUserRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier;
}

bool TDeleteUserRequestData::operator !=(const TDeleteUserRequestData &other) const
{
    return !(*this == other);
}

TDeleteUserRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteUserRequestData &data)
{
    const TDeleteUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteUserRequestData &data)
{
    TDeleteUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteUserRequestData &/*data*/)
{
    //const TDeleteUserRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteUserRequestData(" << ")";
    return dbg.space();
}
