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

#ifndef TGETLABINFOLISTREPLYDATA_H
#define TGETLABINFOLISTREPLYDATA_H

class TGetLabInfoListReplyDataPrivate;

class TIdList;
class TLabInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabInfoListReplyData ====================
============================================================================*/

class T_CORE_EXPORT TGetLabInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabInfoListReplyData)
public:
    explicit TGetLabInfoListReplyData();
    TGetLabInfoListReplyData(const TGetLabInfoListReplyData &other);
    ~TGetLabInfoListReplyData();
public:
    TIdList deletedLabs() const;
    TLabInfoList newLabs() const;
    void setDeletedLabs(const TIdList &deletedLabs);
    void setNewLabs(const TLabInfoList &newLabs);
public:
    TGetLabInfoListReplyData &operator =(const TGetLabInfoListReplyData &other);
    bool operator ==(const TGetLabInfoListReplyData &other) const;
    bool operator !=(const TGetLabInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetLabInfoListReplyData)

#endif // TGETLABINFOLISTREPLYDATA_H
