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

#ifndef TGETLATESTAPPVERSIONREQUESTDATA_H
#define TGETLATESTAPPVERSIONREQUESTDATA_H

class TGetLatestAppVersionRequestDataPrivate;

class TClientInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLatestAppVersionRequestData =============
============================================================================*/

class T_CORE_EXPORT TGetLatestAppVersionRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLatestAppVersionRequestData)
public:
    explicit TGetLatestAppVersionRequestData();
    TGetLatestAppVersionRequestData(const TGetLatestAppVersionRequestData &other);
    ~TGetLatestAppVersionRequestData();
public:
    void clear();
    TClientInfo clientInfo() const;
    bool isValid() const;
    void setClientInfo(const TClientInfo &info);
public:
    TGetLatestAppVersionRequestData &operator =(const TGetLatestAppVersionRequestData &other);
    bool operator ==(const TGetLatestAppVersionRequestData &other) const;
    bool operator !=(const TGetLatestAppVersionRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLatestAppVersionRequestData &data);
};

Q_DECLARE_METATYPE(TGetLatestAppVersionRequestData)

#endif // TGETLATESTAPPVERSIONREQUESTDATA_H
