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

#ifndef TDELETELABREQUESTDATA_H
#define TDELETELABREQUESTDATA_H

class TDeleteLabRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteLabRequestData =======================
============================================================================*/

class T_CORE_EXPORT TDeleteLabRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteLabRequestData)
public:
    explicit TDeleteLabRequestData();
    TDeleteLabRequestData(const TDeleteLabRequestData &other);
    ~TDeleteLabRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TDeleteLabRequestData &operator =(const TDeleteLabRequestData &other);
    bool operator ==(const TDeleteLabRequestData &other) const;
    bool operator !=(const TDeleteLabRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TDeleteLabRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TDeleteLabRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TDeleteLabRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteLabRequestData)

#endif // TDELETELABREQUESTDATA_H
