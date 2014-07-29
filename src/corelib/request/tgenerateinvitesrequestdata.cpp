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

#include "tgenerateinvitesrequestdata.h"

#include "taccesslevel.h"
#include "tidlist.h"
#include "tservicelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGenerateInvitesRequestDataPrivate ==========
============================================================================*/

class TGenerateInvitesRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGenerateInvitesRequestData)
public:
    TAccessLevel accessLevel;
    quint16 count;
    QDateTime expirationDateTime;
    TIdList groups;
    TServiceList services;
public:
    explicit TGenerateInvitesRequestDataPrivate(TGenerateInvitesRequestData *q);
    ~TGenerateInvitesRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGenerateInvitesRequestDataPrivate)
};

/*============================================================================
================================ TGenerateInvitesRequestDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TGenerateInvitesRequestDataPrivate::TGenerateInvitesRequestDataPrivate(TGenerateInvitesRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGenerateInvitesRequestDataPrivate::~TGenerateInvitesRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGenerateInvitesRequestDataPrivate::init()
{
    count = 0;
    expirationDateTime.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TGenerateInvitesRequestData =================
============================================================================*/

/*============================== Public constructors =======================*/

TGenerateInvitesRequestData::TGenerateInvitesRequestData() :
    BBase(*new TGenerateInvitesRequestDataPrivate(this))
{
    d_func()->init();
}

TGenerateInvitesRequestData::TGenerateInvitesRequestData(const TGenerateInvitesRequestData &other) :
    BBase(*new TGenerateInvitesRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGenerateInvitesRequestData::~TGenerateInvitesRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAccessLevel TGenerateInvitesRequestData::accessLevel() const
{
    return d_func()->accessLevel;
}

void TGenerateInvitesRequestData::clear()
{
    B_D(TGenerateInvitesRequestData);
    d->accessLevel = TAccessLevel();
    d->count = 0;
    d->expirationDateTime = QDateTime().toUTC();
    d->groups.clear();
    d->services.clear();
}

quint16 TGenerateInvitesRequestData::count() const
{
    return d_func()->count;
}

QDateTime TGenerateInvitesRequestData::expirationDateTime() const
{
    return d_func()->expirationDateTime;
}

TIdList TGenerateInvitesRequestData::groups() const
{
    return d_func()->groups;
}

bool TGenerateInvitesRequestData::isValid() const
{
    const B_D(TGenerateInvitesRequestData);
    return d->accessLevel.isValid() && d->count && d->expirationDateTime.isValid();
}

TServiceList TGenerateInvitesRequestData::services() const
{
    return d_func()->services;
}

void TGenerateInvitesRequestData::setAccessLevel(const TAccessLevel &accessLevel)
{
    d_func()->accessLevel = accessLevel;
}

void TGenerateInvitesRequestData::setCount(quint16 count)
{
    d_func()->count = count;
}

void TGenerateInvitesRequestData::setExpirationDateTime(const QDateTime &dt)
{
    d_func()->expirationDateTime = dt.toUTC();
}

void TGenerateInvitesRequestData::setGroups(const TIdList &groups)
{
    B_D(TGenerateInvitesRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TGenerateInvitesRequestData::setServices(const TServiceList &services)
{
    B_D(TGenerateInvitesRequestData);
    d->services = services;
    bRemoveDuplicates(d->services);
}

/*============================== Public operators ==========================*/

TGenerateInvitesRequestData &TGenerateInvitesRequestData::operator =(const TGenerateInvitesRequestData &other)
{
    B_D(TGenerateInvitesRequestData);
    const TGenerateInvitesRequestDataPrivate *dd = other.d_func();
    d->accessLevel = dd->accessLevel;
    d->count = dd->count;
    d->expirationDateTime = dd->expirationDateTime;
    d->groups = dd->groups;
    d->services = dd->services;
    return *this;
}

bool TGenerateInvitesRequestData::operator ==(const TGenerateInvitesRequestData &other) const
{
    const B_D(TGenerateInvitesRequestData);
    const TGenerateInvitesRequestDataPrivate *dd = other.d_func();
    return d->accessLevel == dd->accessLevel && d->count == dd->count && d->groups == dd->groups
            && d->expirationDateTime == dd->expirationDateTime && d->services == dd->services;
}

bool TGenerateInvitesRequestData::operator !=(const TGenerateInvitesRequestData &other) const
{
    return !(*this == other);
}

TGenerateInvitesRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesRequestData &data)
{
    const TGenerateInvitesRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("access_level", d->accessLevel);
    m.insert("count", d->count);
    m.insert("expiration_date_time", d->expirationDateTime);
    m.insert("groups", d->groups);
    m.insert("services", d->services);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGenerateInvitesRequestData &data)
{
    TGenerateInvitesRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->accessLevel = m.value("access_level").value<TAccessLevel>();
    d->count = m.value("count").toUInt();
    d->expirationDateTime = m.value("expiration_date_time").toDateTime().toUTC();
    d->groups = m.value("groups").value<TIdList>();
    d->services = m.value("services").value<TServiceList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGenerateInvitesRequestData &/*data*/)
{
    //const TGenerateInvitesRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGenerateInvitesRequestData(" << ")";
    return dbg.space();
}
