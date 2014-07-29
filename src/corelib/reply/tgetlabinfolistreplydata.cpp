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

#include "tgetlabinfolistreplydata.h"

#include "tidlist.h"
#include "tlabinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLabInfoListReplyDataPrivate =============
============================================================================*/

class TGetLabInfoListReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLabInfoListReplyData)
public:
    TIdList deletedLabs;
    TLabInfoList newLabs;
public:
    explicit TGetLabInfoListReplyDataPrivate(TGetLabInfoListReplyData *q);
    ~TGetLabInfoListReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLabInfoListReplyDataPrivate)
};

/*============================================================================
================================ TGetLabInfoListReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabInfoListReplyDataPrivate::TGetLabInfoListReplyDataPrivate(TGetLabInfoListReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetLabInfoListReplyDataPrivate::~TGetLabInfoListReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabInfoListReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLabInfoListReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabInfoListReplyData::TGetLabInfoListReplyData() :
    BBase(*new TGetLabInfoListReplyDataPrivate(this))
{
    d_func()->init();
}

TGetLabInfoListReplyData::TGetLabInfoListReplyData(const TGetLabInfoListReplyData &other) :
    BBase(*new TGetLabInfoListReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLabInfoListReplyData::~TGetLabInfoListReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TGetLabInfoListReplyData::deletedLabs() const
{
    return d_func()->deletedLabs;
}

TLabInfoList TGetLabInfoListReplyData::newLabs() const
{
    return d_func()->newLabs;
}

void TGetLabInfoListReplyData::setDeletedLabs(const TIdList &deletedLabs)
{
    B_D(TGetLabInfoListReplyData);
    d->deletedLabs = deletedLabs;
    d->deletedLabs.removeAll(0);
    bRemoveDuplicates(d->deletedLabs);
}

void TGetLabInfoListReplyData::setNewLabs(const TLabInfoList &newLabs)
{
    d_func()->newLabs = newLabs;
}

/*============================== Public operators ==========================*/

TGetLabInfoListReplyData &TGetLabInfoListReplyData::operator =(const TGetLabInfoListReplyData &other)
{
    B_D(TGetLabInfoListReplyData);
    const TGetLabInfoListReplyDataPrivate *dd = other.d_func();
    d->deletedLabs = dd->deletedLabs;
    d->newLabs = dd->newLabs;
    return *this;
}

bool TGetLabInfoListReplyData::operator ==(const TGetLabInfoListReplyData &other) const
{
    const B_D(TGetLabInfoListReplyData);
    const TGetLabInfoListReplyDataPrivate *dd = other.d_func();
    return d->deletedLabs == dd->deletedLabs && d->newLabs == dd->newLabs;
}

bool TGetLabInfoListReplyData::operator !=(const TGetLabInfoListReplyData &other) const
{
    return !(*this == other);
}

TGetLabInfoListReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLabInfoListReplyData &data)
{
    const TGetLabInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("deleted_labs", d->deletedLabs);
    m.insert("new_labs", d->newLabs);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLabInfoListReplyData &data)
{
    TGetLabInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->deletedLabs = m.value("deleted_labs").value<TIdList>();
    d->newLabs = m.value("new_labs").value<TLabInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLabInfoListReplyData &/*data*/)
{
    //const TGetLabInfoListReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLabInfoListReplyData(" << ")";
    return dbg.space();
}
