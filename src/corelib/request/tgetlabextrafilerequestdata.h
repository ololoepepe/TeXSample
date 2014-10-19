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

#ifndef TGETLABEXTRAFILEREQUESTDATA_H
#define TGETLABEXTRAFILEREQUESTDATA_H

class TGetLabExtraFileRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabExtraFileRequestData =================
============================================================================*/

class T_CORE_EXPORT TGetLabExtraFileRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabExtraFileRequestData)
public:
    explicit TGetLabExtraFileRequestData();
    TGetLabExtraFileRequestData(const TGetLabExtraFileRequestData &other);
    ~TGetLabExtraFileRequestData();
public:
    void clear();
    QString fileName() const;
    bool isValid() const;
    quint64 labId() const;
    void setFileName(const QString &fileName);
    void setLabId(quint64 id);
public:
    TGetLabExtraFileRequestData &operator =(const TGetLabExtraFileRequestData &other);
    bool operator ==(const TGetLabExtraFileRequestData &other) const;
    bool operator !=(const TGetLabExtraFileRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetLabExtraFileRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetLabExtraFileRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetLabExtraFileRequestData &data);
};

Q_DECLARE_METATYPE(TGetLabExtraFileRequestData)

#endif // TGETLABEXTRAFILEREQUESTDATA_H
