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

#include "tcheckemailavailabilityrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCheckEmailAvailabilityRequestDataPrivate ===
============================================================================*/

class TCheckEmailAvailabilityRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCheckEmailAvailabilityRequestData)
public:
    QString email;
public:
    explicit TCheckEmailAvailabilityRequestDataPrivate(TCheckEmailAvailabilityRequestData *q);
    ~TCheckEmailAvailabilityRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCheckEmailAvailabilityRequestDataPrivate)
};

/*============================================================================
================================ TCheckEmailAvailabilityRequestDataPrivate ===
============================================================================*/

/*============================== Public constructors =======================*/

TCheckEmailAvailabilityRequestDataPrivate::TCheckEmailAvailabilityRequestDataPrivate(
        TCheckEmailAvailabilityRequestData *q) :
    BBasePrivate(q)
{
    //
}

TCheckEmailAvailabilityRequestDataPrivate::~TCheckEmailAvailabilityRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCheckEmailAvailabilityRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TCheckEmailAvailabilityRequestData ==========
============================================================================*/

/*============================== Public constructors =======================*/

TCheckEmailAvailabilityRequestData::TCheckEmailAvailabilityRequestData() :
    BBase(*new TCheckEmailAvailabilityRequestDataPrivate(this))
{
    d_func()->init();
}

TCheckEmailAvailabilityRequestData::TCheckEmailAvailabilityRequestData(
        const TCheckEmailAvailabilityRequestData &other) :
    BBase(*new TCheckEmailAvailabilityRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCheckEmailAvailabilityRequestData::~TCheckEmailAvailabilityRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TCheckEmailAvailabilityRequestData::clear()
{
    d_func()->email.clear();
}

QString TCheckEmailAvailabilityRequestData::email() const
{
    return d_func()->email;
}

bool TCheckEmailAvailabilityRequestData::isValid() const
{
    return !d_func()->email.isEmpty();
}

void TCheckEmailAvailabilityRequestData::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

/*============================== Public operators ==========================*/

TCheckEmailAvailabilityRequestData &TCheckEmailAvailabilityRequestData::operator =(
        const TCheckEmailAvailabilityRequestData &other)
{
    B_D(TCheckEmailAvailabilityRequestData);
    const TCheckEmailAvailabilityRequestDataPrivate *dd = other.d_func();
    d->email = dd->email;
    return *this;
}

bool TCheckEmailAvailabilityRequestData::operator ==(const TCheckEmailAvailabilityRequestData &other) const
{
    const B_D(TCheckEmailAvailabilityRequestData);
    const TCheckEmailAvailabilityRequestDataPrivate *dd = other.d_func();
    return d->email == dd->email;
}

bool TCheckEmailAvailabilityRequestData::operator !=(const TCheckEmailAvailabilityRequestData &other) const
{
    return !(*this == other);
}

TCheckEmailAvailabilityRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCheckEmailAvailabilityRequestData &data)
{
    const TCheckEmailAvailabilityRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("email", d->email);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCheckEmailAvailabilityRequestData &data)
{
    TCheckEmailAvailabilityRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->email = m.value("email").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCheckEmailAvailabilityRequestData &/*data*/)
{
    //const TCheckEmailAvailabilityRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TCheckEmailAvailabilityRequestData(" << ")";
    return dbg.space();
}
