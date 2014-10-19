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

#ifndef TCHECKLOGINAVAILABILITYREQUESTDATA_H
#define TCHECKLOGINAVAILABILITYREQUESTDATA_H

class TCheckLoginAvailabilityRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckLoginAvailabilityRequestData ==========
============================================================================*/

class T_CORE_EXPORT TCheckLoginAvailabilityRequestData : public BBase
{
    B_DECLARE_PRIVATE(TCheckLoginAvailabilityRequestData)
public:
    explicit TCheckLoginAvailabilityRequestData();
    TCheckLoginAvailabilityRequestData(const TCheckLoginAvailabilityRequestData &other);
    ~TCheckLoginAvailabilityRequestData();
public:
    void clear();
    bool isValid() const;
    QString login() const;
    void setLogin(const QString &login);
public:
    TCheckLoginAvailabilityRequestData &operator =(const TCheckLoginAvailabilityRequestData &other);
    bool operator ==(const TCheckLoginAvailabilityRequestData &other) const;
    bool operator !=(const TCheckLoginAvailabilityRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityRequestData &data);
};

Q_DECLARE_METATYPE(TCheckLoginAvailabilityRequestData)

#endif // TCHECKLOGINAVAILABILITYREQUESTDATA_H
