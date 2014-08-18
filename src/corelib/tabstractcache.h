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

#ifndef TABSTRACTCACHE_H
#define TABSTRACTCACHE_H

class QDateTime;
class QString;

#include "tglobal.h"

#include <QVariant>

/*============================================================================
================================ TAbstractCache ==============================
============================================================================*/

class T_CORE_EXPORT TAbstractCache
{
public:
    explicit TAbstractCache();
    virtual ~TAbstractCache();
public:
    virtual QVariant data(const QString &operation, const QVariant &id = QVariant()) const = 0;
    virtual QDateTime lastRequestDateTime(const QString &operation, const QVariant &id = QVariant()) const = 0;
    virtual void removeData(const QString &operation, const QVariant &id = QVariant()) = 0;
    virtual void setData(const QString &operation, const QDateTime &requestDateTime,
                         const QVariant &data = QVariant()) = 0;
private:
    Q_DISABLE_COPY(TAbstractCache)
};

#endif // TABSTRACTCACHE_H
