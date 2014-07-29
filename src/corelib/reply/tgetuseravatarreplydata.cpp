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

#include "tgetuseravatarreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserAvatarReplyDataPrivate ==============
============================================================================*/

class TGetUserAvatarReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserAvatarReplyData)
public:
    QImage avatar;
public:
    explicit TGetUserAvatarReplyDataPrivate(TGetUserAvatarReplyData *q);
    ~TGetUserAvatarReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserAvatarReplyDataPrivate)
};

/*============================================================================
================================ TGetUserAvatarReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarReplyDataPrivate::TGetUserAvatarReplyDataPrivate(TGetUserAvatarReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserAvatarReplyDataPrivate::~TGetUserAvatarReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserAvatarReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserAvatarReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarReplyData::TGetUserAvatarReplyData() :
    BBase(*new TGetUserAvatarReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserAvatarReplyData::TGetUserAvatarReplyData(const TGetUserAvatarReplyData &other) :
    BBase(*new TGetUserAvatarReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserAvatarReplyData::~TGetUserAvatarReplyData()
{
    //
}

/*============================== Public methods ============================*/

QImage TGetUserAvatarReplyData::avatar() const
{
    return d_func()->avatar;
}

void TGetUserAvatarReplyData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = avatar;
}

/*============================== Public operators ==========================*/

TGetUserAvatarReplyData &TGetUserAvatarReplyData::operator =(const TGetUserAvatarReplyData &other)
{
    B_D(TGetUserAvatarReplyData);
    const TGetUserAvatarReplyDataPrivate *dd = other.d_func();
    d->avatar = dd->avatar;
    return *this;
}

bool TGetUserAvatarReplyData::operator ==(const TGetUserAvatarReplyData &other) const
{
    const B_D(TGetUserAvatarReplyData);
    const TGetUserAvatarReplyDataPrivate *dd = other.d_func();
    return d->avatar == dd->avatar;
}

bool TGetUserAvatarReplyData::operator !=(const TGetUserAvatarReplyData &other) const
{
    return !(*this == other);
}

TGetUserAvatarReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarReplyData &data)
{
    const TGetUserAvatarReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("avatar", d->avatar);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserAvatarReplyData &data)
{
    TGetUserAvatarReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->avatar = m.value("avatar").value<QImage>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserAvatarReplyData &/*data*/)
{
    //const TGetUserAvatarReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserAvatarReplyData(" << ")";
    return dbg.space();
}
