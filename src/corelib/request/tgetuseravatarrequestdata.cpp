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

#include "tgetuseravatarrequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserAvatarRequestDataPrivate ============
============================================================================*/

class TGetUserAvatarRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserAvatarRequestData)
public:
    TUserIdentifier identifier;
public:
    explicit TGetUserAvatarRequestDataPrivate(TGetUserAvatarRequestData *q);
    ~TGetUserAvatarRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserAvatarRequestDataPrivate)
};

/*============================================================================
================================ TGetUserAvatarRequestDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarRequestDataPrivate::TGetUserAvatarRequestDataPrivate(TGetUserAvatarRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserAvatarRequestDataPrivate::~TGetUserAvatarRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserAvatarRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserAvatarRequestData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarRequestData::TGetUserAvatarRequestData() :
    BBase(*new TGetUserAvatarRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserAvatarRequestData::TGetUserAvatarRequestData(const TGetUserAvatarRequestData &other) :
    BBase(*new TGetUserAvatarRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserAvatarRequestData::~TGetUserAvatarRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserAvatarRequestData::clear()
{
    d_func()->identifier.clear();
}

TUserIdentifier TGetUserAvatarRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TGetUserAvatarRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TGetUserAvatarRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

/*============================== Public operators ==========================*/

TGetUserAvatarRequestData &TGetUserAvatarRequestData::operator =(const TGetUserAvatarRequestData &other)
{
    B_D(TGetUserAvatarRequestData);
    const TGetUserAvatarRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    return *this;
}

bool TGetUserAvatarRequestData::operator ==(const TGetUserAvatarRequestData &other) const
{
    const B_D(TGetUserAvatarRequestData);
    const TGetUserAvatarRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier;
}

bool TGetUserAvatarRequestData::operator !=(const TGetUserAvatarRequestData &other) const
{
    return !(*this == other);
}

TGetUserAvatarRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarRequestData &data)
{
    const TGetUserAvatarRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserAvatarRequestData &data)
{
    TGetUserAvatarRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserAvatarRequestData &/*data*/)
{
    //const TGetUserAvatarRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserAvatarRequestData(" << ")";
    return dbg.space();
}
