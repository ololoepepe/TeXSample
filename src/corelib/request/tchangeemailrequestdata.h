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

#ifndef TCHANGEEMAILREQUESTDATA_H
#define TCHANGEEMAILREQUESTDATA_H

class TChangeEmailRequestDataPrivate;

class QByteArray;
class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TChangeEmailRequestData =====================
============================================================================*/

class T_CORE_EXPORT TChangeEmailRequestData : public BBase
{
    B_DECLARE_PRIVATE(TChangeEmailRequestData)
public:
    explicit TChangeEmailRequestData();
    TChangeEmailRequestData(const TChangeEmailRequestData &other);
    ~TChangeEmailRequestData();
public:
    void clear();
    QString email() const;
    bool isValid() const;
    QByteArray password() const;
    void setEmail(const QString &email);
    void setPassword(const QString &password);
public:
    TChangeEmailRequestData &operator =(const TChangeEmailRequestData &other);
    bool operator ==(const TChangeEmailRequestData &other) const;
    bool operator !=(const TChangeEmailRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TChangeEmailRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TChangeEmailRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TChangeEmailRequestData &data);
};

Q_DECLARE_METATYPE(TChangeEmailRequestData)

#endif // TCHANGEEMAILREQUESTDATA_H
