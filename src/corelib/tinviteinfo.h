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

#ifndef TINVITEINFO_H
#define TINVITEINFO_H

class TInviteInfoPrivate;

class TIdList;
class TServiceList;

class BUuid;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TInviteInfo =================================
============================================================================*/

class T_CORE_EXPORT TInviteInfo : public BBase
{
    B_DECLARE_PRIVATE(TInviteInfo)
public:
    explicit TInviteInfo();
    TInviteInfo(const TInviteInfo &other);
    ~TInviteInfo();
public:
    void clear();
    BUuid code() const;
    QDateTime creationDateTime() const;
    QDateTime expirationDateTime() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    quint64 ownerId() const;
    QString ownerLogin() const;
    TServiceList services() const;
    void setCode(const BUuid &code);
    void setCreationDateTime(const QDateTime &dt);
    void setExpirationDateTime(const QDateTime &dt);
    void setGroups(const TIdList &groups);
    void setId(quint64 id);
    void setOwnerId(quint64 id);
    void setOwnerLogin(const QString &login);
    void setServices(const TServiceList &services);
public:
    TInviteInfo &operator =(const TInviteInfo &other);
    bool operator ==(const TInviteInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TInviteInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TInviteInfo &info);
    friend QDebug operator <<(QDebug dbg, const TInviteInfo &info);
};

Q_DECLARE_METATYPE(TInviteInfo)

#endif // TINVITEINFO_H
