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

#include "tconfirmemailchangereplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TConfirmEmailChangeReplyDataPrivate =========
============================================================================*/

class TConfirmEmailChangeReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TConfirmEmailChangeReplyData)
public:
    bool success;
public:
    explicit TConfirmEmailChangeReplyDataPrivate(TConfirmEmailChangeReplyData *q);
    ~TConfirmEmailChangeReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TConfirmEmailChangeReplyDataPrivate)
};

/*============================================================================
================================ TConfirmEmailChangeReplyDataPrivate =========
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmEmailChangeReplyDataPrivate::TConfirmEmailChangeReplyDataPrivate(TConfirmEmailChangeReplyData *q) :
    BBasePrivate(q)
{
    //
}

TConfirmEmailChangeReplyDataPrivate::~TConfirmEmailChangeReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmEmailChangeReplyDataPrivate::init()
{
    success = false;
}

/*============================================================================
================================ TConfirmEmailChangeReplyData ================
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmEmailChangeReplyData::TConfirmEmailChangeReplyData() :
    BBase(*new TConfirmEmailChangeReplyDataPrivate(this))
{
    d_func()->init();
}

TConfirmEmailChangeReplyData::TConfirmEmailChangeReplyData(const TConfirmEmailChangeReplyData &other) :
    BBase(*new TConfirmEmailChangeReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TConfirmEmailChangeReplyData::~TConfirmEmailChangeReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmEmailChangeReplyData::setSuccess(bool success)
{
    d_func()->success = success;
}

bool TConfirmEmailChangeReplyData::success() const
{
    return d_func()->success;
}

/*============================== Public operators ==========================*/

TConfirmEmailChangeReplyData &TConfirmEmailChangeReplyData::operator =(const TConfirmEmailChangeReplyData &other)
{
    B_D(TConfirmEmailChangeReplyData);
    const TConfirmEmailChangeReplyDataPrivate *dd = other.d_func();
    d->success = dd->success;
    return *this;
}

bool TConfirmEmailChangeReplyData::operator ==(const TConfirmEmailChangeReplyData &other) const
{
    const B_D(TConfirmEmailChangeReplyData);
    const TConfirmEmailChangeReplyDataPrivate *dd = other.d_func();
    return d->success == dd->success;
}

bool TConfirmEmailChangeReplyData::operator !=(const TConfirmEmailChangeReplyData &other) const
{
    return !(*this == other);
}

TConfirmEmailChangeReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TConfirmEmailChangeReplyData &data)
{
    const TConfirmEmailChangeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("success", d->success);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TConfirmEmailChangeReplyData &data)
{
    TConfirmEmailChangeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->success = m.value("success").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TConfirmEmailChangeReplyData &/*data*/)
{
    //const TConfirmEmailChangeReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TConfirmEmailChangeReplyData(" << ")";
    return dbg.space();
}
