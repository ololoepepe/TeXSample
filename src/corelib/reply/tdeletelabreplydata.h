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

#ifndef TDELETELABREPLYDATA_H
#define TDELETELABREPLYDATA_H

class TDeleteLabReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteLabReplyData =========================
============================================================================*/

class T_CORE_EXPORT TDeleteLabReplyData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteLabReplyData)
public:
    explicit TDeleteLabReplyData();
    TDeleteLabReplyData(const TDeleteLabReplyData &other);
    ~TDeleteLabReplyData();
public:
    TDeleteLabReplyData &operator =(const TDeleteLabReplyData &other);
    bool operator ==(const TDeleteLabReplyData &other) const;
    bool operator !=(const TDeleteLabReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteLabReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteLabReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteLabReplyData &data);
};

Q_DECLARE_METATYPE(TDeleteLabReplyData)

#endif // TDELETELABREPLYDATA_H
