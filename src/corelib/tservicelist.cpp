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

#include "tservicelist.h"

#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

/*============================================================================
================================ TServiceList ================================
============================================================================*/

/*============================== Static public methods =====================*/

TServiceList TServiceList::allServices(bool includeNoService)
{
    TServiceList list;
    if (includeNoService)
        list << TService::NoService;
    list << TService::TexsampleService;
    list << TService::CloudlabService;
    return list;
}

/*============================== Public methods ============================*/

QString TServiceList::toString(const QString &separator) const
{
    return toStringList().join(separator);
}

QStringList TServiceList::toStringList() const
{
    QStringList sl;
    foreach (const TService &s, *this)
        sl << s.toString();
    return sl;
}

QStringList TServiceList::toStringListNoTr() const
{
    QStringList sl;
    foreach (const TService &s, *this)
        sl << s.toStringNoTr();
    return sl;
}

QString TServiceList::toStringNoTr(const QString &separator) const
{
    return toStringListNoTr().join(separator);
}

/*============================== Public operators ==========================*/

TServiceList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
