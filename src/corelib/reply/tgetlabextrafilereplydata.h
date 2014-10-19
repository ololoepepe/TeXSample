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

#ifndef TGETLABEXTRAFILEREPLYDATA_H
#define TGETLABEXTRAFILEREPLYDATA_H

class TGetLabExtraFileReplyDataPrivate;

class TBinaryFile;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabExtraFileReplyData ===================
============================================================================*/

class T_CORE_EXPORT TGetLabExtraFileReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabExtraFileReplyData)
public:
    explicit TGetLabExtraFileReplyData();
    TGetLabExtraFileReplyData(const TGetLabExtraFileReplyData &other);
    ~TGetLabExtraFileReplyData();
public:
    TBinaryFile &file();
    const TBinaryFile &file() const;
    void setFile(const TBinaryFile &file);
public:
    TGetLabExtraFileReplyData &operator =(const TGetLabExtraFileReplyData &other);
    bool operator ==(const TGetLabExtraFileReplyData &other) const;
    bool operator !=(const TGetLabExtraFileReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetLabExtraFileReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetLabExtraFileReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetLabExtraFileReplyData &data);
};

Q_DECLARE_METATYPE(TGetLabExtraFileReplyData)

#endif // TGETLABEXTRAFILEREPLYDATA_H
