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

#ifndef TEDITGROUPREQUESTDATA_H
#define TEDITGROUPREQUESTDATA_H

class TEditGroupRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditGroupRequestData =======================
============================================================================*/

class T_CORE_EXPORT TEditGroupRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditGroupRequestData)
public:
    explicit TEditGroupRequestData();
    TEditGroupRequestData(const TEditGroupRequestData &other);
    ~TEditGroupRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    QString name() const;
    void setId(quint64 id);
    void setName(const QString &name);
public:
    TEditGroupRequestData &operator =(const TEditGroupRequestData &other);
    bool operator ==(const TEditGroupRequestData &other) const;
    bool operator !=(const TEditGroupRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TEditGroupRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TEditGroupRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TEditGroupRequestData &data);
};

Q_DECLARE_METATYPE(TEditGroupRequestData)

#endif // TEDITGROUPREQUESTDATA_H
