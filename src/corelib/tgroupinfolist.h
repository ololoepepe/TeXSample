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

#ifndef TGROUPINFOLIST_H
#define TGROUPINFOLIST_H

#include "tglobal.h"
#include "tgroupinfo.h"

#include <QList>
#include <QMetaType>
#include <QStringList>
#include <QVariant>

/*============================================================================
================================ TGroupInfoList ==============================
============================================================================*/

class T_CORE_EXPORT TGroupInfoList : public QList<TGroupInfo>
{
public:
    using QList<TGroupInfo>::contains;
public:
    QStringList names() const;
public:
    bool contains(quint64 groupId) const;
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TGroupInfoList)

#endif // TGROUPINFOLIST_H
