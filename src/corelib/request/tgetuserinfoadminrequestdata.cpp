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

#include "tgetuserinfoadminrequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoAdminRequestDataPrivate =========
============================================================================*/

class TGetUserInfoAdminRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoAdminRequestData)
public:
    TUserIdentifier identifier;
    bool includeAvatar;
public:
    explicit TGetUserInfoAdminRequestDataPrivate(TGetUserInfoAdminRequestData *q);
    ~TGetUserInfoAdminRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoAdminRequestDataPrivate)
};

/*============================================================================
================================ TGetUserInfoAdminRequestDataPrivate =========
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoAdminRequestDataPrivate::TGetUserInfoAdminRequestDataPrivate(TGetUserInfoAdminRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoAdminRequestDataPrivate::~TGetUserInfoAdminRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoAdminRequestDataPrivate::init()
{
    includeAvatar = false;
}

/*============================================================================
================================ TGetUserInfoAdminRequestData ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoAdminRequestData::TGetUserInfoAdminRequestData() :
    BBase(*new TGetUserInfoAdminRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoAdminRequestData::TGetUserInfoAdminRequestData(const TGetUserInfoAdminRequestData &other) :
    BBase(*new TGetUserInfoAdminRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoAdminRequestData::~TGetUserInfoAdminRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoAdminRequestData::clear()
{
    d_func()->identifier.clear();
    d_func()->includeAvatar = false;
}

TUserIdentifier TGetUserInfoAdminRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TGetUserInfoAdminRequestData::includeAvatar() const
{
    return d_func()->includeAvatar;
}

bool TGetUserInfoAdminRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TGetUserInfoAdminRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

void TGetUserInfoAdminRequestData::setIncludeAvatar(bool include)
{
    d_func()->includeAvatar = include;
}

/*============================== Public operators ==========================*/

TGetUserInfoAdminRequestData &TGetUserInfoAdminRequestData::operator =(const TGetUserInfoAdminRequestData &other)
{
    B_D(TGetUserInfoAdminRequestData);
    const TGetUserInfoAdminRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    d->includeAvatar = dd->includeAvatar;
    return *this;
}

bool TGetUserInfoAdminRequestData::operator ==(const TGetUserInfoAdminRequestData &other) const
{
    const B_D(TGetUserInfoAdminRequestData);
    const TGetUserInfoAdminRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier && d->includeAvatar == dd->includeAvatar;
}

bool TGetUserInfoAdminRequestData::operator !=(const TGetUserInfoAdminRequestData &other) const
{
    return !(*this == other);
}

TGetUserInfoAdminRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoAdminRequestData &data)
{
    const TGetUserInfoAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    m.insert("include_avatar", d->includeAvatar);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoAdminRequestData &data)
{
    TGetUserInfoAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    d->includeAvatar = m.value("include_avatar").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoAdminRequestData &/*data*/)
{
    //const TGetUserInfoAdminRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoAdminRequestData(" << ")";
    return dbg.space();
}
