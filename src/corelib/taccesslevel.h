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

#ifndef TACCESSLEVEL_H
#define TACCESSLEVEL_H

class TAccessLevelPrivate;

class QDataStream;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>
#include <QList>

/*============================================================================
================================ TAccessLevel ================================
============================================================================*/

class T_CORE_EXPORT TAccessLevel : public BBase
{
    B_DECLARE_PRIVATE(TAccessLevel)
    Q_DECLARE_TR_FUNCTIONS(TAccessLevel)
public:
    enum AccessLevel
    {
        NoLevel = 0,
        UserLevel = 10,
        ModeratorLevel = 100,
        AdminLevel = 1000,
        SuperuserLevel = 10000
    };
public:
    static QString accessLevelToString(AccessLevel lvl, bool singular = true);
    static QString accessLevelToStringNoTr(AccessLevel lvl, bool singular = true);
    static QList<TAccessLevel> allAccessLevels(bool includeNoLevel = false);
public:
    TAccessLevel(int lvl = NoLevel);
    TAccessLevel(const TAccessLevel &other);
    ~TAccessLevel();
public:
    bool isValid() const;
    QString toString() const;
    QString toStringNoTr() const;
public:
    TAccessLevel &operator =(const TAccessLevel &other);
    TAccessLevel &operator =(int lvl);
    bool operator ==(const TAccessLevel &other) const;
    bool operator !=(const TAccessLevel &other) const;
    bool operator <(const TAccessLevel &other) const;
    bool operator <=(const TAccessLevel &other) const;
    bool operator >(const TAccessLevel &other) const;
    bool operator >=(const TAccessLevel &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAccessLevel &lvl);
    friend QDataStream &operator >>(QDataStream &stream, TAccessLevel &lvl);
    friend QDebug operator <<(QDebug dbg, const TAccessLevel &lvl);
};

Q_DECLARE_METATYPE(TAccessLevel)

#endif // TACCESSLEVEL_H
