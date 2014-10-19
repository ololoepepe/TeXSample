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

#ifndef TUSERIDENTIFIER_H
#define TUSERIDENTIFIER_H

class TUserIdentifierPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TUserIdentifier =============================
============================================================================*/

class T_CORE_EXPORT TUserIdentifier : public BBase
{
    B_DECLARE_PRIVATE(TUserIdentifier)
public:
    explicit TUserIdentifier();
    TUserIdentifier(quint64 id);
    TUserIdentifier(const QString &login);
    TUserIdentifier(const TUserIdentifier &other);
    ~TUserIdentifier();
public:
    enum Type
    {
        NoType = 0,
        IdType,
        LoginType
    };
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    QString login() const;
    void setId(quint64 id);
    void setLogin(const QString &login);
    Type type() const;
public:
    TUserIdentifier &operator =(const TUserIdentifier &other);
    bool operator ==(const TUserIdentifier &other) const;
    bool operator !=(const TUserIdentifier &other) const;
    operator QVariant() const;
    operator quint64() const;
    operator QString() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TUserIdentifier &identificator);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TUserIdentifier &identificator);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TUserIdentifier &identificator);
};

Q_DECLARE_METATYPE(TUserIdentifier)

#endif // TUSERIDENTIFIER_H

