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

#ifndef TGETUSERINFOREQUESTDATA_H
#define TGETUSERINFOREQUESTDATA_H

class TGetUserInfoRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoRequestData =====================
============================================================================*/

class T_CORE_EXPORT TGetUserInfoRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoRequestData)
public:
    explicit TGetUserInfoRequestData();
    TGetUserInfoRequestData(const TGetUserInfoRequestData &other);
    ~TGetUserInfoRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool includeAvatar() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
    void setIncludeAvatar(bool include);
public:
    TGetUserInfoRequestData &operator =(const TGetUserInfoRequestData &other);
    bool operator ==(const TGetUserInfoRequestData &other) const;
    bool operator !=(const TGetUserInfoRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoRequestData)

#endif // TGETUSERINFOREQUESTDATA_H
