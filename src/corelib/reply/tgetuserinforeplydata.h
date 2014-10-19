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

#ifndef TGETUSERINFOREPLYDATA_H
#define TGETUSERINFOREPLYDATA_H

class TGetUserInfoReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoReplyData =======================
============================================================================*/

class T_CORE_EXPORT TGetUserInfoReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoReplyData)
public:
    explicit TGetUserInfoReplyData();
    TGetUserInfoReplyData(const TGetUserInfoReplyData &other);
    ~TGetUserInfoReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TGetUserInfoReplyData &operator =(const TGetUserInfoReplyData &other);
    bool operator ==(const TGetUserInfoReplyData &other) const;
    bool operator !=(const TGetUserInfoReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetUserInfoReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoReplyData)

#endif // TGETUSERINFOREPLYDATA_H
