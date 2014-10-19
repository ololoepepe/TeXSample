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

#ifndef TGENERATEINVITESREQUESTDATA_H
#define TGENERATEINVITESREQUESTDATA_H

class TGenerateInvitesRequestDataPrivate;

class TAccessLevel;
class TIdList;
class TServiceList;

class QDataStream;
class QDateTime;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGenerateInvitesRequestData =================
============================================================================*/

class T_CORE_EXPORT TGenerateInvitesRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGenerateInvitesRequestData)
public:
    explicit TGenerateInvitesRequestData();
    TGenerateInvitesRequestData(const TGenerateInvitesRequestData &other);
    ~TGenerateInvitesRequestData();
public:
    TAccessLevel accessLevel() const;
    void clear();
    quint16 count() const;
    QDateTime expirationDateTime() const;
    TIdList groups() const;
    bool isValid() const;
    TServiceList services() const;
    void setAccessLevel(const TAccessLevel &accessLevel);
    void setCount(quint16 count);
    void setExpirationDateTime(const QDateTime &dt);
    void setGroups(const TIdList &groups);
    void setServices(const TServiceList &services);
public:
    TGenerateInvitesRequestData &operator =(const TGenerateInvitesRequestData &other);
    bool operator ==(const TGenerateInvitesRequestData &other) const;
    bool operator !=(const TGenerateInvitesRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGenerateInvitesRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGenerateInvitesRequestData &data);
};

Q_DECLARE_METATYPE(TGenerateInvitesRequestData)

#endif // TGENERATEINVITESREQUESTDATA_H
