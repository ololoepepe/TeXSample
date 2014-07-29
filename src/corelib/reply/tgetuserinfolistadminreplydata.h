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

#ifndef TGETUSERINFOLISTADMINREPLYDATA_H
#define TGETUSERINFOLISTADMINREPLYDATA_H

class TGetUserInfoListAdminReplyDataPrivate;

class TIdList;
class TUserInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserInfoListAdminReplyData ==============
============================================================================*/

class T_CORE_EXPORT TGetUserInfoListAdminReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserInfoListAdminReplyData)
public:
    explicit TGetUserInfoListAdminReplyData();
    TGetUserInfoListAdminReplyData(const TGetUserInfoListAdminReplyData &other);
    ~TGetUserInfoListAdminReplyData();
public:
    TIdList deletedUsers() const;
    TUserInfoList newUsers() const;
    void setDeletedUsers(const TIdList &deletedUsers);
    void setNewUsers(const TUserInfoList &newUsers);
public:
    TGetUserInfoListAdminReplyData &operator =(const TGetUserInfoListAdminReplyData &other);
    bool operator ==(const TGetUserInfoListAdminReplyData &other) const;
    bool operator !=(const TGetUserInfoListAdminReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserInfoListAdminReplyData)

#endif // TGETUSERINFOLISTADMINREPLYDATA_H
