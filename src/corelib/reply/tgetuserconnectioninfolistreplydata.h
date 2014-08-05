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

#ifndef TGETUSERCONNECTIONINFOLISTREPLYDATA_H
#define TGETUSERCONNECTIONINFOLISTREPLYDATA_H

class TGetUserConnectionInfoListReplyDataPrivate;

class TUserConnectionInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserConnectionInfoListReplyData =========
============================================================================*/

class TGetUserConnectionInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserConnectionInfoListReplyData)
public:
    explicit TGetUserConnectionInfoListReplyData();
    TGetUserConnectionInfoListReplyData(const TGetUserConnectionInfoListReplyData &other);
    ~TGetUserConnectionInfoListReplyData();
public:
    TUserConnectionInfoList connectionInfoList() const;
    void setConnectionInfoList(const TUserConnectionInfoList &list);
public:
    TGetUserConnectionInfoListReplyData &operator =(const TGetUserConnectionInfoListReplyData &other);
    bool operator ==(const TGetUserConnectionInfoListReplyData &other) const;
    bool operator !=(const TGetUserConnectionInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserConnectionInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserConnectionInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserConnectionInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserConnectionInfoListReplyData)

#endif // TGETUSERCONNECTIONINFOLISTREPLYDATA_H
