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

#ifndef TDELETEUSERREPLYDATA_H
#define TDELETEUSERREPLYDATA_H

class TDeleteUserReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteUserReplyData ========================
============================================================================*/

class T_CORE_EXPORT TDeleteUserReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteUserReplyData)
public:
    explicit TDeleteUserReplyData();
    TDeleteUserReplyData(const TDeleteUserReplyData &other);
    ~TDeleteUserReplyData();
public:
    void setUserId(quint64 userId);
    quint64 userId() const;
public:
    TDeleteUserReplyData &operator =(const TDeleteUserReplyData &other);
    bool operator ==(const TDeleteUserReplyData &other) const;
    bool operator !=(const TDeleteUserReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TDeleteUserReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TDeleteUserReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TDeleteUserReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteUserReplyData)

#endif // TDELETEUSERREPLYDATA_H
