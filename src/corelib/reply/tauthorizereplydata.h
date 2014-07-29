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

#ifndef TAUTHORIZEREPLYDATA_H
#define TAUTHORIZEREPLYDATA_H

class TAuthorizeReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAuthorizeReplyData =========================
============================================================================*/

class T_CORE_EXPORT TAuthorizeReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAuthorizeReplyData)
public:
    explicit TAuthorizeReplyData();
    TAuthorizeReplyData(const TAuthorizeReplyData &other);
    ~TAuthorizeReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TAuthorizeReplyData &operator =(const TAuthorizeReplyData &other);
    bool operator ==(const TAuthorizeReplyData &other) const;
    bool operator !=(const TAuthorizeReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAuthorizeReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAuthorizeReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAuthorizeReplyData &data);
};

Q_DECLARE_METATYPE(TAuthorizeReplyData)

#endif // TAUTHORIZEREPLYDATA_H
