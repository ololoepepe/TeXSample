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

#ifndef TDELETEGROUPREQUESTDATA_H
#define TDELETEGROUPREQUESTDATA_H

class TDeleteGroupRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteGroupRequestData =====================
============================================================================*/

class T_CORE_EXPORT TDeleteGroupRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteGroupRequestData)
public:
    explicit TDeleteGroupRequestData();
    TDeleteGroupRequestData(const TDeleteGroupRequestData &other);
    ~TDeleteGroupRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TDeleteGroupRequestData &operator =(const TDeleteGroupRequestData &other);
    bool operator ==(const TDeleteGroupRequestData &other) const;
    bool operator !=(const TDeleteGroupRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteGroupRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteGroupRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteGroupRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteGroupRequestData)

#endif // TDELETEGROUPREQUESTDATA_H
