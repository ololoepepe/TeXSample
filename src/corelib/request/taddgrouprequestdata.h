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

#ifndef TADDGROUPREQUESTDATA_H
#define TADDGROUPREQUESTDATA_H

class TAddGroupRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddGroupRequestData ========================
============================================================================*/

class T_CORE_EXPORT TAddGroupRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddGroupRequestData)
public:
    explicit TAddGroupRequestData();
    TAddGroupRequestData(const TAddGroupRequestData &other);
    ~TAddGroupRequestData();
public:
    void clear();
    bool isValid() const;
    QString name() const;
    void setName(const QString &name);
public:
    TAddGroupRequestData &operator =(const TAddGroupRequestData &other);
    bool operator ==(const TAddGroupRequestData &other) const;
    bool operator !=(const TAddGroupRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddGroupRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddGroupRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAddGroupRequestData &data);
};

Q_DECLARE_METATYPE(TAddGroupRequestData)

#endif // TADDGROUPREQUESTDATA_H
