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

#ifndef TREGISTERREQUESTDATA_H
#define TREGISTERREQUESTDATA_H

class TRegisterRequestDataPrivate;

class BUuid;

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
================================ TRegisterRequestData ========================
============================================================================*/

class T_CORE_EXPORT TRegisterRequestData : public BBase
{
    B_DECLARE_PRIVATE(TRegisterRequestData)
public:
    explicit TRegisterRequestData();
    TRegisterRequestData(const TRegisterRequestData &other);
    ~TRegisterRequestData();
public:
    QImage avatar() const;
    void clear();
    QString email() const;
    QByteArray encryptedPassword() const;
    BUuid inviteCode() const;
    bool isValid() const;
    QString login() const;
    QString name() const;
    QString patronymic() const;
    void setAvatar(const QImage &avatar);
    void setEmail(const QString &email);
    void setInviteCode(const QString &inviteCode);
    void setLogin(const QString &login);
    void setName(const QString &name);
    void setPassword(const QString &password);
    void setPatronymic(const QString &patronymic);
    void setSurname(const QString &surname);
    QString surname() const;
public:
    TRegisterRequestData &operator =(const TRegisterRequestData &other);
    bool operator ==(const TRegisterRequestData &other) const;
    bool operator !=(const TRegisterRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRegisterRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRegisterRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TRegisterRequestData &data);
};

Q_DECLARE_METATYPE(TRegisterRequestData)

#endif // TREGISTERREQUESTDATA_H
