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

#ifndef TCONFIRMREGISTRATIONREQUESTDATA_H
#define TCONFIRMREGISTRATIONREQUESTDATA_H

class TConfirmRegistrationRequestDataPrivate;

class BUuid;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TConfirmRegistrationRequestData =============
============================================================================*/

class T_CORE_EXPORT TConfirmRegistrationRequestData : public BBase
{
    B_DECLARE_PRIVATE(TConfirmRegistrationRequestData)
public:
    explicit TConfirmRegistrationRequestData();
    TConfirmRegistrationRequestData(const TConfirmRegistrationRequestData &other);
    ~TConfirmRegistrationRequestData();
public:
    void clear();
    BUuid confirmationCode() const;
    bool isValid() const;
    void setConfirmationCode(const BUuid &code);
public:
    TConfirmRegistrationRequestData &operator =(const TConfirmRegistrationRequestData &other);
    bool operator ==(const TConfirmRegistrationRequestData &other) const;
    bool operator !=(const TConfirmRegistrationRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TConfirmRegistrationRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TConfirmRegistrationRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TConfirmRegistrationRequestData &data);
};

Q_DECLARE_METATYPE(TConfirmRegistrationRequestData)

#endif // TCONFIRMREGISTRATIONREQUESTDATA_H
