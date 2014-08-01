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

#ifndef TUSERINFO_H
#define TUSERINFO_H

class TUserInfoPrivate;

class TAccessLevel;
class TGroupInfoList;
class TServiceList;

class QDataStream;
class QDateTime;
class QDebug;
class QImage;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

class T_CORE_EXPORT TUserInfo : public BBase
{
    B_DECLARE_PRIVATE(TUserInfo)
public:
    explicit TUserInfo();
    TUserInfo(const TUserInfo &other);
    ~TUserInfo();
public:
    TAccessLevel accessLevel() const;
    bool active() const;
    TGroupInfoList availableGroups() const;
    TServiceList availableServices() const;
    QImage avatar() const;
    void clear();
    bool containsAvatar() const;
    QString email() const;
    TGroupInfoList groups() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    QString login() const;
    QString name() const;
    QString patronymic() const;
    QDateTime registrationDateTime() const;
    void setAccessLevel(const TAccessLevel &accessLevel);
    void setActive(bool active);
    void setAvailableGroups(const TGroupInfoList &groups);
    void setAvailableServices(const TServiceList &services);
    void setAvatar(const QImage &avatar);
    void setContainsAvatar(bool contains);
    void setEmail(const QString &email);
    void setGroups(const TGroupInfoList &groups);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setLogin(const QString &login);
    void setName(const QString &name);
    void setPatronymic(const QString &partonymic);
    void setRegistrationDateTime(const QDateTime &dt);
    void setSurname(const QString &surname);
    QString surname() const;
public:
    TUserInfo &operator =(const TUserInfo &other);
    bool operator ==(const TUserInfo &other) const;
    bool operator !=(const TUserInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TUserInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TUserInfo &info);
    friend QDebug operator <<(QDebug dbg, const TUserInfo &info);
};

Q_DECLARE_METATYPE(TUserInfo)

#endif // TUSERINFO_H
