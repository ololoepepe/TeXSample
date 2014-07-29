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

#include "tsubscriberequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSubscribeRequestDataPrivate =================
============================================================================*/

class TSubscribeRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSubscribeRequestData)
public:
    bool subscribedToLog;
public:
    explicit TSubscribeRequestDataPrivate(TSubscribeRequestData *q);
    ~TSubscribeRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSubscribeRequestDataPrivate)
};

/*============================================================================
================================ TSubscribeRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TSubscribeRequestDataPrivate::TSubscribeRequestDataPrivate(TSubscribeRequestData *q) :
    BBasePrivate(q)
{
    //
}

TSubscribeRequestDataPrivate::~TSubscribeRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSubscribeRequestDataPrivate::init()
{
    subscribedToLog = false;
}

/*============================================================================
================================ TSubscribeRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TSubscribeRequestData::TSubscribeRequestData() :
    BBase(*new TSubscribeRequestDataPrivate(this))
{
    d_func()->init();
}

TSubscribeRequestData::TSubscribeRequestData(const TSubscribeRequestData &other) :
    BBase(*new TSubscribeRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSubscribeRequestData::~TSubscribeRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TSubscribeRequestData::clear()
{
    d_func()->subscribedToLog = false;
}

bool TSubscribeRequestData::isValid() const
{
    return true;
}

void TSubscribeRequestData::setSubscribedTLog(bool subscribed)
{
    d_func()->subscribedToLog = subscribed;
}

bool TSubscribeRequestData::subscribedToLog() const
{
    return d_func()->subscribedToLog;
}

/*============================== Public operators ==========================*/

TSubscribeRequestData &TSubscribeRequestData::operator =(const TSubscribeRequestData &other)
{
    B_D(TSubscribeRequestData);
    const TSubscribeRequestDataPrivate *dd = other.d_func();
    d->subscribedToLog = dd->subscribedToLog;
    return *this;
}

bool TSubscribeRequestData::operator ==(const TSubscribeRequestData &other) const
{
    const B_D(TSubscribeRequestData);
    const TSubscribeRequestDataPrivate *dd = other.d_func();
    return d->subscribedToLog == dd->subscribedToLog;
}

bool TSubscribeRequestData::operator !=(const TSubscribeRequestData &other) const
{
    return !(*this == other);
}

TSubscribeRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSubscribeRequestData &data)
{
    const TSubscribeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("subscribed_to_log", d->subscribedToLog);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSubscribeRequestData &data)
{
    TSubscribeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->subscribedToLog = m.value("subscribed_to_log").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSubscribeRequestData &/*data*/)
{
    //const TSubscribeRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TSubscribeRequestData(" << ")";
    return dbg.space();
}
