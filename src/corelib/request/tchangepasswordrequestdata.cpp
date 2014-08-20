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

#include "tchangepasswordrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TChangePasswordRequestDataPrivate ===========
============================================================================*/

class TChangePasswordRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TChangePasswordRequestData)
public:
    QByteArray newPassword;
    QByteArray oldPassword;
public:
    explicit TChangePasswordRequestDataPrivate(TChangePasswordRequestData *q);
    ~TChangePasswordRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TChangePasswordRequestDataPrivate)
};

/*============================================================================
================================ TChangePasswordRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TChangePasswordRequestDataPrivate::TChangePasswordRequestDataPrivate(TChangePasswordRequestData *q) :
    BBasePrivate(q)
{
    //
}

TChangePasswordRequestDataPrivate::~TChangePasswordRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TChangePasswordRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TChangePasswordRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TChangePasswordRequestData::TChangePasswordRequestData() :
    BBase(*new TChangePasswordRequestDataPrivate(this))
{
    d_func()->init();
}

TChangePasswordRequestData::TChangePasswordRequestData(const TChangePasswordRequestData &other) :
    BBase(*new TChangePasswordRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TChangePasswordRequestData::~TChangePasswordRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TChangePasswordRequestData::clear()
{
    d_func()->newPassword.clear();
    d_func()->oldPassword.clear();
}

bool TChangePasswordRequestData::isValid() const
{
    return !d_func()->newPassword.isEmpty() && !d_func()->oldPassword.isEmpty();
}

QByteArray TChangePasswordRequestData::newPassword() const
{
    return d_func()->newPassword;
}

QByteArray TChangePasswordRequestData::oldPassword() const
{
    return d_func()->oldPassword;
}

void TChangePasswordRequestData::setNewPassword(const QByteArray &password)
{
    d_func()->newPassword = Texsample::testPassword(password) ? password : QByteArray();
}

void TChangePasswordRequestData::setOldPassword(const QByteArray &password)
{
    d_func()->oldPassword = Texsample::testPassword(password) ? password : QByteArray();
}

/*============================== Public operators ==========================*/

TChangePasswordRequestData &TChangePasswordRequestData::operator =(const TChangePasswordRequestData &other)
{
    B_D(TChangePasswordRequestData);
    const TChangePasswordRequestDataPrivate *dd = other.d_func();
    d->newPassword = dd->newPassword;
    d->oldPassword = dd->oldPassword;
    return *this;
}

bool TChangePasswordRequestData::operator ==(const TChangePasswordRequestData &other) const
{
    const B_D(TChangePasswordRequestData);
    const TChangePasswordRequestDataPrivate *dd = other.d_func();
    return d->newPassword == dd->newPassword && d->oldPassword == dd->oldPassword;
}

bool TChangePasswordRequestData::operator !=(const TChangePasswordRequestData &other) const
{
    return !(*this == other);
}

TChangePasswordRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TChangePasswordRequestData &data)
{
    const TChangePasswordRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("new_password", d->newPassword);
    m.insert("old_password", d->oldPassword);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TChangePasswordRequestData &data)
{
    TChangePasswordRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->newPassword = m.value("new_password").toByteArray();
    d->oldPassword = m.value("old_password").toByteArray();
    return stream;
}

QDebug operator <<(QDebug dbg, const TChangePasswordRequestData &/*data*/)
{
    //const TChangePasswordRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TChangePasswordRequestData(" << ")";
    return dbg.space();
}
