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

#include "teditselfreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSelfReplyDataPrivate ===================
============================================================================*/

class TEditSelfReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSelfReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TEditSelfReplyDataPrivate(TEditSelfReplyData *q);
    ~TEditSelfReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSelfReplyDataPrivate)
};

/*============================================================================
================================ TEditSelfReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfReplyDataPrivate::TEditSelfReplyDataPrivate(TEditSelfReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditSelfReplyDataPrivate::~TEditSelfReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSelfReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditSelfReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfReplyData::TEditSelfReplyData() :
    BBase(*new TEditSelfReplyDataPrivate(this))
{
    d_func()->init();
}

TEditSelfReplyData::TEditSelfReplyData(const TEditSelfReplyData &other) :
    BBase(*new TEditSelfReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSelfReplyData::~TEditSelfReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditSelfReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TEditSelfReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TEditSelfReplyData &TEditSelfReplyData::operator =(const TEditSelfReplyData &other)
{
    B_D(TEditSelfReplyData);
    const TEditSelfReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TEditSelfReplyData::operator ==(const TEditSelfReplyData &other) const
{
    const B_D(TEditSelfReplyData);
    const TEditSelfReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TEditSelfReplyData::operator !=(const TEditSelfReplyData &other) const
{
    return !(*this == other);
}

TEditSelfReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSelfReplyData &data)
{
    const TEditSelfReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSelfReplyData &data)
{
    TEditSelfReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSelfReplyData &/*data*/)
{
    //const TEditSelfReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSelfReplyData(" << ")";
    return dbg.space();
}
