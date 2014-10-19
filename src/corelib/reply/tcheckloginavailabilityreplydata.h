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

#ifndef TCHECKLOGINAVAILABILITYREPLYDATA_H
#define TCHECKLOGINAVAILABILITYREPLYDATA_H

class TCheckLoginAvailabilityReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCheckLoginAvailabilityReplyData ============
============================================================================*/

class T_CORE_EXPORT TCheckLoginAvailabilityReplyData : public BBase
{
    B_DECLARE_PRIVATE(TCheckLoginAvailabilityReplyData)
public:
    explicit TCheckLoginAvailabilityReplyData();
    TCheckLoginAvailabilityReplyData(const TCheckLoginAvailabilityReplyData &other);
    ~TCheckLoginAvailabilityReplyData();
public:
    void setAvailable(bool available);
    bool available() const;
public:
    TCheckLoginAvailabilityReplyData &operator =(const TCheckLoginAvailabilityReplyData &other);
    bool operator ==(const TCheckLoginAvailabilityReplyData &other) const;
    bool operator !=(const TCheckLoginAvailabilityReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityReplyData &data);
};

Q_DECLARE_METATYPE(TCheckLoginAvailabilityReplyData)

#endif // TCHECKLOGINAVAILABILITYREPLYDATA_H
