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

#ifndef TGETSERVERSTATEREQUESTDATA_H
#define TGETSERVERSTATEREQUESTDATA_H

class TGetServerStateRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetServerStateRequestData ==================
============================================================================*/

class T_CORE_EXPORT TGetServerStateRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetServerStateRequestData)
public:
    explicit TGetServerStateRequestData();
    TGetServerStateRequestData(const TGetServerStateRequestData &other);
    ~TGetServerStateRequestData();
public:
    TGetServerStateRequestData &operator =(const TGetServerStateRequestData &other);
    bool operator ==(const TGetServerStateRequestData &other) const;
    bool operator !=(const TGetServerStateRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetServerStateRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetServerStateRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetServerStateRequestData &data);
};

Q_DECLARE_METATYPE(TGetServerStateRequestData)

#endif // TGETSERVERSTATEREQUESTDATA_H
