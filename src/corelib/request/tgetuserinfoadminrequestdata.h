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

#ifndef TGETUSERINFOADMINREQUESTDATA_H
#define TGETUSERINFOADMINREQUESTDATA_H

class TGetUserInfoAdminRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoAdminRequestData ================
============================================================================*/

class T_CORE_EXPORT TGetUserInfoAdminRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoAdminRequestData)
public:
    explicit TGetUserInfoAdminRequestData();
    TGetUserInfoAdminRequestData(const TGetUserInfoAdminRequestData &other);
    ~TGetUserInfoAdminRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TGetUserInfoAdminRequestData &operator =(const TGetUserInfoAdminRequestData &other);
    bool operator ==(const TGetUserInfoAdminRequestData &other) const;
    bool operator !=(const TGetUserInfoAdminRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoAdminRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoAdminRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoAdminRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoAdminRequestData)

#endif // TGETUSERINFOADMINREQUESTDATA_H
