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

#ifndef TGETSAMPLEINFOLISTREPLYDATA_H
#define TGETSAMPLEINFOLISTREPLYDATA_H

class TGetSampleInfoListReplyDataPrivate;

class TIdList;
class TSampleInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleInfoListReplyData =================
============================================================================*/

class T_CORE_EXPORT TGetSampleInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleInfoListReplyData)
public:
    explicit TGetSampleInfoListReplyData();
    TGetSampleInfoListReplyData(const TGetSampleInfoListReplyData &other);
    ~TGetSampleInfoListReplyData();
public:
    TIdList deletedSamples() const;
    TSampleInfoList newSamples() const;
    void setDeletedSamples(const TIdList &deletedSamples);
    void setNewSamples(const TSampleInfoList &newSamples);
public:
    TGetSampleInfoListReplyData &operator =(const TGetSampleInfoListReplyData &other);
    bool operator ==(const TGetSampleInfoListReplyData &other) const;
    bool operator !=(const TGetSampleInfoListReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetSampleInfoListReplyData)

#endif // TGETSAMPLEINFOLISTREPLYDATA_H
