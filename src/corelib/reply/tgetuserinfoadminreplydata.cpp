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

#include "tgetuserinfoadminreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoAdminReplyDataPrivate ===========
============================================================================*/

class TGetUserInfoAdminReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoAdminReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TGetUserInfoAdminReplyDataPrivate(TGetUserInfoAdminReplyData *q);
    ~TGetUserInfoAdminReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoAdminReplyDataPrivate)
};

/*============================================================================
================================ TGetUserInfoAdminReplyDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoAdminReplyDataPrivate::TGetUserInfoAdminReplyDataPrivate(TGetUserInfoAdminReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoAdminReplyDataPrivate::~TGetUserInfoAdminReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoAdminReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoAdminReplyData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoAdminReplyData::TGetUserInfoAdminReplyData() :
    BBase(*new TGetUserInfoAdminReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoAdminReplyData::TGetUserInfoAdminReplyData(const TGetUserInfoAdminReplyData &other) :
    BBase(*new TGetUserInfoAdminReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoAdminReplyData::~TGetUserInfoAdminReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoAdminReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TGetUserInfoAdminReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TGetUserInfoAdminReplyData &TGetUserInfoAdminReplyData::operator =(const TGetUserInfoAdminReplyData &other)
{
    B_D(TGetUserInfoAdminReplyData);
    const TGetUserInfoAdminReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TGetUserInfoAdminReplyData::operator ==(const TGetUserInfoAdminReplyData &other) const
{
    const B_D(TGetUserInfoAdminReplyData);
    const TGetUserInfoAdminReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TGetUserInfoAdminReplyData::operator !=(const TGetUserInfoAdminReplyData &other) const
{
    return !(*this == other);
}

TGetUserInfoAdminReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoAdminReplyData &data)
{
    const TGetUserInfoAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoAdminReplyData &data)
{
    TGetUserInfoAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoAdminReplyData &/*data*/)
{
    //const TGetUserInfoAdminReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoAdminReplyData(" << ")";
    return dbg.space();
}
