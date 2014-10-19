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

#ifndef TDELETEINVITESREQUESTDATA_H
#define TDELETEINVITESREQUESTDATA_H

class TDeleteInvitesRequestDataPrivate;

class TIdList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteInvitesRequestData ===================
============================================================================*/

class T_CORE_EXPORT TDeleteInvitesRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteInvitesRequestData)
public:
    explicit TDeleteInvitesRequestData();
    TDeleteInvitesRequestData(const TDeleteInvitesRequestData &other);
    ~TDeleteInvitesRequestData();
public:
    void clear();
    TIdList ids() const;
    bool isValid() const;
    void setIds(const TIdList &ids);
public:
    TDeleteInvitesRequestData &operator =(const TDeleteInvitesRequestData &other);
    bool operator ==(const TDeleteInvitesRequestData &other) const;
    bool operator !=(const TDeleteInvitesRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TDeleteInvitesRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TDeleteInvitesRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteInvitesRequestData)

#endif // TDELETEINVITESREQUESTDATA_H
