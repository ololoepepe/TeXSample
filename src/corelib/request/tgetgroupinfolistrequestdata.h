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

#ifndef TGETGROUPINFOLISTREQUESTDATA_H
#define TGETGROUPINFOLISTREQUESTDATA_H

class TGetGroupInfoListRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetGroupInfoListRequestData ================
============================================================================*/

class T_CORE_EXPORT TGetGroupInfoListRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetGroupInfoListRequestData)
public:
    explicit TGetGroupInfoListRequestData();
    TGetGroupInfoListRequestData(const TGetGroupInfoListRequestData &other);
    ~TGetGroupInfoListRequestData();
public:
    TGetGroupInfoListRequestData &operator =(const TGetGroupInfoListRequestData &other);
    bool operator ==(const TGetGroupInfoListRequestData &other) const;
    bool operator !=(const TGetGroupInfoListRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetGroupInfoListRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetGroupInfoListRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetGroupInfoListRequestData &data);
};

Q_DECLARE_METATYPE(TGetGroupInfoListRequestData)

#endif // TGETGROUPINFOLISTREQUESTDATA_H
