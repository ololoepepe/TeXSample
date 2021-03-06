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

#ifndef TDELETEUSERREQUESTDATA_H
#define TDELETEUSERREQUESTDATA_H

class TDeleteUserRequestDataPrivate;

class TUserIdentifier;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteUserRequestData ======================
============================================================================*/

class T_CORE_EXPORT TDeleteUserRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteUserRequestData)
public:
    explicit TDeleteUserRequestData();
    TDeleteUserRequestData(const TDeleteUserRequestData &other);
    ~TDeleteUserRequestData();
public:
    void clear();
    TUserIdentifier identifier() const;
    bool isValid() const;
    void setIdentifier(const TUserIdentifier &identifier);
public:
    TDeleteUserRequestData &operator =(const TDeleteUserRequestData &other);
    bool operator ==(const TDeleteUserRequestData &other) const;
    bool operator !=(const TDeleteUserRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TDeleteUserRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TDeleteUserRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TDeleteUserRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteUserRequestData)

#endif // TDELETEUSERREQUESTDATA_H
