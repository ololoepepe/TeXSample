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

#ifndef TLABAPPLICATION_H
#define TLABAPPLICATION_H

class TLabApplicationPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>
#include <QStringList>

/*============================================================================
================================ TLabApplication =============================
============================================================================*/

class T_CORE_EXPORT TLabApplication : BBase
{
    B_DECLARE_PRIVATE(TLabApplication)
public:
    explicit TLabApplication();
    TLabApplication(const TLabApplication &other);
    ~TLabApplication();
public:
    void clear();
    bool isValid() const;
    bool load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames = QStringList());
    bool mayBeExecutable() const;
    BeQt::OSType os() const;
    bool save(const QString &dir) const;
    void setOsType(BeQt::OSType os);
    int size() const;
public:
    TLabApplication &operator =(const TLabApplication &other);
    bool operator ==(const TLabApplication &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabApplication &project);
    friend QDataStream &operator >>(QDataStream &stream, TLabApplication &project);
    friend QDebug operator <<(QDebug dbg, const TLabApplication &project);
};

Q_DECLARE_METATYPE(TLabApplication)

#endif // TLABAPPLICATION_H
