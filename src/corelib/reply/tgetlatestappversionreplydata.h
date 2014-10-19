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

#ifndef TGETLATESTAPPVERSIONREPLYDATA_H
#define TGETLATESTAPPVERSIONREPLYDATA_H

class TGetLatestAppVersionReplyDataPrivate;

class BVersion;

class QDataStream;
class QDebug;
class QUrl;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLatestAppVersionReplyData ===============
============================================================================*/

class T_CORE_EXPORT TGetLatestAppVersionReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLatestAppVersionReplyData)
public:
    explicit TGetLatestAppVersionReplyData();
    TGetLatestAppVersionReplyData(const TGetLatestAppVersionReplyData &other);
    ~TGetLatestAppVersionReplyData();
public:
    QUrl downloadUrl() const;
    void setDownloadUrl(const QUrl &url);
    void setVersion(const BVersion &version);
    BVersion version() const;
public:
    TGetLatestAppVersionReplyData &operator =(const TGetLatestAppVersionReplyData &other);
    bool operator ==(const TGetLatestAppVersionReplyData &other) const;
    bool operator !=(const TGetLatestAppVersionReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TGetLatestAppVersionReplyData &data);
};

Q_DECLARE_METATYPE(TGetLatestAppVersionReplyData)

#endif // TGETLATESTAPPVERSIONREPLYDATA_H
