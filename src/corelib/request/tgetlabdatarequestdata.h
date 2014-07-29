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

#ifndef TGETLABDATAREQUESTDATA_H
#define TGETLABDATAREQUESTDATA_H

class TGetLabDataRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TGetLabDataRequestData ======================
============================================================================*/

class T_CORE_EXPORT TGetLabDataRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabDataRequestData)
public:
    explicit TGetLabDataRequestData();
    TGetLabDataRequestData(const TGetLabDataRequestData &other);
    ~TGetLabDataRequestData();
public:
    void clear();
    bool isValid() const;
    quint64 labId() const;
    BeQt::OSType os() const;
    void setLabId(quint64 id);
    void setOs(const BeQt::OSType os);
public:
    TGetLabDataRequestData &operator =(const TGetLabDataRequestData &other);
    bool operator ==(const TGetLabDataRequestData &other) const;
    bool operator !=(const TGetLabDataRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabDataRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabDataRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabDataRequestData &data);
};

Q_DECLARE_METATYPE(TGetLabDataRequestData)

#endif // TGETLABDATAREQUESTDATA_H
