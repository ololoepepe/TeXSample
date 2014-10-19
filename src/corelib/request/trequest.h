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

#ifndef TREQUEST_H
#define TREQUEST_H

class TRequestPrivate;

class QDataStream;
class QDateTime;
class QDebug;
class QLocale;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRequest ====================================
============================================================================*/

class T_CORE_EXPORT TRequest : public BBase
{
    B_DECLARE_PRIVATE(TRequest)
public:
    explicit TRequest();
    explicit TRequest(const QVariant &data);
    TRequest(const TRequest &other);
    ~TRequest();
public:
    bool cachingEnabled() const;
    void clear();
    QVariant data() const;
    bool isValid() const;
    QDateTime lastRequestDateTime() const;
    QLocale locale() const;
    void setCachingEnabled(bool enabled);
    void setData(const QVariant &data);
    void setLastRequestDateTime(const QDateTime &dt);
    void setLocale(const QLocale &locale);
public:
    TRequest &operator =(const TRequest &other);
    bool operator ==(const TRequest &other) const;
    bool operator !=(const TRequest &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TRequest &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TRequest &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TRequest &data);
};

Q_DECLARE_METATYPE(TRequest)

#endif // TREQUEST_H
