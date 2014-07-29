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

#include "teditlabreplydata.h"

#include "tlabinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditLabReplyDataPrivate ====================
============================================================================*/

class TEditLabReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditLabReplyData)
public:
    TLabInfo labInfo;
public:
    explicit TEditLabReplyDataPrivate(TEditLabReplyData *q);
    ~TEditLabReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditLabReplyDataPrivate)
};

/*============================================================================
================================ TEditLabReplyDataPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TEditLabReplyDataPrivate::TEditLabReplyDataPrivate(TEditLabReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditLabReplyDataPrivate::~TEditLabReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditLabReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditLabReplyData ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditLabReplyData::TEditLabReplyData() :
    BBase(*new TEditLabReplyDataPrivate(this))
{
    d_func()->init();
}

TEditLabReplyData::TEditLabReplyData(const TEditLabReplyData &other) :
    BBase(*new TEditLabReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditLabReplyData::~TEditLabReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditLabReplyData::setLabInfo(const TLabInfo &info)
{
    d_func()->labInfo = info;
}

TLabInfo TEditLabReplyData::labInfo() const
{
    return d_func()->labInfo;
}

/*============================== Public operators ==========================*/

TEditLabReplyData &TEditLabReplyData::operator =(const TEditLabReplyData &other)
{
    B_D(TEditLabReplyData);
    const TEditLabReplyDataPrivate *dd = other.d_func();
    d->labInfo = dd->labInfo;
    return *this;
}

bool TEditLabReplyData::operator ==(const TEditLabReplyData &other) const
{
    const B_D(TEditLabReplyData);
    const TEditLabReplyDataPrivate *dd = other.d_func();
    return d->labInfo == dd->labInfo;
}

bool TEditLabReplyData::operator !=(const TEditLabReplyData &other) const
{
    return !(*this == other);
}

TEditLabReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditLabReplyData &data)
{
    const TEditLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("lab_info", d->labInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditLabReplyData &data)
{
    TEditLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->labInfo = m.value("lab_info").value<TLabInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditLabReplyData &/*data*/)
{
    //const TEditLabReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditLabReplyData(" << ")";
    return dbg.space();
}
