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

#ifndef TLABDATAINFO_H
#define TLABDATAINFO_H

class TLabDataInfoPrivate;

class TLabType;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TLabDataInfo ================================
============================================================================*/

class T_CORE_EXPORT TLabDataInfo : public BBase
{
    B_DECLARE_PRIVATE(TLabDataInfo)
public:
    explicit TLabDataInfo();
    TLabDataInfo(const TLabDataInfo &other);
    ~TLabDataInfo();
public:
    void clear();
    bool isValid() const;
    BeQt::OSType os() const;
    void setOs(BeQt::OSType os);
    void setSize(int size);
    void setType(const TLabType &type);
    int size() const;
    TLabType type() const;
public:
    TLabDataInfo &operator =(const TLabDataInfo &other);
    bool operator ==(const TLabDataInfo &other) const;
    bool operator !=(const TLabDataInfo &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TLabDataInfo &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TLabDataInfo &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TLabDataInfo &data);
};

Q_DECLARE_METATYPE(TLabDataInfo)

#endif // TLABDATAINFO_H
