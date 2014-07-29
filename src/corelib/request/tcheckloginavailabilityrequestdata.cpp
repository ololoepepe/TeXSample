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

#include "tcheckloginavailabilityrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCheckLoginAvailabilityRequestDataPrivate ===
============================================================================*/

class TCheckLoginAvailabilityRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCheckLoginAvailabilityRequestData)
public:
    QString login;
public:
    explicit TCheckLoginAvailabilityRequestDataPrivate(TCheckLoginAvailabilityRequestData *q);
    ~TCheckLoginAvailabilityRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCheckLoginAvailabilityRequestDataPrivate)
};

/*============================================================================
================================ TCheckLoginAvailabilityRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TCheckLoginAvailabilityRequestDataPrivate::TCheckLoginAvailabilityRequestDataPrivate(
        TCheckLoginAvailabilityRequestData *q) :
    BBasePrivate(q)
{
    //
}

TCheckLoginAvailabilityRequestDataPrivate::~TCheckLoginAvailabilityRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCheckLoginAvailabilityRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TCheckLoginAvailabilityRequestData ==========
============================================================================*/

/*============================== Public constructors =======================*/

TCheckLoginAvailabilityRequestData::TCheckLoginAvailabilityRequestData() :
    BBase(*new TCheckLoginAvailabilityRequestDataPrivate(this))
{
    d_func()->init();
}

TCheckLoginAvailabilityRequestData::TCheckLoginAvailabilityRequestData(
        const TCheckLoginAvailabilityRequestData &other) :
    BBase(*new TCheckLoginAvailabilityRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCheckLoginAvailabilityRequestData::~TCheckLoginAvailabilityRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TCheckLoginAvailabilityRequestData::clear()
{
    d_func()->login.clear();
}

bool TCheckLoginAvailabilityRequestData::isValid() const
{
    return !d_func()->login.isEmpty();
}

QString TCheckLoginAvailabilityRequestData::login() const
{
    return d_func()->login;
}

void TCheckLoginAvailabilityRequestData::setLogin(const QString &login)
{
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

/*============================== Public operators ==========================*/

TCheckLoginAvailabilityRequestData &TCheckLoginAvailabilityRequestData::operator =(
        const TCheckLoginAvailabilityRequestData &other)
{
    B_D(TCheckLoginAvailabilityRequestData);
    const TCheckLoginAvailabilityRequestDataPrivate *dd = other.d_func();
    d->login = dd->login;
    return *this;
}

bool TCheckLoginAvailabilityRequestData::operator ==(const TCheckLoginAvailabilityRequestData &other) const
{
    const B_D(TCheckLoginAvailabilityRequestData);
    const TCheckLoginAvailabilityRequestDataPrivate *dd = other.d_func();
    return d->login == dd->login;
}

bool TCheckLoginAvailabilityRequestData::operator !=(const TCheckLoginAvailabilityRequestData &other) const
{
    return !(*this == other);
}

TCheckLoginAvailabilityRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityRequestData &data)
{
    const TCheckLoginAvailabilityRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("login", d->login);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityRequestData &data)
{
    TCheckLoginAvailabilityRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->login = m.value("login").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityRequestData &/*data*/)
{
    //const TCheckLoginAvailabilityRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TCheckLoginAvailabilityRequestData(" << ")";
    return dbg.space();
}
