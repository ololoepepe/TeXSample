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

#ifndef TGETINVITEINFOLISTREPLYDATA_H
#define TGETINVITEINFOLISTREPLYDATA_H

class TGetInviteInfoListReplyDataPrivate;

class TIdList;
class TInviteInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetInviteInfoListReplyData =================
============================================================================*/

class T_CORE_EXPORT TGetInviteInfoListReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetInviteInfoListReplyData)
public:
    explicit TGetInviteInfoListReplyData();
    TGetInviteInfoListReplyData(const TGetInviteInfoListReplyData &other);
    ~TGetInviteInfoListReplyData();
public:
    TIdList deletedInvites() const;
    TInviteInfoList newInvites() const;
    void setDeletedInvites(const TIdList &deletedInvites);
    void setNewInvites(const TInviteInfoList &newInvites);
public:
    TGetInviteInfoListReplyData &operator =(const TGetInviteInfoListReplyData &other);
    bool operator ==(const TGetInviteInfoListReplyData &other) const;
    bool operator !=(const TGetInviteInfoListReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetInviteInfoListReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetInviteInfoListReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetInviteInfoListReplyData &data);
};

Q_DECLARE_METATYPE(TGetInviteInfoListReplyData)

#endif // TGETINVITEINFOLISTREPLYDATA_H
