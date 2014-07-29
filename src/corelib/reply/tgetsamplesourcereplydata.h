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

#ifndef TGETSAMPLESOURCEREPLYDATA_H
#define TGETSAMPLESOURCEREPLYDATA_H

class TGetSampleSourceReplyDataPrivate;

class TTexProject;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleSourceReplyData ===================
============================================================================*/

class T_CORE_EXPORT TGetSampleSourceReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleSourceReplyData)
public:
    explicit TGetSampleSourceReplyData();
    TGetSampleSourceReplyData(const TGetSampleSourceReplyData &other);
    ~TGetSampleSourceReplyData();
public:
    TTexProject &project();
    const TTexProject &project() const;
    void setProject(const TTexProject &project);
public:
    TGetSampleSourceReplyData &operator =(const TGetSampleSourceReplyData &other);
    bool operator ==(const TGetSampleSourceReplyData &other) const;
    bool operator !=(const TGetSampleSourceReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleSourceReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleSourceReplyData &data);
};

Q_DECLARE_METATYPE(TGetSampleSourceReplyData)

#endif // TGETSAMPLESOURCEREPLYDATA_H
