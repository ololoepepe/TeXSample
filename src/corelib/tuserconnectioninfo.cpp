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

#include "tuserconnectioninfo.h"

#include "tclientinfo.h"
#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TUserConnectionInfoPrivate ==================
============================================================================*/

class TUserConnectionInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserConnectionInfo)
public:
    TClientInfo clientInfo;
    QDateTime connectionDateTime;
    QString peerAddress;
    BUuid uniqueId;
    qint64 uptime;
    TUserInfo userInfo;
public:
    explicit TUserConnectionInfoPrivate(TUserConnectionInfo *q);
    ~TUserConnectionInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TUserConnectionInfoPrivate)
};


/*============================================================================
================================ TUserConnectionInfoPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TUserConnectionInfoPrivate::TUserConnectionInfoPrivate(TUserConnectionInfo *q) :
    BBasePrivate(q)
{
    //
}

TUserConnectionInfoPrivate::~TUserConnectionInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserConnectionInfoPrivate::init()
{
    connectionDateTime = QDateTime().toUTC();
    uptime = 0;
}

/*============================================================================
================================ TUserConnectionInfo =========================
============================================================================*/

/*============================== Public constructors =======================*/

TUserConnectionInfo::TUserConnectionInfo() :
    BBase(*new TUserConnectionInfoPrivate(this))
{
    d_func()->init();
}

TUserConnectionInfo::TUserConnectionInfo(const TUserConnectionInfo &other) :
    BBase(*new TUserConnectionInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TUserConnectionInfo::~TUserConnectionInfo()
{
    //
}

/*============================== Public methods ============================*/

void TUserConnectionInfo::clear()
{
    B_D(TUserConnectionInfo);
    d->clientInfo = TClientInfo();
    d->connectionDateTime = QDateTime().toUTC();
    d->peerAddress.clear();
    d->uniqueId = BUuid();
    d->uptime = 0;
    d->userInfo.clear();
}

TClientInfo TUserConnectionInfo::clientInfo() const
{
    return d_func()->clientInfo;
}

QDateTime TUserConnectionInfo::connectionDateTime() const
{
    return d_func()->connectionDateTime;
}

bool TUserConnectionInfo::isValid() const
{
    const B_D(TUserConnectionInfo);
    return d->clientInfo.isValid() && d->connectionDateTime.isValid() && !d->peerAddress.isEmpty()
            && !d->uniqueId.isNull();
}

QString TUserConnectionInfo::peerAddress() const
{
    return d_func()->peerAddress;
}

void TUserConnectionInfo::setClientInfo(const TClientInfo &info)
{
    d_func()->clientInfo = info;
}

void TUserConnectionInfo::setConnectionDateTime(const QDateTime &dt)
{
    d_func()->connectionDateTime = dt.toUTC();
}

void TUserConnectionInfo::setPeerAddress(const QString &address)
{
    d_func()->peerAddress = address;
}

void TUserConnectionInfo::setUniqueId(const BUuid &id)
{
    d_func()->uniqueId = id;
}

void TUserConnectionInfo::setUptime(qint64 msecs)
{
    d_func()->uptime = (msecs > 0) ? msecs : 0;
}

void TUserConnectionInfo::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

BUuid TUserConnectionInfo::uniqueId() const
{
    return d_func()->uniqueId;
}

qint64 TUserConnectionInfo::uptime() const
{
    return d_func()->uptime;
}

TUserInfo TUserConnectionInfo::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TUserConnectionInfo &TUserConnectionInfo::operator =(const TUserConnectionInfo &other)
{
    B_D(TUserConnectionInfo);
    const TUserConnectionInfoPrivate *dd = other.d_func();
    d->clientInfo = dd->clientInfo;
    d->connectionDateTime = dd->connectionDateTime;
    d->peerAddress = dd->peerAddress;
    d->uniqueId = dd->uniqueId;
    d->uptime = dd->uptime;
    d->userInfo = dd->userInfo;
    return *this;
}

bool TUserConnectionInfo::operator ==(const TUserConnectionInfo &other) const
{
    const B_D(TUserConnectionInfo);
    const TUserConnectionInfoPrivate *dd = other.d_func();
    return d->clientInfo == dd->clientInfo && d->connectionDateTime == dd->connectionDateTime
            && d->peerAddress == dd->peerAddress && d->uniqueId == dd->uniqueId && d->uptime == dd->uptime
            && d->userInfo == dd->userInfo;
}

bool TUserConnectionInfo::operator !=(const TUserConnectionInfo &other) const
{
    return !(*this == other);
}

TUserConnectionInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserConnectionInfo &data)
{
    const TUserConnectionInfoPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("client_info", d->clientInfo);
    m.insert("connection_date_time", d->connectionDateTime);
    m.insert("peer_address", d->peerAddress);
    m.insert("unique_id", d->uniqueId);
    m.insert("uptime", d->uptime);
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserConnectionInfo &data)
{
    TUserConnectionInfoPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->clientInfo = m.value("client_info").value<TClientInfo>();
    d->connectionDateTime = m.value("connection_date_time").toDateTime();
    d->peerAddress = m.value("peer_address").toString();
    d->uniqueId = m.value("unique_id").value<BUuid>();
    d->uptime = m.value("uptime").toLongLong();
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserConnectionInfo &/*data*/)
{
    //const TUserConnectionInfoPrivate *d = data.d_func();
    dbg.nospace() << "TUserConnectionInfo(" << ")";
    return dbg.space();
}
