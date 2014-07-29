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

#ifndef TLABTYPE_H
#define TLABTYPE_H

class TLabTypePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TLabType ====================================
============================================================================*/

class T_CORE_EXPORT TLabType : public BBase
{
    B_DECLARE_PRIVATE(TLabType)
    Q_DECLARE_TR_FUNCTIONS(TLabType)
public:
    enum LabType
    {
         NoType = 0,
         DesktopApplication,
         WebApplication,
         Url
    };
public:
    static QString labTypeToString(LabType type, bool singular = true);
    static QString labTypeToStringNoTr(LabType type, bool singular = true);
public:
    TLabType(int type = NoType);
    TLabType(const TLabType &other);
    ~TLabType();
public:
    bool isValid() const;
    QString toString() const;
    QString toStringNoTr() const;
public:
    TLabType &operator =(const TLabType &other);
    TLabType &operator =(int type);
    bool operator ==(const TLabType &other) const;
    bool operator !=(const TLabType &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabType &type);
    friend QDataStream &operator >>(QDataStream &stream, TLabType &type);
    friend QDebug operator <<(QDebug dbg, const TLabType &type);
};

Q_DECLARE_METATYPE(TLabType)

#endif // TLABTYPE_H
