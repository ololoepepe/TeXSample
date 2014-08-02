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

#include "tconfirmregistrationrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TConfirmRegistrationRequestDataPrivate ======
============================================================================*/

class TConfirmRegistrationRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TConfirmRegistrationRequestData)
public:
    BUuid confirmationCode;
public:
    explicit TConfirmRegistrationRequestDataPrivate(TConfirmRegistrationRequestData *q);
    ~TConfirmRegistrationRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TConfirmRegistrationRequestDataPrivate)
};

/*============================================================================
================================ TConfirmRegistrationRequestDataPrivate ======
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmRegistrationRequestDataPrivate::TConfirmRegistrationRequestDataPrivate(TConfirmRegistrationRequestData *q) :
    BBasePrivate(q)
{
    //
}

TConfirmRegistrationRequestDataPrivate::~TConfirmRegistrationRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmRegistrationRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TConfirmRegistrationRequestData =============
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmRegistrationRequestData::TConfirmRegistrationRequestData() :
    BBase(*new TConfirmRegistrationRequestDataPrivate(this))
{
    d_func()->init();
}

TConfirmRegistrationRequestData::TConfirmRegistrationRequestData(const TConfirmRegistrationRequestData &other) :
    BBase(*new TConfirmRegistrationRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TConfirmRegistrationRequestData::~TConfirmRegistrationRequestData()
{
    //
}

/*============================== Public methods ============================*/

BUuid TConfirmRegistrationRequestData::confirmationCode() const
{
    return d_func()->confirmationCode;
}

void TConfirmRegistrationRequestData::clear()
{
    d_func()->confirmationCode = BUuid();
}

bool TConfirmRegistrationRequestData::isValid() const
{
    return !d_func()->confirmationCode.isNull();
}

void TConfirmRegistrationRequestData::setConfirmationCode(const BUuid &code)
{
    d_func()->confirmationCode = code;
}

/*============================== Public operators ==========================*/

TConfirmRegistrationRequestData &TConfirmRegistrationRequestData::operator =(
        const TConfirmRegistrationRequestData &other)
{
    B_D(TConfirmRegistrationRequestData);
    const TConfirmRegistrationRequestDataPrivate *dd = other.d_func();
    d->confirmationCode = dd->confirmationCode;
    return *this;
}

bool TConfirmRegistrationRequestData::operator ==(const TConfirmRegistrationRequestData &other) const
{
    const B_D(TConfirmRegistrationRequestData);
    const TConfirmRegistrationRequestDataPrivate *dd = other.d_func();
    return d->confirmationCode == dd->confirmationCode;
}

bool TConfirmRegistrationRequestData::operator !=(const TConfirmRegistrationRequestData &other) const
{
    return !(*this == other);
}

TConfirmRegistrationRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TConfirmRegistrationRequestData &data)
{
    const TConfirmRegistrationRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("confirmation_code", d->confirmationCode);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TConfirmRegistrationRequestData &data)
{
    TConfirmRegistrationRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->confirmationCode = m.value("confirmation_code").value<BUuid>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TConfirmRegistrationRequestData &/*data*/)
{
    //const TConfirmRegistrationRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TConfirmRegistrationRequestData(" << ")";
    return dbg.space();
}
