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

#ifndef TCHECKEMAILAVAILABILITYREQUESTDATA_H
#define TCHECKEMAILAVAILABILITYREQUESTDATA_H

class TCheckEmailAvailabilityRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckEmailAvailabilityRequestData ==========
============================================================================*/

class T_CORE_EXPORT TCheckEmailAvailabilityRequestData : public BBase
{
    B_DECLARE_PRIVATE(TCheckEmailAvailabilityRequestData)
public:
    explicit TCheckEmailAvailabilityRequestData();
    TCheckEmailAvailabilityRequestData(const TCheckEmailAvailabilityRequestData &other);
    ~TCheckEmailAvailabilityRequestData();
public:
    void clear();
    QString email() const;
    bool isValid() const;
    void setEmail(const QString &email);
public:
    TCheckEmailAvailabilityRequestData &operator =(const TCheckEmailAvailabilityRequestData &other);
    bool operator ==(const TCheckEmailAvailabilityRequestData &other) const;
    bool operator !=(const TCheckEmailAvailabilityRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TCheckEmailAvailabilityRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TCheckEmailAvailabilityRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TCheckEmailAvailabilityRequestData &data);
};

Q_DECLARE_METATYPE(TCheckEmailAvailabilityRequestData)

#endif // TCHECKEMAILAVAILABILITYREQUESTDATA_H
