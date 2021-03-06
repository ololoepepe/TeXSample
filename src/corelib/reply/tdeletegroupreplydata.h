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

#ifndef TDELETEGROUPREPLYDATA_H
#define TDELETEGROUPREPLYDATA_H

class TDeleteGroupReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteGroupReplyData =======================
============================================================================*/

class T_CORE_EXPORT TDeleteGroupReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteGroupReplyData)
public:
    explicit TDeleteGroupReplyData();
    TDeleteGroupReplyData(const TDeleteGroupReplyData &other);
    ~TDeleteGroupReplyData();
public:
    TDeleteGroupReplyData &operator =(const TDeleteGroupReplyData &other);
    bool operator ==(const TDeleteGroupReplyData &other) const;
    bool operator !=(const TDeleteGroupReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TDeleteGroupReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TDeleteGroupReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TDeleteGroupReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteGroupReplyData)

#endif // TDELETEGROUPREPLYDATA_H
