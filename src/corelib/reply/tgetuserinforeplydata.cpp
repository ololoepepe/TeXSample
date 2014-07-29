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

#include "tgetuserinforeplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoReplyDataPrivate ================
============================================================================*/

class TGetUserInfoReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TGetUserInfoReplyDataPrivate(TGetUserInfoReplyData *q);
    ~TGetUserInfoReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoReplyDataPrivate)
};

/*============================================================================
================================ TGetUserInfoReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoReplyDataPrivate::TGetUserInfoReplyDataPrivate(TGetUserInfoReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoReplyDataPrivate::~TGetUserInfoReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoReplyData::TGetUserInfoReplyData() :
    BBase(*new TGetUserInfoReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoReplyData::TGetUserInfoReplyData(const TGetUserInfoReplyData &other) :
    BBase(*new TGetUserInfoReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoReplyData::~TGetUserInfoReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TGetUserInfoReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TGetUserInfoReplyData &TGetUserInfoReplyData::operator =(const TGetUserInfoReplyData &other)
{
    B_D(TGetUserInfoReplyData);
    const TGetUserInfoReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TGetUserInfoReplyData::operator ==(const TGetUserInfoReplyData &other) const
{
    const B_D(TGetUserInfoReplyData);
    const TGetUserInfoReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TGetUserInfoReplyData::operator !=(const TGetUserInfoReplyData &other) const
{
    return !(*this == other);
}

TGetUserInfoReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoReplyData &data)
{
    const TGetUserInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoReplyData &data)
{
    TGetUserInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoReplyData &/*data*/)
{
    //const TGetUserInfoReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoReplyData(" << ")";
    return dbg.space();
}
