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

#ifndef TCONFIRMEMAILCHANGEREQUESTDATA_H
#define TCONFIRMEMAILCHANGEREQUESTDATA_H

class TConfirmEmailChangeRequestDataPrivate;

class BUuid;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TConfirmEmailChangeRequestData ==============
============================================================================*/

class T_CORE_EXPORT TConfirmEmailChangeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TConfirmEmailChangeRequestData)
public:
    explicit TConfirmEmailChangeRequestData();
    TConfirmEmailChangeRequestData(const TConfirmEmailChangeRequestData &other);
    ~TConfirmEmailChangeRequestData();
public:
    void clear();
    BUuid confirmationCode() const;
    bool isValid() const;
    void setConfirmationCode(const BUuid &code);
public:
    TConfirmEmailChangeRequestData &operator =(const TConfirmEmailChangeRequestData &other);
    bool operator ==(const TConfirmEmailChangeRequestData &other) const;
    bool operator !=(const TConfirmEmailChangeRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TConfirmEmailChangeRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TConfirmEmailChangeRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TConfirmEmailChangeRequestData &data);
};

Q_DECLARE_METATYPE(TConfirmEmailChangeRequestData)

#endif // TCONFIRMEMAILCHANGEREQUESTDATA_H