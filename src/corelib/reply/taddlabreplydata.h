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

#ifndef TADDLABREPLYDATA_H
#define TADDLABREPLYDATA_H

class TAddLabReplyDataPrivate;

class TLabInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddLabReplyData ============================
============================================================================*/

class T_CORE_EXPORT TAddLabReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddLabReplyData)
public:
    explicit TAddLabReplyData();
    TAddLabReplyData(const TAddLabReplyData &other);
    ~TAddLabReplyData();
public:
    TLabInfo labInfo() const;
    void setLabInfo(const TLabInfo &info);
public:
    TAddLabReplyData &operator =(const TAddLabReplyData &other);
    bool operator ==(const TAddLabReplyData &other) const;
    bool operator !=(const TAddLabReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TAddLabReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TAddLabReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TAddLabReplyData &data);
};

Q_DECLARE_METATYPE(TAddLabReplyData)

#endif // TADDLABREPLYDATA_H
