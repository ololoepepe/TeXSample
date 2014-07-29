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

#include "tgetinviteinfolistreplydata.h"

#include "tidlist.h"
#include "tinviteinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetInviteInfoListReplyDataPrivate ==========
============================================================================*/

class TGetInviteInfoListReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetInviteInfoListReplyData)
public:
    TIdList deletedInvites;
    TInviteInfoList newInvites;
public:
    explicit TGetInviteInfoListReplyDataPrivate(TGetInviteInfoListReplyData *q);
    ~TGetInviteInfoListReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetInviteInfoListReplyDataPrivate)
};

/*============================================================================
================================ TGetInviteInfoListReplyDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TGetInviteInfoListReplyDataPrivate::TGetInviteInfoListReplyDataPrivate(TGetInviteInfoListReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetInviteInfoListReplyDataPrivate::~TGetInviteInfoListReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetInviteInfoListReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetInviteInfoListReplyData =================
============================================================================*/

/*============================== Public constructors =======================*/

TGetInviteInfoListReplyData::TGetInviteInfoListReplyData() :
    BBase(*new TGetInviteInfoListReplyDataPrivate(this))
{
    d_func()->init();
}

TGetInviteInfoListReplyData::TGetInviteInfoListReplyData(const TGetInviteInfoListReplyData &other) :
    BBase(*new TGetInviteInfoListReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetInviteInfoListReplyData::~TGetInviteInfoListReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TGetInviteInfoListReplyData::deletedInvites() const
{
    return d_func()->deletedInvites;
}

TInviteInfoList TGetInviteInfoListReplyData::newInvites() const
{
    return d_func()->newInvites;
}

void TGetInviteInfoListReplyData::setDeletedInvites(const TIdList &deletedInvites)
{
    B_D(TGetInviteInfoListReplyData);
    d->deletedInvites = deletedInvites;
    d->deletedInvites.removeAll(0);
    bRemoveDuplicates(d->deletedInvites);
}

void TGetInviteInfoListReplyData::setNewInvites(const TInviteInfoList &newInvites)
{
    d_func()->newInvites = newInvites;
}

/*============================== Public operators ==========================*/

TGetInviteInfoListReplyData &TGetInviteInfoListReplyData::operator =(const TGetInviteInfoListReplyData &other)
{
    B_D(TGetInviteInfoListReplyData);
    const TGetInviteInfoListReplyDataPrivate *dd = other.d_func();
    d->deletedInvites = dd->deletedInvites;
    d->newInvites = dd->newInvites;
    return *this;
}

bool TGetInviteInfoListReplyData::operator ==(const TGetInviteInfoListReplyData &other) const
{
    const B_D(TGetInviteInfoListReplyData);
    const TGetInviteInfoListReplyDataPrivate *dd = other.d_func();
    return d->deletedInvites == dd->deletedInvites && d->newInvites == dd->newInvites;
}

bool TGetInviteInfoListReplyData::operator !=(const TGetInviteInfoListReplyData &other) const
{
    return !(*this == other);
}

TGetInviteInfoListReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetInviteInfoListReplyData &data)
{
    const TGetInviteInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("deleted_invites", d->deletedInvites);
    m.insert("new_invites", d->newInvites);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetInviteInfoListReplyData &data)
{
    TGetInviteInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->deletedInvites = m.value("deleted_invites").value<TIdList>();
    d->newInvites = m.value("new_invites").value<TInviteInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetInviteInfoListReplyData &/*data*/)
{
    //const TGetInviteInfoListReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetInviteInfoListReplyData(" << ")";
    return dbg.space();
}
