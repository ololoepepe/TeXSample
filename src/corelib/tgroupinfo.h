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

#ifndef TGROUPINFO_H
#define TGROUPINFO_H

class TGroupInfoPrivate;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGroupInfo ==================================
============================================================================*/

class T_CORE_EXPORT TGroupInfo : public BBase
{
    B_DECLARE_PRIVATE(TGroupInfo)
public:
    explicit TGroupInfo();
    TGroupInfo(const TGroupInfo &other);
    ~TGroupInfo();
public:
    void clear();
    QDateTime creationDateTime() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    QString name() const;
    quint64 ownerId() const;
    QString ownerLogin() const;
    void setCreationDateTime(const QDateTime &dt);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setName(const QString &name);
    void setOwnerId(quint64 ownerId);
    void setOwnerLogin(const QString &login);
public:
    TGroupInfo &operator =(const TGroupInfo &other);
    bool operator ==(const TGroupInfo &other) const;
    bool operator !=(const TGroupInfo &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGroupInfo &info);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGroupInfo &info);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGroupInfo &info);
};

Q_DECLARE_METATYPE(TGroupInfo)

#endif // TGROUPINFO_H
