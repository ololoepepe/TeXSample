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

#ifndef TEDITGROUPREPLYDATA_H
#define TEDITGROUPREPLYDATA_H

class TEditGroupReplyDataPrivate;

class TGroupInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditGroupReplyData =========================
============================================================================*/

class T_CORE_EXPORT TEditGroupReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditGroupReplyData)
public:
    explicit TEditGroupReplyData();
    TEditGroupReplyData(const TEditGroupReplyData &other);
    ~TEditGroupReplyData();
public:
    TGroupInfo groupInfo() const;
    void setGroupInfo(const TGroupInfo &info);
public:
    TEditGroupReplyData &operator =(const TEditGroupReplyData &other);
    bool operator ==(const TEditGroupReplyData &other) const;
    bool operator !=(const TEditGroupReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditGroupReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditGroupReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditGroupReplyData &data);
};

Q_DECLARE_METATYPE(TEditGroupReplyData)

#endif // TEDITGROUPREPLYDATA_H
