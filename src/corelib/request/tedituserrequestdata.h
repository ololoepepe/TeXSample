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

#ifndef TEDITUSERREQUESTDATA_H
#define TEDITUSERREQUESTDATA_H

class TEditUserRequestDataPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;
class TUserIdentifier;

class QByteArray;
class QDataStream;
class QDebug;
class QImage;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditUserRequestData ========================
============================================================================*/

class T_CORE_EXPORT TEditUserRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditUserRequestData)
public:
    explicit TEditUserRequestData();
    TEditUserRequestData(const TEditUserRequestData &other);
    ~TEditUserRequestData();
public:
    TAccessLevel accessLevel() const;
    TServiceList availableServices() const;
    QImage avatar() const;
    void clear();
    bool editAvatar() const;
    bool editEmail() const;
    bool editPassword() const;
    QString email() const;
    TIdList groups() const;
    TUserIdentifier identifier() const;
    bool active() const;
    bool isValid() const;
    QString name() const;
    QByteArray password() const;
    QString patronymic() const;
    void setAccesslevel(const TAccessLevel &accessLevel);
    void setActive(bool active);
    void setAvailableServices(const TServiceList &services);
    void setAvatar(const QImage &avatar);
    void setEditAvatar(bool edit);
    void setEditEmail(bool edit);
    void setEditPassword(bool edit);
    void setEmail(const QString &email);
    void setGroups(const TIdList &groups);
    void setIdentifier(const TUserIdentifier &identifier);
    void setName(const QString &name);
    void setPassword(const QByteArray &password);
    void setPatronymic(const QString &patronymic);
    void setSurname(const QString &surname);
    QString surname() const;
public:
    TEditUserRequestData &operator =(const TEditUserRequestData &other);
    bool operator ==(const TEditUserRequestData &other) const;
    bool operator !=(const TEditUserRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditUserRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditUserRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditUserRequestData &data);
};

Q_DECLARE_METATYPE(TEditUserRequestData)

#endif // TEDITUSERREQUESTDATA_H
