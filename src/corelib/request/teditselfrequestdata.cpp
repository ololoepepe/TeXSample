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

#include "teditselfrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSelfRequestDataPrivate =================
============================================================================*/

class TEditSelfRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSelfRequestData)
public:
    QImage avatar;
    bool editAvatar;
    QString name;
    QString patronymic;
    QString surname;
public:
    explicit TEditSelfRequestDataPrivate(TEditSelfRequestData *q);
    ~TEditSelfRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSelfRequestDataPrivate)
};

/*============================================================================
================================ TEditSelfRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfRequestDataPrivate::TEditSelfRequestDataPrivate(TEditSelfRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditSelfRequestDataPrivate::~TEditSelfRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSelfRequestDataPrivate::init()
{
    editAvatar = false;
}

/*============================================================================
================================ TEditSelfRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfRequestData::TEditSelfRequestData() :
    BBase(*new TEditSelfRequestDataPrivate(this))
{
    d_func()->init();
}

TEditSelfRequestData::TEditSelfRequestData(const TEditSelfRequestData &other) :
    BBase(*new TEditSelfRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSelfRequestData::~TEditSelfRequestData()
{
    //
}

/*============================== Public methods ============================*/

QImage TEditSelfRequestData::avatar() const
{
    return d_func()->avatar;
}

void TEditSelfRequestData::clear()
{
    B_D(TEditSelfRequestData);
    d->avatar = QImage();
    d->editAvatar = false;
    d->name.clear();
    d->patronymic.clear();
    d->surname.clear();
}

bool TEditSelfRequestData::editAvatar() const
{
    return d_func()->editAvatar;
}

QString TEditSelfRequestData::name() const
{
    return d_func()->name;
}

QString TEditSelfRequestData::patronymic() const
{
    return d_func()->patronymic;
}

bool TEditSelfRequestData::isValid() const
{
    return true;
}

void TEditSelfRequestData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = Texsample::testAvatar(avatar) ? avatar : QImage();
}

void TEditSelfRequestData::setEditAvatar(bool edit)
{
    d_func()->editAvatar = edit;
}

void TEditSelfRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TEditSelfRequestData::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testPatronymic(patronymic) ? patronymic : QString();
}

void TEditSelfRequestData::setSurname(const QString &surname)
{
    d_func()->surname = Texsample::testSurname(surname) ? surname : QString();
}

QString TEditSelfRequestData::surname() const
{
    return d_func()->surname;
}

/*============================== Public operators ==========================*/

TEditSelfRequestData &TEditSelfRequestData::operator =(const TEditSelfRequestData &other)
{
    B_D(TEditSelfRequestData);
    const TEditSelfRequestDataPrivate *dd = other.d_func();
    d->avatar = dd->avatar;
    d->editAvatar = dd->editAvatar;
    d->name = dd->name;
    d->patronymic = dd->patronymic;
    d->surname = dd->surname;
    return *this;
}

bool TEditSelfRequestData::operator ==(const TEditSelfRequestData &other) const
{
    const B_D(TEditSelfRequestData);
    const TEditSelfRequestDataPrivate *dd = other.d_func();
    return d->avatar == dd->avatar && d->editAvatar == dd->editAvatar && d->name == dd->name
            && d->patronymic == dd->patronymic && d->surname == dd->surname;
}

bool TEditSelfRequestData::operator !=(const TEditSelfRequestData &other) const
{
    return !(*this == other);
}

TEditSelfRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSelfRequestData &data)
{
    const TEditSelfRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    if (d->editAvatar)
        m.insert("avatar", d->avatar);
    m.insert("edit_avatar", d->editAvatar);
    m.insert("name", d->name);
    m.insert("patronymic", d->patronymic);
    m.insert("surname", d->surname);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSelfRequestData &data)
{
    TEditSelfRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->avatar = m.value("avatar").value<QImage>();
    d->editAvatar = m.value("edit_avatar").toBool();
    d->name = m.value("name").toString();
    d->patronymic = m.value("patronymic").toString();
    d->surname = m.value("surname").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSelfRequestData &/*data*/)
{
    //const TEditSelfRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSelfRequestData(" << ")";
    return dbg.space();
}
