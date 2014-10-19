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

#ifndef TGENERATEINVITESREPLYDATA_H
#define TGENERATEINVITESREPLYDATA_H

class TGenerateInvitesReplyDataPrivate;

class TInviteInfoList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGenerateInvitesReplyData ===================
============================================================================*/

class T_CORE_EXPORT TGenerateInvitesReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGenerateInvitesReplyData)
public:
    explicit TGenerateInvitesReplyData();
    TGenerateInvitesReplyData(const TGenerateInvitesReplyData &other);
    ~TGenerateInvitesReplyData();
public:
    TInviteInfoList generatedInvites() const;
    void setGeneratedInvites(const TInviteInfoList &generatedInvites);
public:
    TGenerateInvitesReplyData &operator =(const TGenerateInvitesReplyData &other);
    bool operator ==(const TGenerateInvitesReplyData &other) const;
    bool operator !=(const TGenerateInvitesReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGenerateInvitesReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGenerateInvitesReplyData &data);
};

Q_DECLARE_METATYPE(TGenerateInvitesReplyData)

#endif // TGENERATEINVITESREPLYDATA_H
