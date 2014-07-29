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

#ifndef TREGISTERREPLYDATA_H
#define TREGISTERREPLYDATA_H

class TRegisterReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRegisterReplyData ==========================
============================================================================*/

class T_CORE_EXPORT TRegisterReplyData : public BBase
{
    B_DECLARE_PRIVATE(TRegisterReplyData)
public:
    explicit TRegisterReplyData();
    TRegisterReplyData(const TRegisterReplyData &other);
    ~TRegisterReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TRegisterReplyData &operator =(const TRegisterReplyData &other);
    bool operator ==(const TRegisterReplyData &other) const;
    bool operator !=(const TRegisterReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRegisterReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRegisterReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TRegisterReplyData &data);
};

Q_DECLARE_METATYPE(TRegisterReplyData)

#endif // TREGISTERREPLYDATA_H
