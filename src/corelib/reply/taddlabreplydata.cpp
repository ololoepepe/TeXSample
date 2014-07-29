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

#include "taddlabreplydata.h"

#include "tlabinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddLabReplyDataPrivate =====================
============================================================================*/

class TAddLabReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddLabReplyData)
public:
    TLabInfo labInfo;
public:
    explicit TAddLabReplyDataPrivate(TAddLabReplyData *q);
    ~TAddLabReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddLabReplyDataPrivate)
};

/*============================================================================
================================ TAddLabReplyDataPrivate =====================
============================================================================*/

/*============================== Public constructors =======================*/

TAddLabReplyDataPrivate::TAddLabReplyDataPrivate(TAddLabReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAddLabReplyDataPrivate::~TAddLabReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddLabReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddLabReplyData ============================
============================================================================*/

/*============================== Public constructors =======================*/

TAddLabReplyData::TAddLabReplyData() :
    BBase(*new TAddLabReplyDataPrivate(this))
{
    d_func()->init();
}

TAddLabReplyData::TAddLabReplyData(const TAddLabReplyData &other) :
    BBase(*new TAddLabReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddLabReplyData::~TAddLabReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAddLabReplyData::setLabInfo(const TLabInfo &info)
{
    d_func()->labInfo = info;
}

TLabInfo TAddLabReplyData::labInfo() const
{
    return d_func()->labInfo;
}

/*============================== Public operators ==========================*/

TAddLabReplyData &TAddLabReplyData::operator =(const TAddLabReplyData &other)
{
    B_D(TAddLabReplyData);
    const TAddLabReplyDataPrivate *dd = other.d_func();
    d->labInfo = dd->labInfo;
    return *this;
}

bool TAddLabReplyData::operator ==(const TAddLabReplyData &other) const
{
    const B_D(TAddLabReplyData);
    const TAddLabReplyDataPrivate *dd = other.d_func();
    return d->labInfo == dd->labInfo;
}

bool TAddLabReplyData::operator !=(const TAddLabReplyData &other) const
{
    return !(*this == other);
}

TAddLabReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddLabReplyData &data)
{
    const TAddLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("lab_info", d->labInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddLabReplyData &data)
{
    TAddLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->labInfo = m.value("lab_info").value<TLabInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddLabReplyData &/*data*/)
{
    //const TAddLabReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddLabReplyData(" << ")";
    return dbg.space();
}
