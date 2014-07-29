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

#ifndef TSAMPLETYPE_H
#define TSAMPLETYPE_H

class TSampleTypePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TSampleType =================================
============================================================================*/

class T_CORE_EXPORT TSampleType : public BBase
{
    B_DECLARE_PRIVATE(TSampleType)
    Q_DECLARE_TR_FUNCTIONS(TSampleType)
public:
    enum SampleType
    {
         Unverified = 0,
         Approved = 10,
         Rejected = 100
    };
public:
    static QString sampleTypeToString(SampleType type, bool singular = true);
    static QString sampleTypeToStringNoTr(SampleType type, bool singular = true);
public:
    TSampleType(int type = Unverified);
    TSampleType(const TSampleType &other);
    ~TSampleType();
public:
    QString toString() const;
    QString toStringNoTr() const;
public:
    TSampleType &operator =(const TSampleType &other);
    TSampleType &operator =(int type);
    bool operator ==(const TSampleType &other) const;
    bool operator !=(const TSampleType &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSampleType &type);
    friend QDataStream &operator >>(QDataStream &stream, TSampleType &type);
    friend QDebug operator <<(QDebug dbg, const TSampleType &type);
};

Q_DECLARE_METATYPE(TSampleType)

#endif // TSAMPLETYPE_H
