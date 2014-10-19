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

#ifndef TGETLABDATAREPLYDATA_H
#define TGETLABDATAREPLYDATA_H

class TGetLabDataReplyDataPrivate;

class TLabData;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabDataReplyData ========================
============================================================================*/

class T_CORE_EXPORT TGetLabDataReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabDataReplyData)
public:
    explicit TGetLabDataReplyData();
    TGetLabDataReplyData(const TGetLabDataReplyData &other);
    ~TGetLabDataReplyData();
public:
    TLabData &data();
    const TLabData &data() const;
    void setData(const TLabData &data);
public:
    TGetLabDataReplyData &operator =(const TGetLabDataReplyData &other);
    bool operator ==(const TGetLabDataReplyData &other) const;
    bool operator !=(const TGetLabDataReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetLabDataReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetLabDataReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetLabDataReplyData &data);
};

Q_DECLARE_METATYPE(TGetLabDataReplyData)

#endif // TGETLABDATAREPLYDATA_H
