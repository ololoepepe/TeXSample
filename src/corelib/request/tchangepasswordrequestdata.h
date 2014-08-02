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

#ifndef TCHANGEPASSWORDREQUESTDATA_H
#define TCHANGEPASSWORDREQUESTDATA_H

class TChangePasswordRequestDataPrivate;

class QByteArray;
class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TChangePasswordRequestData ==================
============================================================================*/

class T_CORE_EXPORT TChangePasswordRequestData : public BBase
{
    B_DECLARE_PRIVATE(TChangePasswordRequestData)
public:
    explicit TChangePasswordRequestData();
    TChangePasswordRequestData(const TChangePasswordRequestData &other);
    ~TChangePasswordRequestData();
public:
    void clear();
    bool isValid() const;
    QByteArray newPassword() const;
    QByteArray oldPassword() const;
    void setNewPassword(const QByteArray &password);
    void setOldPassword(const QByteArray &password);
public:
    TChangePasswordRequestData &operator =(const TChangePasswordRequestData &other);
    bool operator ==(const TChangePasswordRequestData &other) const;
    bool operator !=(const TChangePasswordRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TChangePasswordRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TChangePasswordRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TChangePasswordRequestData &data);
};

Q_DECLARE_METATYPE(TChangePasswordRequestData)

#endif // TCHANGEPASSWORDREQUESTDATA_H
