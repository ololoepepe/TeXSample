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

#ifndef TGETUSERAVATARREQUESTDATA_H
#define TGETUSERAVATARREQUESTDATA_H

class TGetUserAvatarRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserAvatarRequestData ===================
============================================================================*/

class T_CORE_EXPORT TGetUserAvatarRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserAvatarRequestData)
public:
    explicit TGetUserAvatarRequestData();
    TGetUserAvatarRequestData(const TGetUserAvatarRequestData &other);
    ~TGetUserAvatarRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TGetUserAvatarRequestData &operator =(const TGetUserAvatarRequestData &other);
    bool operator ==(const TGetUserAvatarRequestData &other) const;
    bool operator !=(const TGetUserAvatarRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserAvatarRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserAvatarRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserAvatarRequestData)

#endif // TGETUSERAVATARREQUESTDATA_H
