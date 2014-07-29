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

#ifndef TDELETEINVITESREPLYDATA_H
#define TDELETEINVITESREPLYDATA_H

class TDeleteInvitesReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteInvitesReplyData =====================
============================================================================*/

class T_CORE_EXPORT TDeleteInvitesReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteInvitesReplyData)
public:
    explicit TDeleteInvitesReplyData();
    TDeleteInvitesReplyData(const TDeleteInvitesReplyData &other);
    ~TDeleteInvitesReplyData();
public:
    quint32 count() const;
    void setCount(quint32 count);
public:
    TDeleteInvitesReplyData &operator =(const TDeleteInvitesReplyData &other);
    bool operator ==(const TDeleteInvitesReplyData &other) const;
    bool operator !=(const TDeleteInvitesReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteInvitesReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteInvitesReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteInvitesReplyData)

#endif // TDELETEINVITESREPLYDATA_H
