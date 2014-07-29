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

#ifndef TADDSAMPLEREPLYDATA_H
#define TADDSAMPLEREPLYDATA_H

class TAddSampleReplyDataPrivate;

class TSampleInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddSampleReplyData =========================
============================================================================*/

class T_CORE_EXPORT TAddSampleReplyData : public BBase
{
    B_DECLARE_PRIVATE(TAddSampleReplyData)
public:
    explicit TAddSampleReplyData();
    TAddSampleReplyData(const TAddSampleReplyData &other);
    ~TAddSampleReplyData();
public:
    TSampleInfo sampleInfo() const;
    void setSampleInfo(const TSampleInfo &info);
public:
    TAddSampleReplyData &operator =(const TAddSampleReplyData &other);
    bool operator ==(const TAddSampleReplyData &other) const;
    bool operator !=(const TAddSampleReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddSampleReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddSampleReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TAddSampleReplyData &data);
};

Q_DECLARE_METATYPE(TAddSampleReplyData)

#endif // TADDSAMPLEREPLYDATA_H
