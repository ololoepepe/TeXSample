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

#ifndef TADDUSERREPLYDATA_H
#define TADDUSERREPLYDATA_H

class TAddUserReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddUserReplyData ===========================
============================================================================*/

class T_CORE_EXPORT TAddUserReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddUserReplyData)
public:
    explicit TAddUserReplyData();
    TAddUserReplyData(const TAddUserReplyData &other);
    ~TAddUserReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TAddUserReplyData &operator =(const TAddUserReplyData &other);
    bool operator ==(const TAddUserReplyData &other) const;
    bool operator !=(const TAddUserReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddUserReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddUserReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAddUserReplyData &data);
};

Q_DECLARE_METATYPE(TAddUserReplyData)

#endif // TADDUSERREPLYDATA_H
