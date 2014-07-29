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

#include "tgetuserinfolistadminreplydata.h"

#include "tidlist.h"
#include "tuserinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoListAdminReplyDataPrivate =======
============================================================================*/

class TGetUserInfoListAdminReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoListAdminReplyData)
public:
    TIdList deletedUsers;
    TUserInfoList newUsers;
public:
    explicit TGetUserInfoListAdminReplyDataPrivate(TGetUserInfoListAdminReplyData *q);
    ~TGetUserInfoListAdminReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoListAdminReplyDataPrivate)
};

/*============================================================================
================================ TGetUserInfoListAdminReplyDataPrivate =======
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoListAdminReplyDataPrivate::TGetUserInfoListAdminReplyDataPrivate(TGetUserInfoListAdminReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoListAdminReplyDataPrivate::~TGetUserInfoListAdminReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoListAdminReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoListAdminReplyData ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoListAdminReplyData::TGetUserInfoListAdminReplyData() :
    BBase(*new TGetUserInfoListAdminReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoListAdminReplyData::TGetUserInfoListAdminReplyData(const TGetUserInfoListAdminReplyData &other) :
    BBase(*new TGetUserInfoListAdminReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoListAdminReplyData::~TGetUserInfoListAdminReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TGetUserInfoListAdminReplyData::deletedUsers() const
{
    return d_func()->deletedUsers;
}

TUserInfoList TGetUserInfoListAdminReplyData::newUsers() const
{
    return d_func()->newUsers;
}

void TGetUserInfoListAdminReplyData::setDeletedUsers(const TIdList &deletedUsers)
{
    B_D(TGetUserInfoListAdminReplyData);
    d->deletedUsers = deletedUsers;
    d->deletedUsers.removeAll(0);
    bRemoveDuplicates(d->deletedUsers);
}

void TGetUserInfoListAdminReplyData::setNewUsers(const TUserInfoList &newUsers)
{
    d_func()->newUsers = newUsers;
}

/*============================== Public operators ==========================*/

TGetUserInfoListAdminReplyData &TGetUserInfoListAdminReplyData::operator =(const TGetUserInfoListAdminReplyData &other)
{
    B_D(TGetUserInfoListAdminReplyData);
    const TGetUserInfoListAdminReplyDataPrivate *dd = other.d_func();
    d->deletedUsers = dd->deletedUsers;
    d->newUsers = dd->newUsers;
    return *this;
}

bool TGetUserInfoListAdminReplyData::operator ==(const TGetUserInfoListAdminReplyData &other) const
{
    const B_D(TGetUserInfoListAdminReplyData);
    const TGetUserInfoListAdminReplyDataPrivate *dd = other.d_func();
    return d->deletedUsers == dd->deletedUsers && d->newUsers == dd->newUsers;
}

bool TGetUserInfoListAdminReplyData::operator !=(const TGetUserInfoListAdminReplyData &other) const
{
    return !(*this == other);
}

TGetUserInfoListAdminReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminReplyData &data)
{
    const TGetUserInfoListAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("deleted_users", d->deletedUsers);
    m.insert("new_users", d->newUsers);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminReplyData &data)
{
    TGetUserInfoListAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->deletedUsers = m.value("deleted_users").value<TIdList>();
    d->newUsers = m.value("new_users").value<TUserInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminReplyData &/*data*/)
{
    //const TGetUserInfoListAdminReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoListAdminReplyData(" << ")";
    return dbg.space();
}
