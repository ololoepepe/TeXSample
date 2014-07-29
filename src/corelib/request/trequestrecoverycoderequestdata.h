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

#ifndef TREQUESTRECOVERYCODEREQUESTDATA_H
#define TREQUESTRECOVERYCODEREQUESTDATA_H

class TRequestRecoveryCodeRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRequestRecoveryCodeRequestData =============
============================================================================*/

class T_CORE_EXPORT TRequestRecoveryCodeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TRequestRecoveryCodeRequestData)
public:
    explicit TRequestRecoveryCodeRequestData();
    TRequestRecoveryCodeRequestData(const TRequestRecoveryCodeRequestData &other);
    ~TRequestRecoveryCodeRequestData();
public:
    void clear();
    QString email() const;
    bool isValid() const;
    void setEmail(const QString &email);
public:
    TRequestRecoveryCodeRequestData &operator =(const TRequestRecoveryCodeRequestData &other);
    bool operator ==(const TRequestRecoveryCodeRequestData &other) const;
    bool operator !=(const TRequestRecoveryCodeRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeRequestData &data);
};

Q_DECLARE_METATYPE(TRequestRecoveryCodeRequestData)

#endif // TREQUESTRECOVERYCODEREQUESTDATA_H
