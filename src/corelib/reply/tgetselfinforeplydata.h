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

#ifndef TGETSELFINFOREPLYDATA_H
#define TGETSELFINFOREPLYDATA_H

class TGetSelfInfoReplyDataPrivate;

class TUserInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSelfInfoReplyData =======================
============================================================================*/

class T_CORE_EXPORT TGetSelfInfoReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSelfInfoReplyData)
public:
    explicit TGetSelfInfoReplyData();
    TGetSelfInfoReplyData(const TGetSelfInfoReplyData &other);
    ~TGetSelfInfoReplyData();
public:
    void setUserInfo(const TUserInfo &info);
    TUserInfo userInfo() const;
public:
    TGetSelfInfoReplyData &operator =(const TGetSelfInfoReplyData &other);
    bool operator ==(const TGetSelfInfoReplyData &other) const;
    bool operator !=(const TGetSelfInfoReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSelfInfoReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSelfInfoReplyData &data);
};

Q_DECLARE_METATYPE(TGetSelfInfoReplyData)

#endif // TGETSELFINFOREPLYDATA_H
