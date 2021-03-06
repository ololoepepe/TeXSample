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

#include "trequestrecoverycoderequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRequestRecoveryCodeRequestDataPrivate ======
============================================================================*/

class TRequestRecoveryCodeRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRequestRecoveryCodeRequestData)
public:
    QString email;
public:
    explicit TRequestRecoveryCodeRequestDataPrivate(TRequestRecoveryCodeRequestData *q);
    ~TRequestRecoveryCodeRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRequestRecoveryCodeRequestDataPrivate)
};

/*============================================================================
================================ TRequestRecoveryCodeRequestDataPrivate ======
============================================================================*/

/*============================== Public constructors =======================*/

TRequestRecoveryCodeRequestDataPrivate::TRequestRecoveryCodeRequestDataPrivate(TRequestRecoveryCodeRequestData *q) :
    BBasePrivate(q)
{
    //
}

TRequestRecoveryCodeRequestDataPrivate::~TRequestRecoveryCodeRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRequestRecoveryCodeRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRequestRecoveryCodeRequestData =============
============================================================================*/

/*============================== Public constructors =======================*/

TRequestRecoveryCodeRequestData::TRequestRecoveryCodeRequestData() :
    BBase(*new TRequestRecoveryCodeRequestDataPrivate(this))
{
    d_func()->init();
}

TRequestRecoveryCodeRequestData::TRequestRecoveryCodeRequestData(const TRequestRecoveryCodeRequestData &other) :
    BBase(*new TRequestRecoveryCodeRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRequestRecoveryCodeRequestData::~TRequestRecoveryCodeRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TRequestRecoveryCodeRequestData::clear()
{
    d_func()->email.clear();
}

QString TRequestRecoveryCodeRequestData::email() const
{
    return d_func()->email;
}

bool TRequestRecoveryCodeRequestData::isValid() const
{
    return !d_func()->email.isEmpty();
}

void TRequestRecoveryCodeRequestData::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

/*============================== Public operators ==========================*/

TRequestRecoveryCodeRequestData &TRequestRecoveryCodeRequestData::operator =(const TRequestRecoveryCodeRequestData &other)
{
    B_D(TRequestRecoveryCodeRequestData);
    const TRequestRecoveryCodeRequestDataPrivate *dd = other.d_func();
    d->email = dd->email;
    return *this;
}

bool TRequestRecoveryCodeRequestData::operator ==(const TRequestRecoveryCodeRequestData &other) const
{
    const B_D(TRequestRecoveryCodeRequestData);
    const TRequestRecoveryCodeRequestDataPrivate *dd = other.d_func();
    return d->email == dd->email;
}

bool TRequestRecoveryCodeRequestData::operator !=(const TRequestRecoveryCodeRequestData &other) const
{
    return !(*this == other);
}

TRequestRecoveryCodeRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeRequestData &data)
{
    const TRequestRecoveryCodeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("email", d->email);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeRequestData &data)
{
    TRequestRecoveryCodeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->email = m.value("email").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeRequestData &/*data*/)
{
    //const TRequestRecoveryCodeRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TRequestRecoveryCodeRequestData(" << ")";
    return dbg.space();
}
