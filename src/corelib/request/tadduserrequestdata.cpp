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

#include "tadduserrequestdata.h"

#include "taccesslevel.h"
#include "tidlist.h"
#include "tnamespace.h"
#include "tservicelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddUserRequestDataPrivate ==================
============================================================================*/

class TAddUserRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddUserRequestData)
public:
    TAccessLevel accessLevel;
    QImage avatar;
    QString email;
    TIdList groups;
    QString login;
    QString name;
    QByteArray password;
    QString patronymic;
    TServiceList services;
    QString surname;
public:
    explicit TAddUserRequestDataPrivate(TAddUserRequestData *q);
    ~TAddUserRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddUserRequestDataPrivate)
};

/*============================================================================
================================ TAddUserRequestDataPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TAddUserRequestDataPrivate::TAddUserRequestDataPrivate(TAddUserRequestData *q) :
    BBasePrivate(q)
{
    //
}

TAddUserRequestDataPrivate::~TAddUserRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddUserRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddUserRequestData =========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddUserRequestData::TAddUserRequestData() :
    BBase(*new TAddUserRequestDataPrivate(this))
{
    d_func()->init();
}

TAddUserRequestData::TAddUserRequestData(const TAddUserRequestData &other) :
    BBase(*new TAddUserRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddUserRequestData::~TAddUserRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAccessLevel TAddUserRequestData::accessLevel() const
{
    return d_func()->accessLevel;
}

QImage TAddUserRequestData::avatar() const
{
    return d_func()->avatar;
}

void TAddUserRequestData::clear()
{
    B_D(TAddUserRequestData);
    d->accessLevel = TAccessLevel();
    d->avatar = QImage();
    d->email.clear();
    d->groups.clear();
    d->login.clear();
    d->name.clear();
    d->password.clear();
    d->patronymic.clear();
    d->services.clear();
    d->surname.clear();
}

QString TAddUserRequestData::email() const
{
    return d_func()->email;
}

QByteArray TAddUserRequestData::encryptedPassword() const
{
    return d_func()->password;
}

TIdList TAddUserRequestData::groups() const
{
    return d_func()->groups;
}

bool TAddUserRequestData::isValid() const
{
    const B_D(TAddUserRequestData);
    return !d->email.isEmpty() && !d->login.isEmpty() && !d->password.isEmpty();
}

QString TAddUserRequestData::login() const
{
    return d_func()->login;
}

QString TAddUserRequestData::name() const
{
    return d_func()->name;
}

QString TAddUserRequestData::patronymic() const
{
    return d_func()->patronymic;
}

TServiceList TAddUserRequestData::services() const
{
    return d_func()->services;
}

void TAddUserRequestData::setAccesslevel(const TAccessLevel &accessLevel)
{
    d_func()->accessLevel = accessLevel;
}

void TAddUserRequestData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = Texsample::testAvatar(avatar) ? avatar : QImage();
}

void TAddUserRequestData::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

void TAddUserRequestData::setGroups(const TIdList &groups)
{
    B_D(TAddUserRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TAddUserRequestData::setLogin(const QString &login)
{
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

void TAddUserRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TAddUserRequestData::setPassword(const QString &password)
{
    d_func()->password = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

void TAddUserRequestData::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testName(patronymic) ? patronymic : QString();
}

void TAddUserRequestData::setServices(const TServiceList &services)
{
    B_D(TAddUserRequestData);
    d->services = services;
    bRemoveDuplicates(d->services);
}

void TAddUserRequestData::setSurname(const QString &surname)
{
    d_func()->surname = Texsample::testName(surname) ? surname : QString();
}

QString TAddUserRequestData::surname() const
{
    return d_func()->surname;
}

/*============================== Public operators ==========================*/

TAddUserRequestData &TAddUserRequestData::operator =(const TAddUserRequestData &other)
{
    B_D(TAddUserRequestData);
    const TAddUserRequestDataPrivate *dd = other.d_func();
    d->accessLevel = dd->accessLevel;
    d->avatar = dd->avatar;
    d->email = dd->email;
    d->groups = dd->groups;
    d->login = dd->login;
    d->name = dd->name;
    d->password = dd->password;
    d->patronymic = dd->patronymic;
    d->services = dd->services;
    d->surname = dd->surname;
    return *this;
}

bool TAddUserRequestData::operator ==(const TAddUserRequestData &other) const
{
    const B_D(TAddUserRequestData);
    const TAddUserRequestDataPrivate *dd = other.d_func();
    return d->accessLevel == dd->accessLevel && d->avatar == dd->avatar && d->email == dd->email
            && d->groups == dd->groups && d->login == dd->login && d->name == dd->name && d->password == dd->password
            && d->patronymic == dd->patronymic && d->services == dd->services && d->surname == dd->surname;
}

bool TAddUserRequestData::operator !=(const TAddUserRequestData &other) const
{
    return !(*this == other);
}

TAddUserRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddUserRequestData &data)
{
    const TAddUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("access_level", d->accessLevel);
    m.insert("avatar", d->avatar);
    m.insert("email", d->email);
    m.insert("groups", d->groups);
    m.insert("login", d->login);
    m.insert("name", d->name);
    m.insert("password", d->password);
    m.insert("patronymic", d->patronymic);
    m.insert("services", d->services);
    m.insert("surname", d->surname);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddUserRequestData &data)
{
    TAddUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->accessLevel = m.value("access_level").value<TAccessLevel>();
    d->avatar = m.value("avatar").value<QImage>();
    d->email = m.value("email").toString();
    d->groups = m.value("grouos").value<TIdList>();
    d->login = m.value("login").toString();
    d->name = m.value("name").toString();
    d->password = m.value("password").toByteArray();
    d->patronymic = m.value("patronymic").toString();
    d->services = m.value("services").value<TServiceList>();
    d->surname = m.value("surname").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddUserRequestData &data)
{
    const TAddUserRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddUserRequestData(" << d->login << ")";
    return dbg.space();
}
