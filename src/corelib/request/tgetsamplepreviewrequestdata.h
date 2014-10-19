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

#ifndef TGETSAMPLIPREVIEWREQUESTDATA_H
#define TGETSAMPLIPREVIEWREQUESTDATA_H

class TGetSamplePreviewRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSamplePreviewRequestData ================
============================================================================*/

class T_CORE_EXPORT TGetSamplePreviewRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSamplePreviewRequestData)
public:
    explicit TGetSamplePreviewRequestData();
    TGetSamplePreviewRequestData(const TGetSamplePreviewRequestData &other);
    ~TGetSamplePreviewRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TGetSamplePreviewRequestData &operator =(const TGetSamplePreviewRequestData &other);
    bool operator ==(const TGetSamplePreviewRequestData &other) const;
    bool operator !=(const TGetSamplePreviewRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetSamplePreviewRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetSamplePreviewRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetSamplePreviewRequestData &data);
};

Q_DECLARE_METATYPE(TGetSamplePreviewRequestData)

#endif // TGETSAMPLIPREVIEWREQUESTDATA_H
