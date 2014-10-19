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

#ifndef TGETSELFINFOREQUESTDATA_H
#define TGETSELFINFOREQUESTDATA_H

class TGetSelfInfoRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSelfInfoRequestData =====================
============================================================================*/

class T_CORE_EXPORT TGetSelfInfoRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSelfInfoRequestData)
public:
    explicit TGetSelfInfoRequestData();
    TGetSelfInfoRequestData(const TGetSelfInfoRequestData &other);
    ~TGetSelfInfoRequestData();
public:
    TGetSelfInfoRequestData &operator =(const TGetSelfInfoRequestData &other);
    bool operator ==(const TGetSelfInfoRequestData &other) const;
    bool operator !=(const TGetSelfInfoRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetSelfInfoRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetSelfInfoRequestData &data);
};

Q_DECLARE_METATYPE(TGetSelfInfoRequestData)

#endif // TGETSELFINFOREQUESTDATA_H
