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

#include "tsetserverstaterequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSetServerStateRequestDataPrivate ===========
============================================================================*/

class TSetServerStateRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSetServerStateRequestData)
public:
    QString address;
    bool listening;
public:
    explicit TSetServerStateRequestDataPrivate(TSetServerStateRequestData *q);
    ~TSetServerStateRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSetServerStateRequestDataPrivate)
};


/*============================================================================
================================ TSetServerStateRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TSetServerStateRequestDataPrivate::TSetServerStateRequestDataPrivate(TSetServerStateRequestData *q) :
    BBasePrivate(q)
{
    //
}

TSetServerStateRequestDataPrivate::~TSetServerStateRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSetServerStateRequestDataPrivate::init()
{
    listening = false;
}

/*============================================================================
================================ TSetServerStateRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TSetServerStateRequestData::TSetServerStateRequestData() :
    BBase(*new TSetServerStateRequestDataPrivate(this))
{
    d_func()->init();
}

TSetServerStateRequestData::TSetServerStateRequestData(const TSetServerStateRequestData &other) :
    BBase(*new TSetServerStateRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSetServerStateRequestData::~TSetServerStateRequestData()
{
    //
}

/*============================== Public methods ============================*/

QString TSetServerStateRequestData::address() const
{
    return d_func()->address;
}

void TSetServerStateRequestData::clear()
{
    B_D(TSetServerStateRequestData);
    d->address.clear();
    d->listening = false;
}

bool TSetServerStateRequestData::listening()
{
    return d_func()->listening;
}

bool TSetServerStateRequestData::isValid()
{
    return true;
}

void TSetServerStateRequestData::setAddress(const QString &address)
{
    d_func()->address = address;
}

void TSetServerStateRequestData::setListening(bool listening)
{
    d_func()->listening = listening;
}

/*============================== Public operators ==========================*/

TSetServerStateRequestData &TSetServerStateRequestData::operator =(const TSetServerStateRequestData &other)
{
    B_D(TSetServerStateRequestData);
    const TSetServerStateRequestDataPrivate *dd = other.d_func();
    d->address = dd->address;
    d->listening = dd->listening;
    return *this;
}

bool TSetServerStateRequestData::operator ==(const TSetServerStateRequestData &other) const
{
    const B_D(TSetServerStateRequestData);
    const TSetServerStateRequestDataPrivate *dd = other.d_func();
    return d->address == dd->address && d->listening == dd->listening;
}

bool TSetServerStateRequestData::operator !=(const TSetServerStateRequestData &other) const
{
    return !(*this == other);
}

TSetServerStateRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSetServerStateRequestData &data)
{
    const TSetServerStateRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("address", d->address);
    m.insert("listening", d->listening);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSetServerStateRequestData &data)
{
    TSetServerStateRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->address = m.value("address").toString();
    d->listening = m.value("listening").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSetServerStateRequestData &/*data*/)
{
    //const TSetServerStateRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TSetServerStateRequestData(" << ")";
    return dbg.space();
}
