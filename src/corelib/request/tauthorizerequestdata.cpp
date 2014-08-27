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

#include "tauthorizerequestdata.h"

#include "tclientinfo.h"
#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAuthorizeRequestDataPrivate ================
============================================================================*/

class TAuthorizeRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAuthorizeRequestData)
public:
    TClientInfo clientInfo;
    QString identifier;
    QByteArray password;
public:
    explicit TAuthorizeRequestDataPrivate(TAuthorizeRequestData *q);
    ~TAuthorizeRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAuthorizeRequestDataPrivate)
};

/*============================================================================
================================ TAuthorizeRequestDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorizeRequestDataPrivate::TAuthorizeRequestDataPrivate(TAuthorizeRequestData *q) :
    BBasePrivate(q)
{
    //
}

TAuthorizeRequestDataPrivate::~TAuthorizeRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorizeRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAuthorizeRequestData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorizeRequestData::TAuthorizeRequestData() :
    BBase(*new TAuthorizeRequestDataPrivate(this))
{
    d_func()->init();
}

TAuthorizeRequestData::TAuthorizeRequestData(const TAuthorizeRequestData &other) :
    BBase(*new TAuthorizeRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAuthorizeRequestData::~TAuthorizeRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorizeRequestData::clear()
{
    B_D(TAuthorizeRequestData);
    d->clientInfo = TClientInfo();
    d->identifier.clear();
    d->password.clear();
}

TClientInfo TAuthorizeRequestData::clientInfo() const
{
    return d_func()->clientInfo;
}

QString TAuthorizeRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TAuthorizeRequestData::isValid() const
{
    const B_D(TAuthorizeRequestData);
    return d->clientInfo.isValid() && !d->identifier.isEmpty() && !d->password.isEmpty();
}

QByteArray TAuthorizeRequestData::password() const
{
    return d_func()->password;
}

void TAuthorizeRequestData::setClientInfo(const TClientInfo &info)
{
    d_func()->clientInfo = info;
}

void TAuthorizeRequestData::setIdentifier(const QString &identifier)
{
    d_func()->identifier = (Texsample::testLogin(identifier) || Texsample::testEmail(identifier)) ? identifier :
                                                                                                    QString();
}

void TAuthorizeRequestData::setPassword(const QByteArray &password)
{
    d_func()->password = Texsample::testPassword(password) ? password : QByteArray();
}

/*============================== Public operators ==========================*/

TAuthorizeRequestData &TAuthorizeRequestData::operator =(const TAuthorizeRequestData &other)
{
    B_D(TAuthorizeRequestData);
    const TAuthorizeRequestDataPrivate *dd = other.d_func();
    d->clientInfo = dd->clientInfo;
    d->identifier = dd->identifier;
    d->password = dd->password;
    return *this;
}

bool TAuthorizeRequestData::operator ==(const TAuthorizeRequestData &other) const
{
    const B_D(TAuthorizeRequestData);
    const TAuthorizeRequestDataPrivate *dd = other.d_func();
    return d->clientInfo == dd->clientInfo && d->identifier == dd->identifier && d->password == dd->password;
}

bool TAuthorizeRequestData::operator !=(const TAuthorizeRequestData &other) const
{
    return !(*this == other);
}

TAuthorizeRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAuthorizeRequestData &data)
{
    const TAuthorizeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("client_info", d->clientInfo);
    m.insert("identifier", d->identifier);
    m.insert("password", d->password);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAuthorizeRequestData &data)
{
    TAuthorizeRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->clientInfo = m.value("client_info").value<TClientInfo>();
    d->identifier = m.value("identifier").toString();
    d->password = m.value("password").toByteArray();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAuthorizeRequestData &data)
{
    const TAuthorizeRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TAuthorizeRequestData(" << d->identifier << ")";
    return dbg.space();
}
