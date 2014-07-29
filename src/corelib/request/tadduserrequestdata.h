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

#ifndef TADDUSERREQUESTDATA_H
#define TADDUSERREQUESTDATA_H

class TAddUserRequestDataPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;

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
================================ TAddUserRequestData =========================
============================================================================*/

class T_CORE_EXPORT TAddUserRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddUserRequestData)
public:
    explicit TAddUserRequestData();
    TAddUserRequestData(const TAddUserRequestData &other);
    ~TAddUserRequestData();
public:
    TAccessLevel accessLevel() const;
    QImage avatar() const;
    void clear();
    QString email() const;
    QByteArray encryptedPassword() const;
    TIdList groups() const;
    bool isValid() const;
    QString login() const;
    QString name() const;
    QString patronymic() const;
    TServiceList services() const;
    void setAccesslevel(const TAccessLevel &accessLevel);
    void setAvatar(const QImage &avatar);
    void setEmail(const QString &email);
    void setGroups(const TIdList &groups);
    void setLogin(const QString &login);
    void setName(const QString &name);
    void setPassword(const QString &password);
    void setPatronymic(const QString &patronymic);
    void setServices(const TServiceList &services);
    void setSurname(const QString &surname);
    QString surname() const;
public:
    TAddUserRequestData &operator =(const TAddUserRequestData &other);
    bool operator ==(const TAddUserRequestData &other) const;
    bool operator !=(const TAddUserRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddUserRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddUserRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAddUserRequestData &data);
};

Q_DECLARE_METATYPE(TAddUserRequestData)

#endif // TADDUSERREQUESTDATA_H
