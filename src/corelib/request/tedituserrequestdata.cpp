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

#include "tedituserrequestdata.h"

#include "taccesslevel.h"
#include "tidlist.h"
#include "tnamespace.h"
#include "tservicelist.h"
#include "tuseridentifier.h"

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
================================ TEditUserRequestDataPrivate =================
============================================================================*/

class TEditUserRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditUserRequestData)
public:
    TAccessLevel accessLevel;
    bool active;
    TServiceList availableServices;
    QImage avatar;
    bool editAvatar;
    bool editEmail;
    bool editPassword;
    QString email;
    TIdList groups;
    TUserIdentifier identifier;
    QString name;
    QByteArray password;
    QString patronymic;
    QString surname;
public:
    explicit TEditUserRequestDataPrivate(TEditUserRequestData *q);
    ~TEditUserRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditUserRequestDataPrivate)
};

/*============================================================================
================================ TEditUserRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TEditUserRequestDataPrivate::TEditUserRequestDataPrivate(TEditUserRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditUserRequestDataPrivate::~TEditUserRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditUserRequestDataPrivate::init()
{
    active = true;
    editAvatar = false;
    editEmail = false;
    editPassword = false;
}

/*============================================================================
================================ TEditUserRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditUserRequestData::TEditUserRequestData() :
    BBase(*new TEditUserRequestDataPrivate(this))
{
    d_func()->init();
}

TEditUserRequestData::TEditUserRequestData(const TEditUserRequestData &other) :
    BBase(*new TEditUserRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditUserRequestData::~TEditUserRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAccessLevel TEditUserRequestData::accessLevel() const
{
    return d_func()->accessLevel;
}

bool TEditUserRequestData::active() const
{
    return d_func()->active;
}

TServiceList TEditUserRequestData::availableServices() const
{
    return d_func()->availableServices;
}

QImage TEditUserRequestData::avatar() const
{
    return d_func()->avatar;
}

void TEditUserRequestData::clear()
{
    B_D(TEditUserRequestData);
    d->accessLevel = TAccessLevel();
    d->active = true;
    d->availableServices.clear();
    d->avatar = QImage();
    d->editAvatar = false;
    d->editEmail = false;
    d->editPassword = false;
    d->email.clear();
    d->groups.clear();
    d->identifier.clear();
    d->name.clear();
    d->password.clear();
    d->patronymic.clear();
    d->surname.clear();
}

bool TEditUserRequestData::editAvatar() const
{
    return d_func()->editAvatar;
}

bool TEditUserRequestData::editEmail() const
{
    return d_func()->editEmail;
}

bool TEditUserRequestData::editPassword() const
{
    return d_func()->editPassword;
}

QString TEditUserRequestData::email() const
{
    return d_func()->email;
}

QByteArray TEditUserRequestData::encryptedPassword() const
{
    return d_func()->password;
}

TIdList TEditUserRequestData::groups() const
{
    return d_func()->groups;
}

TUserIdentifier TEditUserRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TEditUserRequestData::isValid() const
{
    const B_D(TEditUserRequestData);
    return d->identifier.isValid() && (!d->editEmail || !d->email.isEmpty())
            && (!d->editPassword || !d->password.isEmpty());
}

QString TEditUserRequestData::name() const
{
    return d_func()->name;
}

QString TEditUserRequestData::patronymic() const
{
    return d_func()->patronymic;
}

void TEditUserRequestData::setAccesslevel(const TAccessLevel &accessLevel)
{
    d_func()->accessLevel = accessLevel;
}

void TEditUserRequestData::setActive(bool active)
{
    d_func()->active = active;
}

void TEditUserRequestData::setAvailableServices(const TServiceList &services)
{
    B_D(TEditUserRequestData);
    d->availableServices = services;
    bRemoveDuplicates(d->availableServices);
}

void TEditUserRequestData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = Texsample::testAvatar(avatar) ? avatar : QImage();
}

void TEditUserRequestData::setEditAvatar(bool edit)
{
    d_func()->editAvatar = edit;
}

void TEditUserRequestData::setEditEmail(bool edit)
{
    d_func()->editEmail = edit;
}

void TEditUserRequestData::setEditPassword(bool edit)
{
    d_func()->editPassword = edit;
}

void TEditUserRequestData::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

void TEditUserRequestData::setGroups(const TIdList &groups)
{
    B_D(TEditUserRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TEditUserRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

void TEditUserRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TEditUserRequestData::setPassword(const QString &password)
{
    d_func()->password = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

void TEditUserRequestData::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testName(patronymic) ? patronymic : QString();
}

void TEditUserRequestData::setSurname(const QString &surname)
{
    d_func()->surname = Texsample::testName(surname) ? surname : QString();
}

QString TEditUserRequestData::surname() const
{
    return d_func()->surname;
}

/*============================== Public operators ==========================*/

