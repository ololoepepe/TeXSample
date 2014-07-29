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

#include "tregisterreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRegisterReplyDataPrivate ===================
============================================================================*/

class TRegisterReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRegisterReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TRegisterReplyDataPrivate(TRegisterReplyData *q);
    ~TRegisterReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRegisterReplyDataPrivate)
};

/*============================================================================
================================ TRegisterReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TRegisterReplyDataPrivate::TRegisterReplyDataPrivate(TRegisterReplyData *q) :
    BBasePrivate(q)
{
    //
}

TRegisterReplyDataPrivate::~TRegisterReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRegisterReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRegisterReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TRegisterReplyData::TRegisterReplyData() :
    BBase(*new TRegisterReplyDataPrivate(this))
{
    d_func()->init();
}

TRegisterReplyData::TRegisterReplyData(const TRegisterReplyData &other) :
    BBase(*new TRegisterReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRegisterReplyData::~TRegisterReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TRegisterReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TRegisterReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TRegisterReplyData &TRegisterReplyData::operator =(const TRegisterReplyData &other)
{
    B_D(TRegisterReplyData);
    const TRegisterReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TRegisterReplyData::operator ==(const TRegisterReplyData &other) const
{
    const B_D(TRegisterReplyData);
    const TRegisterReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TRegisterReplyData::operator !=(const TRegisterReplyData &other) const
{
    return !(*this == other);
}

TRegisterReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRegisterReplyData &data)
{
    const TRegisterReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRegisterReplyData &data)
{
    TRegisterReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRegisterReplyData &/*data*/)
{
    //const TRegisterReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TRegisterReplyData(" << ")";
    return dbg.space();
}
