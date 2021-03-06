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

#include "tuserinfo.h"

#include "taccesslevel.h"
#include "tgroupinfolist.h"
#include "tnamespace.h"
#include "tservicelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

class TUserInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserInfo)
public:
    TAccessLevel accessLevel;
    bool active;
    TGroupInfoList availableGroups;
    TServiceList availableServices;
    QImage avatar;
    QString email;
    TGroupInfoList groups;
    quint64 id;
    QDateTime lastModificationDateTime;
    QString login;
    QString name;
    QString patronymic;
    QDateTime registrationDateTime;
    QString surname;
public:
    explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TUserInfoPrivate)
};

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

/*============================== Public constructors =======================*/

TUserInfoPrivate::TUserInfoPrivate(TUserInfo *q) :
    BBasePrivate(q)
{
    //
}

TUserInfoPrivate::~TUserInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserInfoPrivate::init()
{
    active = true;
    id = 0;
    lastModificationDateTime.setTimeSpec(Qt::UTC);
    registrationDateTime.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserInfo::TUserInfo() :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
}

TUserInfo::TUserInfo(const TUserInfo &other) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TUserInfo::~TUserInfo()
{
    //
}

/*============================== Public methods ============================*/

TAccessLevel TUserInfo::accessLevel() const
{
    return d_func()->accessLevel;
}

bool TUserInfo::active() const
{
    return d_func()->active;
}

TGroupInfoList TUserInfo::availableGroups() const
{
    return d_func()->availableGroups;
}

TServiceList TUserInfo::availableServices() const
{
    return d_func()->availableServices;
}

QImage TUserInfo::avatar() const
{
    return d_func()->avatar;
}

void TUserInfo::clear()
{
    B_D(TUserInfo);
    d->accessLevel = TAccessLevel();
    d->active = true;
    d->availableGroups.clear();
    d->availableServices.clear();
    d->avatar = QImage();
    d->email.clear();
    d->id = 0;
    d->lastModificationDateTime = QDateTime().toUTC();
    d->login.clear();
    d->name.clear();
    d->patronymic.clear();
    d->registrationDateTime = QDateTime().toUTC();
    d->surname.clear();
}

QString TUserInfo::email() const
{
    return d_func()->email;
}

TGroupInfoList TUserInfo::groups() const
{
    return d_func()->groups;
}

quint64 TUserInfo::id() const
{
    return d_func()->id;
}

bool TUserInfo::isValid() const
{
    const B_D(TUserInfo);
    return d->accessLevel.isValid() && d->id && !d->login.isEmpty() && d->registrationDateTime.isValid();
}

QDateTime TUserInfo::lastModificationDateTime() const
{
    return d_func()->lastModificationDateTime;
}

QString TUserInfo::login() const
{
    return d_func()->login;
}

QString TUserInfo::name() const
{
    return d_func()->name;
}

QString TUserInfo::patronymic() const
{
    return d_func()->patronymic;
}

QDateTime TUserInfo::registrationDateTime() const
{
    return d_func()->registrationDateTime;
}

void TUserInfo::setAccessLevel(const TAccessLevel &lvl)
{
    d_func()->accessLevel = lvl;
}

void TUserInfo::setActive(bool active)
{
    d_func()->active = active;
}

void TUserInfo::setAvailableGroups(const TGroupInfoList &groups)
{
    d_func()->availableGroups = groups;
    bRemoveDuplicates(d_func()->availableGroups);
}

void TUserInfo::setAvailableServices(const TServiceList &services)
{
    B_D(TUserInfo);
    d->availableServices = services;
    bRemoveDuplicates(d->availableServices);
}

void TUserInfo::setAvatar(const QImage &avatar)
{
    d_func()->avatar = avatar;
}

void TUserInfo::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

void TUserInfo::setGroups(const TGroupInfoList &groups)
{
    B_D(TUserInfo);
    d->groups = groups;
    bRemoveDuplicates(d->groups);
}

void TUserInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TUserInfo::setLastModificationDateTime(const QDateTime &dt)
{
    d_func()->lastModificationDateTime = dt.toUTC();
}

void TUserInfo::setLogin(const QString &login)
{
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

void TUserInfo::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TUserInfo::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testPatronymic(patronymic) ? patronymic : QString();
}

void TUserInfo::setRegistrationDateTime(const QDateTime &dt)
{
    d_func()->registrationDateTime = dt.toUTC();
}

void TUserInfo::setSurname(const QString &surname)
{
    d_func()->surname = Texsample::testSurname(surname) ? surname : QString();
}

QString TUserInfo::surname() const
{
    return d_func()->surname;
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    d->accessLevel = dd->accessLevel;
    d->active = dd->active;
    d->availableGroups = dd->availableGroups;
    d->availableServices = dd->availableServices;
    d->avatar = dd->avatar;
    d->email = dd->email;
    d->groups = dd->groups;
    d->id = dd->id;
    d->lastModificationDateTime = dd->lastModificationDateTime;
    d->login = dd->login;
    d->name = dd->name;
    d->patronymic = dd->patronymic;
    d->registrationDateTime = dd->registrationDateTime;
    d->surname = dd->surname;
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    const B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    return d->accessLevel == dd->accessLevel && d->active == dd->active && d->availableGroups == dd->availableGroups
            && d->availableServices == dd->availableServices && d->avatar == dd->avatar && d->email == dd->email
            && d->groups == dd->groups && d->id == dd->id
            && d->lastModificationDateTime == dd->lastModificationDateTime && d->login == dd->login
            && d->name == dd->name && d->patronymic == dd->patronymic
            && d->registrationDateTime == dd->registrationDateTime && d->surname == dd->surname;
}

bool TUserInfo::operator !=(const TUserInfo &other) const
{
    return !(*this == other);
}

TUserInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("access_level", d->accessLevel);
    m.insert("active", d->active);
    m.insert("available_groups", d->availableGroups);
    m.insert("available_services", d->availableServices);
    m.insert("avatar", d->avatar);
    m.insert("email", d->email);
    m.insert("groups", d->groups);
    m.insert("id", d->id);
    m.insert("last_modification_date_time", d->lastModificationDateTime);
    m.insert("login", d->login);
    m.insert("name", d->name);
    m.insert("patronymic", d->patronymic);
    m.insert("registration_date_time", d->registrationDateTime);
    m.insert("surname", d->surname);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    TUserInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->accessLevel = m.value("access_level").value<TAccessLevel>();
    d->active = m.value("active", true).toBool();
    d->availableGroups = m.value("available_groups").value<TGroupInfoList>();
    d->availableServices = m.value("available_services").value<TServiceList>();
    d->avatar = m.value("avatar").value<QImage>();
    d->email = m.value("email").toString();
    d->groups = m.value("groups").value<TGroupInfoList>();
    d->id = m.value("id").toULongLong();
    d->lastModificationDateTime = m.value("last_modification_date_time").toDateTime().toUTC();
    d->login = m.value("login").toString();
    d->name = m.value("name").toString();
    d->patronymic = m.value("patronymic").toString();
    d->registrationDateTime = m.value("registration_date_time").toDateTime().toUTC();
    d->surname = m.value("surname").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    dbg.nospace() << "TUserInfo(" << d->id << "," << d->login << ")";
    return dbg.space();
}
