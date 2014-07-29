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

#include "tadduserreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddUserReplyDataPrivate ====================
============================================================================*/

class TAddUserReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddUserReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TAddUserReplyDataPrivate(TAddUserReplyData *q);
    ~TAddUserReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddUserReplyDataPrivate)
};

/*============================================================================
================================ TAddUserReplyDataPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TAddUserReplyDataPrivate::TAddUserReplyDataPrivate(TAddUserReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAddUserReplyDataPrivate::~TAddUserReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddUserReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddUserReplyData ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddUserReplyData::TAddUserReplyData() :
    BBase(*new TAddUserReplyDataPrivate(this))
{
    d_func()->init();
}

TAddUserReplyData::TAddUserReplyData(const TAddUserReplyData &other) :
    BBase(*new TAddUserReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddUserReplyData::~TAddUserReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAddUserReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TAddUserReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TAddUserReplyData &TAddUserReplyData::operator =(const TAddUserReplyData &other)
{
    B_D(TAddUserReplyData);
    const TAddUserReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TAddUserReplyData::operator ==(const TAddUserReplyData &other) const
{
    const B_D(TAddUserReplyData);
    const TAddUserReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TAddUserReplyData::operator !=(const TAddUserReplyData &other) const
{
    return !(*this == other);
}

TAddUserReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddUserReplyData &data)
{
    const TAddUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddUserReplyData &data)
{
    TAddUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddUserReplyData &/*data*/)
{
    //const TAddUserReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddUserReplyData(" << ")";
    return dbg.space();
}
