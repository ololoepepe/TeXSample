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

#ifndef TEDITUSERREPLYDATA_H
#define TEDITUSERREPLYDATA_H

class TEditUserReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditUserReplyData ==========================
============================================================================*/

class T_CORE_EXPORT TEditUserReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditUserReplyData)
public:
    explicit TEditUserReplyData();
    TEditUserReplyData(const TEditUserReplyData &other);
    ~TEditUserReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TEditUserReplyData &operator =(const TEditUserReplyData &other);
    bool operator ==(const TEditUserReplyData &other) const;
    bool operator !=(const TEditUserReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditUserReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditUserReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditUserReplyData &data);
};

Q_DECLARE_METATYPE(TEditUserReplyData)

#endif // TEDITUSERREPLYDATA_H
