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

#include "tdeleteuserreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteUserReplyDataPrivate =================
============================================================================*/

class TDeleteUserReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteUserReplyData)
public:
    quint64 userId;
public:
    explicit TDeleteUserReplyDataPrivate(TDeleteUserReplyData *q);
    ~TDeleteUserReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteUserReplyDataPrivate)
};

/*============================================================================
================================ TDeleteUserReplyDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserReplyDataPrivate::TDeleteUserReplyDataPrivate(TDeleteUserReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteUserReplyDataPrivate::~TDeleteUserReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserReplyDataPrivate::init()
{
    userId = 0;
}

/*============================================================================
================================ TDeleteUserReplyData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserReplyData::TDeleteUserReplyData() :
    BBase(*new TDeleteUserReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteUserReplyData::TDeleteUserReplyData(const TDeleteUserReplyData &other) :
    BBase(*new TDeleteUserReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteUserReplyData::~TDeleteUserReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserReplyData::setUserId(quint64 userId)
{
    d_func()->userId = userId;
}

quint64 TDeleteUserReplyData::userId() const
{
    return d_func()->userId;
}

/*============================== Public operators ==========================*/

TDeleteUserReplyData &TDeleteUserReplyData::operator =(const TDeleteUserReplyData &other)
{
    B_D(TDeleteUserReplyData);
    const TDeleteUserReplyDataPrivate *dd = other.d_func();
    d->userId = dd->userId;
    return *this;
}

bool TDeleteUserReplyData::operator ==(const TDeleteUserReplyData &other) const
{
    const B_D(TDeleteUserReplyData);
    const TDeleteUserReplyDataPrivate *dd = other.d_func();
    return d->userId == dd->userId;
}

bool TDeleteUserReplyData::operator !=(const TDeleteUserReplyData &other) const
{
    return !(*this == other);
}

TDeleteUserReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteUserReplyData &data)
{
    const TDeleteUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_id", d->userId);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteUserReplyData &data)
{
    TDeleteUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userId = m.value("user_id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteUserReplyData &/*data*/)
{
    //const TDeleteUserReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteUserReplyData(" << ")";
    return dbg.space();
}
