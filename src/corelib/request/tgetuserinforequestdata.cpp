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

#include "tgetuserinforequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoRequestDataPrivate ==============
============================================================================*/

class TGetUserInfoRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoRequestData)
public:
    TUserIdentifier identifier;
public:
    explicit TGetUserInfoRequestDataPrivate(TGetUserInfoRequestData *q);
    ~TGetUserInfoRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoRequestDataPrivate)
};

/*============================================================================
================================ TGetUserInfoRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoRequestDataPrivate::TGetUserInfoRequestDataPrivate(TGetUserInfoRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoRequestDataPrivate::~TGetUserInfoRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoRequestData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoRequestData::TGetUserInfoRequestData() :
    BBase(*new TGetUserInfoRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoRequestData::TGetUserInfoRequestData(const TGetUserInfoRequestData &other) :
    BBase(*new TGetUserInfoRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoRequestData::~TGetUserInfoRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoRequestData::clear()
{
    d_func()->identifier.clear();
}

TUserIdentifier TGetUserInfoRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TGetUserInfoRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TGetUserInfoRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

/*============================== Public operators ==========================*/

TGetUserInfoRequestData &TGetUserInfoRequestData::operator =(const TGetUserInfoRequestData &other)
{
    B_D(TGetUserInfoRequestData);
    const TGetUserInfoRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    return *this;
}

bool TGetUserInfoRequestData::operator ==(const TGetUserInfoRequestData &other) const
{
    const B_D(TGetUserInfoRequestData);
    const TGetUserInfoRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier;
}

bool TGetUserInfoRequestData::operator !=(const TGetUserInfoRequestData &other) const
{
    return !(*this == other);
}

TGetUserInfoRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoRequestData &data)
{
    const TGetUserInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoRequestData &data)
{
    TGetUserInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoRequestData &/*data*/)
{
    //const TGetUserInfoRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoRequestData(" << ")";
    return dbg.space();
}
