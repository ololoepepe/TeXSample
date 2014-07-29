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

#ifndef TAUTHORIZEREQUESTDATA_H
#define TAUTHORIZEREQUESTDATA_H

class TAuthorizeRequestDataPrivate;

class TClientInfo;

class QByteArray;
class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAuthorizeRequestData =======================
============================================================================*/

class T_CORE_EXPORT TAuthorizeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAuthorizeRequestData)
public:
    explicit TAuthorizeRequestData();
    TAuthorizeRequestData(const TAuthorizeRequestData &other);
    ~TAuthorizeRequestData();
public:
    void clear();
    TClientInfo clientInfo() const;
    QString identifier() const;
    bool isValid() const;
    QByteArray password() const;
    void setClientInfo(const TClientInfo &info);
    void setIdentifier(const QString &identifier);
    void setPassword(const QByteArray &password);
public:
    TAuthorizeRequestData &operator =(const TAuthorizeRequestData &other);
    bool operator ==(const TAuthorizeRequestData &other) const;
    bool operator !=(const TAuthorizeRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAuthorizeRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAuthorizeRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAuthorizeRequestData &data);
};

Q_DECLARE_METATYPE(TAuthorizeRequestData)

#endif // TAUTHORIZEREQUESTDATA_H
