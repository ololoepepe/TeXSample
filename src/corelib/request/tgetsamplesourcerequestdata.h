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

#ifndef TGETSAMPLISOURCEREQUESTDATA_H
#define TGETSAMPLISOURCEREQUESTDATA_H

class TGetSampleSourceRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSampleSourceRequestData =================
============================================================================*/

class T_CORE_EXPORT TGetSampleSourceRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSampleSourceRequestData)
public:
    explicit TGetSampleSourceRequestData();
    TGetSampleSourceRequestData(const TGetSampleSourceRequestData &other);
    ~TGetSampleSourceRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TGetSampleSourceRequestData &operator =(const TGetSampleSourceRequestData &other);
    bool operator ==(const TGetSampleSourceRequestData &other) const;
    bool operator !=(const TGetSampleSourceRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSampleSourceRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSampleSourceRequestData &data);
};

Q_DECLARE_METATYPE(TGetSampleSourceRequestData)

#endif // TGETSAMPLISOURCEREQUESTDATA_H
