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

#include "trecoveraccountreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRecoverAccountReplyDataPrivate =============
============================================================================*/

class TRecoverAccountReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRecoverAccountReplyData)
public:
    bool success;
public:
    explicit TRecoverAccountReplyDataPrivate(TRecoverAccountReplyData *q);
    ~TRecoverAccountReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRecoverAccountReplyDataPrivate)
};

/*============================================================================
================================ TRecoverAccountReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TRecoverAccountReplyDataPrivate::TRecoverAccountReplyDataPrivate(TRecoverAccountReplyData *q) :
    BBasePrivate(q)
{
    //
}

TRecoverAccountReplyDataPrivate::~TRecoverAccountReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRecoverAccountReplyDataPrivate::init()
{
    success = false;
}

/*============================================================================
================================ TRecoverAccountReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoverAccountReplyData::TRecoverAccountReplyData() :
    BBase(*new TRecoverAccountReplyDataPrivate(this))
{
    d_func()->init();
}

TRecoverAccountReplyData::TRecoverAccountReplyData(const TRecoverAccountReplyData &other) :
    BBase(*new TRecoverAccountReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRecoverAccountReplyData::~TRecoverAccountReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TRecoverAccountReplyData::setSuccess(bool success)
{
    d_func()->success = success;
}

bool TRecoverAccountReplyData::success() const
{
    return d_func()->success;
}

/*============================== Public operators ==========================*/

TRecoverAccountReplyData &TRecoverAccountReplyData::operator =(const TRecoverAccountReplyData &other)
{
    B_D(TRecoverAccountReplyData);
    const TRecoverAccountReplyDataPrivate *dd = other.d_func();
    d->success = dd->success;
    return *this;
}

bool TRecoverAccountReplyData::operator ==(const TRecoverAccountReplyData &other) const
{
    const B_D(TRecoverAccountReplyData);
    const TRecoverAccountReplyDataPrivate *dd = other.d_func();
    return d->success == dd->success;
}

bool TRecoverAccountReplyData::operator !=(const TRecoverAccountReplyData &other) const
{
    return !(*this == other);
}

TRecoverAccountReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRecoverAccountReplyData &data)
{
    const TRecoverAccountReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("success", d->success);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRecoverAccountReplyData &data)
{
    TRecoverAccountReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->success = m.value("success").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRecoverAccountReplyData &/*data*/)
{
    //const TRecoverAccountReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TRecoverAccountReplyData(" << ")";
    return dbg.space();
}
