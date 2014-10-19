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

#ifndef TSERVICE_H
#define TSERVICE_H

class TServicePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TService ====================================
============================================================================*/

class T_CORE_EXPORT TService : public BBase
{
    B_DECLARE_PRIVATE(TService)
    Q_DECLARE_TR_FUNCTIONS(TService)
public:
    enum Service
    {
        NoService = 0,
        TexsampleService,
        CloudlabService
    };
public:
    static QString serviceToString(Service srv);
    static QString serviceToStringNoTr(Service srv);
public:
    TService(int srv = NoService);
    TService(const TService &other);
    ~TService();
public:
    QString toString() const;
    QString toStringNoTr() const;
public:
    TService &operator =(const TService &other);
    TService &operator =(int srv);
    bool operator ==(const TService &other) const;
    bool operator !=(const TService &other) const;
    operator QVariant() const;
    operator int() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TService &srv);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TService &srv);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TService &srv);
};

Q_DECLARE_METATYPE(TService)

#endif // TSERVICE_H
