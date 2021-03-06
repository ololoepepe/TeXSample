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

#include "tgroupinfolist.h"

#include "tgroupinfo.h"

#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

/*============================================================================
================================ TGroupInfoList ==============================
============================================================================*/

/*============================== Public methods ============================*/

QStringList TGroupInfoList::names() const
{
    QStringList sl;
    foreach (const TGroupInfo &info, *this)
        sl << info.name();
    return sl;
}

/*============================== Public methods ============================*/

bool TGroupInfoList::contains(quint64 groupId) const
{
    foreach (const TGroupInfo &gi, *this) {
        if (gi.id() == groupId)
            return true;
    }
    return false;
}

/*============================== Public operators ==========================*/

TGroupInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
