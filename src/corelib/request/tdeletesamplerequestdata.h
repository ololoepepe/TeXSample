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

#ifndef TDELETESAMPLEREQUESTDATA_H
#define TDELETESAMPLEREQUESTDATA_H

class TDeleteSampleRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteSampleRequestData ====================
============================================================================*/

class T_CORE_EXPORT TDeleteSampleRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteSampleRequestData)
public:
    explicit TDeleteSampleRequestData();
    TDeleteSampleRequestData(const TDeleteSampleRequestData &other);
    ~TDeleteSampleRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TDeleteSampleRequestData &operator =(const TDeleteSampleRequestData &other);
    bool operator ==(const TDeleteSampleRequestData &other) const;
    bool operator !=(const TDeleteSampleRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TDeleteSampleRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TDeleteSampleRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TDeleteSampleRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteSampleRequestData)

#endif // TDELETESAMPLEREQUESTDATA_H
