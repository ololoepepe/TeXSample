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

#include "tedituserreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditUserReplyDataPrivate ===================
============================================================================*/

class TEditUserReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditUserReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TEditUserReplyDataPrivate(TEditUserReplyData *q);
    ~TEditUserReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditUserReplyDataPrivate)
};

/*============================================================================
================================ TEditUserReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TEditUserReplyDataPrivate::TEditUserReplyDataPrivate(TEditUserReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditUserReplyDataPrivate::~TEditUserReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditUserReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditUserReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditUserReplyData::TEditUserReplyData() :
    BBase(*new TEditUserReplyDataPrivate(this))
{
    d_func()->init();
}

TEditUserReplyData::TEditUserReplyData(const TEditUserReplyData &other) :
    BBase(*new TEditUserReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditUserReplyData::~TEditUserReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditUserReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TEditUserReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TEditUserReplyData &TEditUserReplyData::operator =(const TEditUserReplyData &other)
{
    B_D(TEditUserReplyData);
    const TEditUserReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TEditUserReplyData::operator ==(const TEditUserReplyData &other) const
{
    const B_D(TEditUserReplyData);
    const TEditUserReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TEditUserReplyData::operator !=(const TEditUserReplyData &other) const
{
    return !(*this == other);
}

TEditUserReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditUserReplyData &data)
{
    const TEditUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditUserReplyData &data)
{
    TEditUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditUserReplyData &/*data*/)
{
    //const TEditUserReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditUserReplyData(" << ")";
    return dbg.space();
}
