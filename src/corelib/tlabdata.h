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

#ifndef TLABDATA_H
#define TLABDATA_H

class TLabDataPrivate;

class TLabApplication;
class TLabType;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TLabData ====================================
============================================================================*/

class T_CORE_EXPORT TLabData : public BBase
{
    B_DECLARE_PRIVATE(TLabData)
public:
    explicit TLabData();
    TLabData(const TLabData &other);
    ~TLabData();
public:
    TLabApplication &application();
    const TLabApplication &application() const;
    void clear();
    bool isValid() const;
    BeQt::OSType os() const;
    void setApplication(const TLabApplication &application);
    void setUrl(const QString &url);
    int size() const;
    TLabType type() const;
    QString url() const;
public:
    TLabData &operator =(const TLabData &other);
    bool operator ==(const TLabData &other) const;
    bool operator !=(const TLabData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabData &data);
    friend QDataStream &operator >>(QDataStream &stream, TLabData &data);
    friend QDebug operator <<(QDebug dbg, const TLabData &data);
};

Q_DECLARE_METATYPE(TLabData)

#endif // TLABDATA_H
