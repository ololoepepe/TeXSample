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

#include "taddgroupreplydata.h"

#include "tgroupinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddGroupReplyDataPrivate ===================
============================================================================*/

class TAddGroupReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddGroupReplyData)
public:
    TGroupInfo groupInfo;
public:
    explicit TAddGroupReplyDataPrivate(TAddGroupReplyData *q);
    ~TAddGroupReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddGroupReplyDataPrivate)
};

/*============================================================================
================================ TAddGroupReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TAddGroupReplyDataPrivate::TAddGroupReplyDataPrivate(TAddGroupReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAddGroupReplyDataPrivate::~TAddGroupReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddGroupReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddGroupReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddGroupReplyData::TAddGroupReplyData() :
    BBase(*new TAddGroupReplyDataPrivate(this))
{
    d_func()->init();
}

TAddGroupReplyData::TAddGroupReplyData(const TAddGroupReplyData &other) :
    BBase(*new TAddGroupReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddGroupReplyData::~TAddGroupReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAddGroupReplyData::setGroupInfo(const TGroupInfo &info)
{
    d_func()->groupInfo = info;
}

TGroupInfo TAddGroupReplyData::groupInfo() const
{
    return d_func()->groupInfo;
}

/*============================== Public operators ==========================*/

TAddGroupReplyData &TAddGroupReplyData::operator =(const TAddGroupReplyData &other)
{
    B_D(TAddGroupReplyData);
    const TAddGroupReplyDataPrivate *dd = other.d_func();
    d->groupInfo = dd->groupInfo;
    return *this;
}

bool TAddGroupReplyData::operator ==(const TAddGroupReplyData &other) const
{
    const B_D(TAddGroupReplyData);
    const TAddGroupReplyDataPrivate *dd = other.d_func();
    return d->groupInfo == dd->groupInfo;
}

bool TAddGroupReplyData::operator !=(const TAddGroupReplyData &other) const
{
    return !(*this == other);
}

TAddGroupReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddGroupReplyData &data)
{
    const TAddGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("group_info", d->groupInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddGroupReplyData &data)
{
    TAddGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->groupInfo = m.value("group_info").value<TGroupInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddGroupReplyData &/*data*/)
{
    //const TAddGroupReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddGroupReplyData(" << ")";
    return dbg.space();
}
