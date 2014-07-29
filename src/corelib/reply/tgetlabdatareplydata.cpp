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

#include "tgetlabdatareplydata.h"

#include "tlabdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLabDataReplyDataPrivate =================
============================================================================*/

class TGetLabDataReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLabDataReplyData)
public:
    TLabData data;
public:
    explicit TGetLabDataReplyDataPrivate(TGetLabDataReplyData *q);
    ~TGetLabDataReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLabDataReplyDataPrivate)
};

/*============================================================================
================================ TGetLabDataReplyDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabDataReplyDataPrivate::TGetLabDataReplyDataPrivate(TGetLabDataReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetLabDataReplyDataPrivate::~TGetLabDataReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabDataReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLabDataReplyData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabDataReplyData::TGetLabDataReplyData() :
    BBase(*new TGetLabDataReplyDataPrivate(this))
{
    d_func()->init();
}

TGetLabDataReplyData::TGetLabDataReplyData(const TGetLabDataReplyData &other) :
    BBase(*new TGetLabDataReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLabDataReplyData::~TGetLabDataReplyData()
{
    //
}

/*============================== Public methods ============================*/

TLabData &TGetLabDataReplyData::data()
{
    return d_func()->data;
}

const TLabData &TGetLabDataReplyData::data() const
{
    return d_func()->data;
}

void TGetLabDataReplyData::setData(const TLabData &data)
{
    d_func()->data = data;
}

/*============================== Public operators ==========================*/

TGetLabDataReplyData &TGetLabDataReplyData::operator =(const TGetLabDataReplyData &other)
{
    B_D(TGetLabDataReplyData);
    const TGetLabDataReplyDataPrivate *dd = other.d_func();
    d->data = dd->data;
    return *this;
}

bool TGetLabDataReplyData::operator ==(const TGetLabDataReplyData &other) const
{
    const B_D(TGetLabDataReplyData);
    const TGetLabDataReplyDataPrivate *dd = other.d_func();
    return d->data == dd->data;
}

bool TGetLabDataReplyData::operator !=(const TGetLabDataReplyData &other) const
{
    return !(*this == other);
}

TGetLabDataReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLabDataReplyData &data)
{
    const TGetLabDataReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("data", d->data);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLabDataReplyData &data)
{
    TGetLabDataReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->data = m.value("data").value<TLabData>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLabDataReplyData &/*data*/)
{
    //const TGetLabDataReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLabDataReplyData(" << ")";
    return dbg.space();
}
