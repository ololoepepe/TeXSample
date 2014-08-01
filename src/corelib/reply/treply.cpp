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

#include "treply.h"

#include "tmessage.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TReplyPrivate ===============================
============================================================================*/

class TReplyPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TReply)
public:
    bool cacheUpToDate;
    QVariant data;
    TMessage message;
    QDateTime requestDateTime;
    bool success;
public:
    explicit TReplyPrivate(TReply *q);
    ~TReplyPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TReplyPrivate)
};

/*============================================================================
================================ TReplyPrivate ===============================
============================================================================*/

/*============================== Public constructors =======================*/

TReplyPrivate::TReplyPrivate(TReply *q) :
    BBasePrivate(q)
{
    //
}

TReplyPrivate::~TReplyPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TReplyPrivate::init()
{
    cacheUpToDate = false;
    requestDateTime.setTimeSpec(Qt::UTC);
    success = false;
}

/*============================================================================
================================ TReply ======================================
============================================================================*/

/*============================== Public constructors =======================*/

TReply::TReply() :
    BBase(*new TReplyPrivate(this))
{
    d_func()->init();
}

TReply::TReply(const TMessage &message) :
    BBase(*new TReplyPrivate(this))
{
    d_func()->init();
    d_func()->message = message;
}

TReply::TReply(const TReply &other) :
    BBase(*new TReplyPrivate(this))
{
    d_func()->init();
    *this = other;
}

TReply::~TReply()
{
    //
}

/*============================== Public methods ============================*/

void TReply::clear()
{
    B_D(TReply);
    d->cacheUpToDate = false;
    d->data.clear();
    d->message = TMessage();
    d->requestDateTime = QDateTime().toUTC();
    d->success = false;
}

bool TReply::cacheUpToDate() const
{
    return d_func()->cacheUpToDate;
}

QVariant TReply::data() const
{
    return d_func()->data;
}

bool TReply::isValid() const
{
    return d_func()->data.isValid();
}

TMessage TReply::message() const
{
    return d_func()->message;
}

QString TReply::messageText() const
{
    return d_func()->message.text();
}

QString TReply::messageTextNoTr() const
{
    return d_func()->message.textNoTr();
}

QDateTime TReply::requestDateTime() const
{
    return d_func()->requestDateTime;
}

void TReply::setCacheUpToDate(bool upToDate)
{
    d_func()->cacheUpToDate = upToDate;
}

void TReply::setData(const QVariant &data)
{
    d_func()->data = data;
}

void TReply::setMessage(const TMessage &message)
{
    d_func()->message = message;
}

void TReply::setRequestDateTime(const QDateTime &dt)
{
    d_func()->requestDateTime = dt.toUTC();
}

void TReply::setSuccess(bool success)
{
    d_func()->success = success;
}

bool TReply::success() const
{
    return d_func()->success;
}

/*============================== Public operators ==========================*/

TReply &TReply::operator =(const TReply &other)
{
    B_D(TReply);
    const TReplyPrivate *dd = other.d_func();
    d->cacheUpToDate = dd->cacheUpToDate;
    d->data = dd->data;
    d->message = dd->message;
    d->requestDateTime = dd->requestDateTime;
    d->success = dd->success;
    return *this;
}

bool TReply::operator ==(const TReply &other) const
{
    const B_D(TReply);
    const TReplyPrivate *dd = other.d_func();
    return d->cacheUpToDate == dd->cacheUpToDate && d->data == dd->data && d->message == dd->message
            && d->requestDateTime == dd->requestDateTime && d->success == dd->success;
}

bool TReply::operator !=(const TReply &other) const
{
    return !(*this == other);
}

TReply::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TReply::operator bool() const
{
    return d_func()->success;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TReply &data)
{
    const TReplyPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("cache_up_to_date", d->cacheUpToDate);
    m.insert("data", d->data);
    m.insert("message", d->message);
    m.insert("request_date_time", d->requestDateTime);
    m.insert("success", d->success);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TReply &data)
{
    TReplyPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->cacheUpToDate = m.value("cache_up_to_date").toBool();
    d->data = m.value("data");
    d->message = m.value("message").value<TMessage>();
    d->requestDateTime = m.value("request_date_time").toDateTime().toUTC();
    d->success = m.value("success").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TReply &data)
{
    const TReplyPrivate *d = data.d_func();
    dbg.nospace() << "TReply(" << d->success << ")";
    return dbg.space();
}
