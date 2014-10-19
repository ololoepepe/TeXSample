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

#ifndef TSETLATESTAPPVERSIONREPLYDATA_H
#define TSETLATESTAPPVERSIONREPLYDATA_H

class TSetLatestAppVersionReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TSetLatestAppVersionReplyData ===============
============================================================================*/

class T_CORE_EXPORT TSetLatestAppVersionReplyData : public BBase
{
    B_DECLARE_PRIVATE(TSetLatestAppVersionReplyData)
public:
    explicit TSetLatestAppVersionReplyData();
    TSetLatestAppVersionReplyData(const TSetLatestAppVersionReplyData &other);
    ~TSetLatestAppVersionReplyData();
public:
    TSetLatestAppVersionReplyData &operator =(const TSetLatestAppVersionReplyData &other);
    bool operator ==(const TSetLatestAppVersionReplyData &other) const;
    bool operator !=(const TSetLatestAppVersionReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TSetLatestAppVersionReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TSetLatestAppVersionReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TSetLatestAppVersionReplyData &data);
};

Q_DECLARE_METATYPE(TSetLatestAppVersionReplyData)

#endif // TSETLATESTAPPVERSIONREPLYDATA_H
