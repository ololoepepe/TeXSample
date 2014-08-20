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

#include "tgetuserconnectioninfolistreplydata.h"

#include "tuserconnectioninfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
=============================== TGetUserConnectionInfoListReplyDataPrivate ===
============================================================================*/

class TGetUserConnectionInfoListReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserConnectionInfoListReplyData)
public:
    TUserConnectionInfoList connectionInfoList;
public:
    explicit TGetUserConnectionInfoListReplyDataPrivate(TGetUserConnectionInfoListReplyData *q);
    ~TGetUserConnectionInfoListReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserConnectionInfoListReplyDataPrivate)
};


/*============================================================================
=============================== TGetUserConnectionInfoListReplyDataPrivate ===
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserConnectionInfoListReplyDataPrivate::TGetUserConnectionInfoListReplyDataPrivate(
        TGetUserConnectionInfoListReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserConnectionInfoListReplyDataPrivate::~TGetUserConnectionInfoListReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserConnectionInfoListReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserConnectionInfoListReplyData =========
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserConnectionInfoListReplyData::TGetUserConnectionInfoListReplyData() :
    BBase(*new TGetUserConnectionInfoListReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserConnectionInfoListReplyData::TGetUserConnectionInfoListReplyData(
        const TGetUserConnectionInfoListReplyData &other) :
    BBase(*new TGetUserConnectionInfoListReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserConnectionInfoListReplyData::~TGetUserConnectionInfoListReplyData()
{
    //
}

/*============================== Public methods ============================*/

TUserConnectionInfoList TGetUserConnectionInfoListReplyData::connectionInfoList() const
{
    return d_func()->connectionInfoList;
}

void TGetUserConnectionInfoListReplyData::setConnectionInfoList(const TUserConnectionInfoList &list)
{
    d_func()->connectionInfoList = list;
}

/*============================== Public operators ==========================*/

TGetUserConnectionInfoListReplyData &TGetUserConnectionInfoListReplyData::operator =(
        const TGetUserConnectionInfoListReplyData &other)
{
    B_D(TGetUserConnectionInfoListReplyData);
    const TGetUserConnectionInfoListReplyDataPrivate *dd = other.d_func();
    d->connectionInfoList = dd->connectionInfoList;
    return *this;
}

bool TGetUserConnectionInfoListReplyData::operator ==(const TGetUserConnectionInfoListReplyData &other) const
{
    const B_D(TGetUserConnectionInfoListReplyData);
    const TGetUserConnectionInfoListReplyDataPrivate *dd = other.d_func();
    return d->connectionInfoList == dd->connectionInfoList;
}

bool TGetUserConnectionInfoListReplyData::operator !=(const TGetUserConnectionInfoListReplyData &other) const
{
    return !(*this == other);
}

TGetUserConnectionInfoListReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserConnectionInfoListReplyData &data)
{
    const TGetUserConnectionInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("connection_info_list", d->connectionInfoList);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserConnectionInfoListReplyData &data)
{
    TGetUserConnectionInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->connectionInfoList = m.value("connection_info_list").value<TUserConnectionInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserConnectionInfoListReplyData &/*data*/)
{
    //const TGetUserConnectionInfoListReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserConnectionInfoListReplyData(" << ")";
    return dbg.space();
}