TEditUserRequestData &TEditUserRequestData::operator =(const TEditUserRequestData &other)
{
    B_D(TEditUserRequestData);
    const TEditUserRequestDataPrivate *dd = other.d_func();
    d->accessLevel = dd->accessLevel;
    d->active = dd->active;
    d->availableServices = dd->availableServices;
    d->avatar = dd->avatar;
    d->editAvatar = dd->editAvatar;
    d->editEmail = dd->editEmail;
    d->editPassword = dd->editPassword;
    d->email = dd->email;
    d->groups = dd->groups;
    d->identifier = dd->identifier;
    d->name = dd->name;
    d->password = dd->password;
    d->patronymic = dd->patronymic;
    d->surname = dd->surname;
    return *this;
}

bool TEditUserRequestData::operator ==(const TEditUserRequestData &other) const
{
    const B_D(TEditUserRequestData);
    const TEditUserRequestDataPrivate *dd = other.d_func();
    return d->accessLevel == dd->accessLevel && d->active == dd->active
            && d->availableServices == dd->availableServices && d->avatar == dd->avatar
            && d->editAvatar == dd->editAvatar && d->editEmail == dd->editEmail
            && d->editPassword == dd->editPassword && d->email == dd->email && d->groups == dd->groups
            && d->identifier == dd->identifier && d->name == dd->name && d->password == dd->password
            && d->patronymic == dd->patronymic && d->surname == dd->surname;
}

bool TEditUserRequestData::operator !=(const TEditUserRequestData &other) const
{
    return !(*this == other);
}

TEditUserRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditUserRequestData &data)
{
    const TEditUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("access_level", d->accessLevel);
    m.insert("active", d->active);
    m.insert("available_services", d->availableServices);
    if (d->editAvatar)
        m.insert("avatar", d->avatar);
    m.insert("edit_avatar", d->editAvatar);
    m.insert("edit_email", d->editEmail);
    m.insert("edit_password", d->editPassword);
    if (d->editEmail)
        m.insert("email", d->email);
    m.insert("groups", d->groups);
    m.insert("identifier", d->identifier);
    m.insert("name", d->name);
    if (d->editPassword)
        m.insert("password", d->password);
    m.insert("patronymic", d->patronymic);
    m.insert("surname", d->surname);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditUserRequestData &data)
{
    TEditUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->accessLevel = m.value("access_level").value<TAccessLevel>();
    d->active = m.value("active", true).toBool();
    d->availableServices = m.value("available_services").value<TServiceList>();
    d->avatar = m.value("avatar").value<QImage>();
    d->editAvatar = m.value("edit_avatar").toBool();
    d->editEmail = m.value("edit_email").toBool();
    d->editPassword = m.value("edit_password").toBool();
    d->email = m.value("email").toString();
    d->groups = m.value("groups").value<TIdList>();
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    d->name = m.value("name").toString();
    d->password = m.value("password").toByteArray();
    d->patronymic = m.value("patronymic").toString();
    d->surname = m.value("surname").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditUserRequestData &/*data*/)
{
    //const TEditUserRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditUserRequestData(" << ")";
    return dbg.space();
}
