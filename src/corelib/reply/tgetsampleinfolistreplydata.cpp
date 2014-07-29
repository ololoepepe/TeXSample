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

#include "tgetsampleinfolistreplydata.h"

#include "tidlist.h"
#include "tsampleinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleInfoListReplyDataPrivate ==========
============================================================================*/

class TGetSampleInfoListReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleInfoListReplyData)
public:
    TIdList deletedSamples;
    TSampleInfoList newSamples;
public:
    explicit TGetSampleInfoListReplyDataPrivate(TGetSampleInfoListReplyData *q);
    ~TGetSampleInfoListReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleInfoListReplyDataPrivate)
};

/*============================================================================
================================ TGetSampleInfoListReplyDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListReplyDataPrivate::TGetSampleInfoListReplyDataPrivate(TGetSampleInfoListReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleInfoListReplyDataPrivate::~TGetSampleInfoListReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleInfoListReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSampleInfoListReplyData =================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListReplyData::TGetSampleInfoListReplyData() :
    BBase(*new TGetSampleInfoListReplyDataPrivate(this))
{
    d_func()->init();
}

TGetSampleInfoListReplyData::TGetSampleInfoListReplyData(const TGetSampleInfoListReplyData &other) :
    BBase(*new TGetSampleInfoListReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleInfoListReplyData::~TGetSampleInfoListReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TGetSampleInfoListReplyData::deletedSamples() const
{
    return d_func()->deletedSamples;
}

TSampleInfoList TGetSampleInfoListReplyData::newSamples() const
{
    return d_func()->newSamples;
}

void TGetSampleInfoListReplyData::setDeletedSamples(const TIdList &deletedSamples)
{
    B_D(TGetSampleInfoListReplyData);
    d->deletedSamples = deletedSamples;
    d->deletedSamples.removeAll(0);
    bRemoveDuplicates(d->deletedSamples);
}

void TGetSampleInfoListReplyData::setNewSamples(const TSampleInfoList &newSamples)
{
    d_func()->newSamples = newSamples;
}

/*============================== Public operators ==========================*/

TGetSampleInfoListReplyData &TGetSampleInfoListReplyData::operator =(const TGetSampleInfoListReplyData &other)
{
    B_D(TGetSampleInfoListReplyData);
    const TGetSampleInfoListReplyDataPrivate *dd = other.d_func();
    d->deletedSamples = dd->deletedSamples;
    d->newSamples = dd->newSamples;
    return *this;
}

bool TGetSampleInfoListReplyData::operator ==(const TGetSampleInfoListReplyData &other) const
{
    const B_D(TGetSampleInfoListReplyData);
    const TGetSampleInfoListReplyDataPrivate *dd = other.d_func();
    return d->deletedSamples == dd->deletedSamples && d->newSamples == dd->newSamples;
}

bool TGetSampleInfoListReplyData::operator !=(const TGetSampleInfoListReplyData &other) const
{
    return !(*this == other);
}

TGetSampleInfoListReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListReplyData &data)
{
    const TGetSampleInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("deleted_samples", d->deletedSamples);
    m.insert("new_samples", d->newSamples);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListReplyData &data)
{
    TGetSampleInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->deletedSamples = m.value("deleted_samples").value<TIdList>();
    d->newSamples = m.value("new_samples").value<TSampleInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleInfoListReplyData &/*data*/)
{
    //const TGetSampleInfoListReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleInfoListReplyData(" << ")";
    return dbg.space();
}
