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

#ifndef TSETLATESTAPPVERSIONREQUESTDATA_H
#define TSETLATESTAPPVERSIONREQUESTDATA_H

class TSetLatestAppVersionRequestDataPrivate;

class BVersion;

class QDataStream;
class QDebug;
class QUrl;
class QVariant;

#include "tnamespace.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TSetLatestAppVersionRequestData =============
============================================================================*/

class T_CORE_EXPORT TSetLatestAppVersionRequestData : public BBase
{
    B_DECLARE_PRIVATE(TSetLatestAppVersionRequestData)
public:
    explicit TSetLatestAppVersionRequestData();
    TSetLatestAppVersionRequestData(const TSetLatestAppVersionRequestData &other);
    ~TSetLatestAppVersionRequestData();
public:
    void clear();
    Texsample::ClientType clientType() const;
    QUrl downloadUrl() const;
    bool isValid() const;
    BeQt::OSType os() const;
    bool portable() const;
    BeQt::ProcessorArchitecture processorArchitecture() const;
    void setClientType(Texsample::ClientType type);
    void setDownloadUrl(const QUrl &url);
    void setOs(BeQt::OSType os);
    void setPortable(bool portable);
    void setProcessorArchitecture(BeQt::ProcessorArchitecture arch);
    void setVersion(const BVersion &version);
    BVersion version() const;
public:
    TSetLatestAppVersionRequestData &operator =(const TSetLatestAppVersionRequestData &other);
    bool operator ==(const TSetLatestAppVersionRequestData &other) const;
    bool operator !=(const TSetLatestAppVersionRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TSetLatestAppVersionRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TSetLatestAppVersionRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TSetLatestAppVersionRequestData &data);
};

Q_DECLARE_METATYPE(TSetLatestAppVersionRequestData)

#endif // TSETLATESTAPPVERSIONREQUESTDATA_H
