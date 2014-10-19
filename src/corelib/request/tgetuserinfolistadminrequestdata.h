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

#ifndef TGETUSERINFOLISTADMINREQUESTDATA_H
#define TGETUSERINFOLISTADMINREQUESTDATA_H

class TGetUserInfoListAdminRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoListAdminRequestData ============
============================================================================*/

class T_CORE_EXPORT TGetUserInfoListAdminRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoListAdminRequestData)
public:
    explicit TGetUserInfoListAdminRequestData();
    TGetUserInfoListAdminRequestData(const TGetUserInfoListAdminRequestData &other);
    ~TGetUserInfoListAdminRequestData();
public:
    TGetUserInfoListAdminRequestData &operator =(const TGetUserInfoListAdminRequestData &other);
    bool operator ==(const TGetUserInfoListAdminRequestData &other) const;
    bool operator !=(const TGetUserInfoListAdminRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoListAdminRequestData)

#endif // TGetUserInfoListAdminRequestData_H
