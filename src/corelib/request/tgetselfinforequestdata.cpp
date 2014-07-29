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

#include "tgetselfinforequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSelfInfoRequestDataPrivate ==============
============================================================================*/

class TGetSelfInfoRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSelfInfoRequestData)
public:
    bool includeAvatar;
public:
    explicit TGetSelfInfoRequestDataPrivate(TGetSelfInfoRequestData *q);
    ~TGetSelfInfoRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSelfInfoRequestDataPrivate)
};

/*============================================================================
================================ TGetSelfInfoRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetSelfInfoRequestDataPrivate::TGetSelfInfoRequestDataPrivate(TGetSelfInfoRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetSelfInfoRequestDataPrivate::~TGetSelfInfoRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSelfInfoRequestDataPrivate::init()
{
    includeAvatar = false;
}

/*============================================================================
================================ TGetSelfInfoRequestData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSelfInfoRequestData::TGetSelfInfoRequestData() :
    BBase(*new TGetSelfInfoRequestDataPrivate(this))
{
    d_func()->init();
}

TGetSelfInfoRequestData::TGetSelfInfoRequestData(const TGetSelfInfoRequestData &other) :
    BBase(*new TGetSelfInfoRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSelfInfoRequestData::~TGetSelfInfoRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetSelfInfoRequestData::clear()
{
    d_func()->includeAvatar = false;
}

bool TGetSelfInfoRequestData::includeAvatar() const
{
    return d_func()->includeAvatar;
}

bool TGetSelfInfoRequestData::isValid() const
{
    return true;
}

void TGetSelfInfoRequestData::setIncludeAvatar(bool include)
{
    d_func()->includeAvatar = include;
}

/*============================== Public operators ==========================*/

TGetSelfInfoRequestData &TGetSelfInfoRequestData::operator =(const TGetSelfInfoRequestData &other)
{
    B_D(TGetSelfInfoRequestData);
    const TGetSelfInfoRequestDataPrivate *dd = other.d_func();
    d->includeAvatar = dd->includeAvatar;
    return *this;
}

bool TGetSelfInfoRequestData::operator ==(const TGetSelfInfoRequestData &other) const
{
    const B_D(TGetSelfInfoRequestData);
    const TGetSelfInfoRequestDataPrivate *dd = other.d_func();
    return d->includeAvatar == dd->includeAvatar;
}

bool TGetSelfInfoRequestData::operator !=(const TGetSelfInfoRequestData &other) const
{
    return !(*this == other);
}

TGetSelfInfoRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoRequestData &data)
{
    const TGetSelfInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("include_avatar", d->includeAvatar);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSelfInfoRequestData &data)
{
    TGetSelfInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->includeAvatar = m.value("include_avatar").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSelfInfoRequestData &/*data*/)
{
    //const TGetSelfInfoRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSelfInfoRequestData(" << ")";
    return dbg.space();
}
