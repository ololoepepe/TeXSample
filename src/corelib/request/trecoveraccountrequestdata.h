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

#ifndef TRECOVERACCOUNTREQUESTDATA_H
#define TRECOVERACCOUNTREQUESTDATA_H

class TRecoverAccountRequestDataPrivate;

class BUuid;

class QByteArray;
class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRecoverAccountRequestData ==================
============================================================================*/

class T_CORE_EXPORT TRecoverAccountRequestData : public BBase
{
    B_DECLARE_PRIVATE(TRecoverAccountRequestData)
public:
    explicit TRecoverAccountRequestData();
    TRecoverAccountRequestData(const TRecoverAccountRequestData &other);
    ~TRecoverAccountRequestData();
public:
    void clear();
    bool isValid() const;
    QByteArray password() const;
    BUuid recoveryCode() const;
    void setPassword(const QByteArray &password);
    void setRecoveryCode(const BUuid &code);
public:
    TRecoverAccountRequestData &operator =(const TRecoverAccountRequestData &other);
    bool operator ==(const TRecoverAccountRequestData &other) const;
    bool operator !=(const TRecoverAccountRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRecoverAccountRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRecoverAccountRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TRecoverAccountRequestData &data);
};

Q_DECLARE_METATYPE(TRecoverAccountRequestData)

#endif // TRECOVERACCOUNTREQUESTDATA_H
