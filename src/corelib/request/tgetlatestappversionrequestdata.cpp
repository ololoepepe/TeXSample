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

#include "tgetlatestappversionrequestdata.h"

#include "tclientinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLatestAppVersionRequestDataPrivate ======
============================================================================*/

class TGetLatestAppVersionRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLatestAppVersionRequestData)
public:
    TClientInfo clientInfo;
public:
    explicit TGetLatestAppVersionRequestDataPrivate(TGetLatestAppVersionRequestData *q);
    ~TGetLatestAppVersionRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLatestAppVersionRequestDataPrivate)
};

/*============================================================================
================================ TGetLatestAppVersionRequestDataPrivate ======
============================================================================*/

/*============================== Public constructors =======================*/

TGetLatestAppVersionRequestDataPrivate::TGetLatestAppVersionRequestDataPrivate(TGetLatestAppVersionRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetLatestAppVersionRequestDataPrivate::~TGetLatestAppVersionRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLatestAppVersionRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLatestAppVersionRequestData =============
============================================================================*/

/*============================== Public constructors =======================*/

TGetLatestAppVersionRequestData::TGetLatestAppVersionRequestData() :
    BBase(*new TGetLatestAppVersionRequestDataPrivate(this))
{
    d_func()->init();
}

TGetLatestAppVersionRequestData::TGetLatestAppVersionRequestData(const TGetLatestAppVersionRequestData &other) :
    BBase(*new TGetLatestAppVersionRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLatestAppVersionRequestData::~TGetLatestAppVersionRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetLatestAppVersionRequestData::clear()
{
    B_D(TGetLatestAppVersionRequestData);
    d->clientInfo = TClientInfo();
}

TClientInfo TGetLatestAppVersionRequestData::clientInfo() const
{
    return d_func()->clientInfo;
}

bool TGetLatestAppVersionRequestData::isValid() const
{
    const B_D(TGetLatestAppVersionRequestData);
    return d->clientInfo.isValid();
}

void TGetLatestAppVersionRequestData::setClientInfo(const TClientInfo &info)
{
    d_func()->clientInfo = info;
}

/*============================== Public operators ==========================*/

TGetLatestAppVersionRequestData &TGetLatestAppVersionRequestData::operator =(const TGetLatestAppVersionRequestData &other)
{
    B_D(TGetLatestAppVersionRequestData);
    const TGetLatestAppVersionRequestDataPrivate *dd = other.d_func();
    d->clientInfo = dd->clientInfo;
    return *this;
}

bool TGetLatestAppVersionRequestData::operator ==(const TGetLatestAppVersionRequestData &other) const
{
    const B_D(TGetLatestAppVersionRequestData);
    const TGetLatestAppVersionRequestDataPrivate *dd = other.d_func();
    return d->clientInfo == dd->clientInfo;
}

bool TGetLatestAppVersionRequestData::operator !=(const TGetLatestAppVersionRequestData &other) const
{
    return !(*this == other);
}

TGetLatestAppVersionRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionRequestData &data)
{
    const TGetLatestAppVersionRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("clien_info", d->clientInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionRequestData &data)
{
    TGetLatestAppVersionRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->clientInfo = m.value("client_info").value<TClientInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLatestAppVersionRequestData &/*data*/)
{
    //const TGetLatestAppVersionRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLatestAppVersionRequestData(" << ")";
    return dbg.space();
}
