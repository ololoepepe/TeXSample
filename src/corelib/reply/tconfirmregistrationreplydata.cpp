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

#include "tconfirmregistrationreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TConfirmRegistrationReplyDataPrivate ========
============================================================================*/

class TConfirmRegistrationReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TConfirmRegistrationReplyData)
public:
    bool success;
public:
    explicit TConfirmRegistrationReplyDataPrivate(TConfirmRegistrationReplyData *q);
    ~TConfirmRegistrationReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TConfirmRegistrationReplyDataPrivate)
};

/*============================================================================
================================ TConfirmRegistrationReplyDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmRegistrationReplyDataPrivate::TConfirmRegistrationReplyDataPrivate(TConfirmRegistrationReplyData *q) :
    BBasePrivate(q)
{
    //
}

TConfirmRegistrationReplyDataPrivate::~TConfirmRegistrationReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmRegistrationReplyDataPrivate::init()
{
    success = false;
}

/*============================================================================
================================ TConfirmRegistrationReplyData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmRegistrationReplyData::TConfirmRegistrationReplyData() :
    BBase(*new TConfirmRegistrationReplyDataPrivate(this))
{
    d_func()->init();
}

TConfirmRegistrationReplyData::TConfirmRegistrationReplyData(const TConfirmRegistrationReplyData &other) :
    BBase(*new TConfirmRegistrationReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TConfirmRegistrationReplyData::~TConfirmRegistrationReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmRegistrationReplyData::setSuccess(bool success)
{
    d_func()->success = success;
}

bool TConfirmRegistrationReplyData::success() const
{
    return d_func()->success;
}

/*============================== Public operators ==========================*/

TConfirmRegistrationReplyData &TConfirmRegistrationReplyData::operator =(const TConfirmRegistrationReplyData &other)
{
    B_D(TConfirmRegistrationReplyData);
    const TConfirmRegistrationReplyDataPrivate *dd = other.d_func();
    d->success = dd->success;
    return *this;
}

bool TConfirmRegistrationReplyData::operator ==(const TConfirmRegistrationReplyData &other) const
{
    const B_D(TConfirmRegistrationReplyData);
    const TConfirmRegistrationReplyDataPrivate *dd = other.d_func();
    return d->success == dd->success;
}

bool TConfirmRegistrationReplyData::operator !=(const TConfirmRegistrationReplyData &other) const
{
    return !(*this == other);
}

TConfirmRegistrationReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TConfirmRegistrationReplyData &data)
{
    const TConfirmRegistrationReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("success", d->success);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TConfirmRegistrationReplyData &data)
{
    TConfirmRegistrationReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->success = m.value("success").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TConfirmRegistrationReplyData &/*data*/)
{
    //const TConfirmRegistrationReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TConfirmRegistrationReplyData(" << ")";
    return dbg.space();
}
