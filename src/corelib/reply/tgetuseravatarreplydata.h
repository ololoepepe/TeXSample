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

#ifndef TGETUSERAVATARREPLYDATA_H
#define TGETUSERAVATARREPLYDATA_H

class TGetUserAvatarReplyDataPrivate;

class QDataStream;
class QDebug;
class QImage;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserAvatarReplyData =====================
============================================================================*/

class T_CORE_EXPORT TGetUserAvatarReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserAvatarReplyData)
public:
    explicit TGetUserAvatarReplyData();
    TGetUserAvatarReplyData(const TGetUserAvatarReplyData &other);
    ~TGetUserAvatarReplyData();
public:
    QImage avatar() const;
    void setAvatar(const QImage &avatar);
public:
    TGetUserAvatarReplyData &operator =(const TGetUserAvatarReplyData &other);
    bool operator ==(const TGetUserAvatarReplyData &other) const;
    bool operator !=(const TGetUserAvatarReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserAvatarReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserAvatarReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserAvatarReplyData)

#endif // TGETUSERAVATARREPLYDATA_H
