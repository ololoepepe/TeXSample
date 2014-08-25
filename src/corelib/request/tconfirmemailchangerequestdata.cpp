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

#include "tconfirmemailchangerequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TConfirmEmailChangeRequestDataPrivate =======
============================================================================*/

class TConfirmEmailChangeRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TConfirmEmailChangeRequestData)
public:
    BUuid confirmationCode;
public:
    explicit TConfirmEmailChangeRequestDataPrivate(TConfirmEmailChangeRequestData *q);
    ~TConfirmEmailChangeRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TConfirmEmailChangeRequestDataPrivate)
};

/*============================================================================
================================ TConfirmEmailChangeRequestDataPrivate =======
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmEmailChangeRequestDataPrivate::TConfirmEmailChangeRequestDataPrivate(TConfirmEmailChangeRequestData *q) :
    BBasePrivate(q)
{
    //
}

TConfirmEmailChangeRequestDataPrivate::~TConfirmEmailChangeRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmEmailChangeRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TConfirmEmailChangeRequestData ==============
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmEmailChangeRequestData::TConfirmEmailChangeRequestData() :
    BBase(*new TConfirmEmailChangeRequestDataPrivate(this))
{
    d_func()->init();
}

TConfirmEmailChangeRequestData::TConfirmEmailChangeRequestData(const TConfirmEmailChangeRequestData &other) :
    BBase(*new TConfirmEmailChangeRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TConfirmEmailChangeRequestData::~TConfirmEmailChangeRequestData()
{
    //
}

/*============================== Public methods ============================*/

BUuid TConfirmEmailChangeRequestData::confirmationCode() const
{
    return d_func()->confirmationCode;
}

void TConfirmEmailChangeRequestData::clear()
{
    d_func()->confirmationCode = BUuid();
}

bool TConfirmEmailChangeRequestData::isValid() const
{
    return !d_func()->confirmationCode.isNull();
}

void TConfirmEmailChangeRequestData::setConfirmationCode(const BUuid &code)
{
    d_func()->confirmationCode = code;
}

/*============================== Public operators ==========================*/

TConfirmEmailChangeRequestData &TConfirmEmailChangeRequestData::operator =(
        const TConfirmEmailChangeRequestData &other)
{
    B_D(TConfirmEmailChangeRequestData);
    const TConfirmEmailChangeRequestDataPrivate *dd = other.d_func();
    d->confirmationCode = dd->confirmationCode;
    return *this;
}

bool TConfirmEmailChangeRequestData::operator ==(const TConfirmEmailChangeRequestData &other) const
{
    const B_D(TConfirmEmailChangeRequestData);
    const TConfirmEmailChangeRequestDataPrivate *dd = other.d_func();
    return d->confirmationCode == dd->confirmationCode;
}

bool TConfirmEmailChangeRequestData::operator !=(const TConfirmEmailChangeRequestData &other) const
{
    return !(*this == other);
}

TConfirmEmailChangeRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TConfirmEmailChangeRequestData &data)
{
    const TConfirmEmailChangeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("confirmation_code", d->confirmationCode);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TConfirmEmailChangeRequestData &data)
{
    TConfirmEmailChangeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->confirmationCode = m.value("confirmation_code").value<BUuid>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TConfirmEmailChangeRequestData &/*data*/)
{
    //const TConfirmEmailChangeRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TConfirmEmailChangeRequestData(" << ")";
    return dbg.space();
}
