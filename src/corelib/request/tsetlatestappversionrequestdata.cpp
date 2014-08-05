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

#include "tsetlatestappversionrequestdata.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>
#include <BVersion>

#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSetLatestAppVersionRequestDataPrivate ======
============================================================================*/

class TSetLatestAppVersionRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSetLatestAppVersionRequestData)
public:
    QString clientName;
    QUrl downloadUrl;
    BeQt::OSType os;
    bool portable;
    BeQt::ProcessorArchitecture processorArchitecture;
    BVersion version;
public:
    explicit TSetLatestAppVersionRequestDataPrivate(TSetLatestAppVersionRequestData *q);
    ~TSetLatestAppVersionRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSetLatestAppVersionRequestDataPrivate)
};


/*============================================================================
================================ TSetLatestAppVersionRequestDataPrivate ======
============================================================================*/

/*============================== Public constructors =======================*/

TSetLatestAppVersionRequestDataPrivate::TSetLatestAppVersionRequestDataPrivate(TSetLatestAppVersionRequestData *q) :
    BBasePrivate(q)
{
    //
}

TSetLatestAppVersionRequestDataPrivate::~TSetLatestAppVersionRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSetLatestAppVersionRequestDataPrivate::init()
{
    os = BeQt::UnknownOS;
    portable = false;
    processorArchitecture = BeQt::UnknownArchitecture;
}

/*============================================================================
================================ TSetLatestAppVersionRequestData =============
============================================================================*/

/*============================== Public constructors =======================*/

TSetLatestAppVersionRequestData::TSetLatestAppVersionRequestData() :
    BBase(*new TSetLatestAppVersionRequestDataPrivate(this))
{
    d_func()->init();
}

TSetLatestAppVersionRequestData::TSetLatestAppVersionRequestData(const TSetLatestAppVersionRequestData &other) :
    BBase(*new TSetLatestAppVersionRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSetLatestAppVersionRequestData::~TSetLatestAppVersionRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TSetLatestAppVersionRequestData::clear()
{
    B_D(TSetLatestAppVersionRequestData);
    d->clientName.clear();
    d->downloadUrl.clear();
    d->os = BeQt::UnknownOS;
    d->portable = false;
    d->processorArchitecture = BeQt::UnknownArchitecture;
    d->version.clear();
}

QString TSetLatestAppVersionRequestData::clientName() const
{
    return d_func()->clientName;
}

QUrl TSetLatestAppVersionRequestData::downloadUrl() const
{
    return d_func()->downloadUrl;
}

bool TSetLatestAppVersionRequestData::isValid() const
{
    const B_D(TSetLatestAppVersionRequestData);
    return !d->clientName.isEmpty() && d->downloadUrl.isValid() && (BeQt::UnknownOS != d->os)
            && (BeQt::UnknownArchitecture != d->processorArchitecture) && d->version.isValid();
}

BeQt::OSType TSetLatestAppVersionRequestData::os() const
{
    return d_func()->os;
}

bool TSetLatestAppVersionRequestData::portable() const
{
    return d_func()->portable;
}

BeQt::ProcessorArchitecture TSetLatestAppVersionRequestData::processorArchitecture() const
{
    return d_func()->processorArchitecture;
}

void TSetLatestAppVersionRequestData::setClientName(const QString &clientName)
{
    d_func()->clientName = clientName;
}

void TSetLatestAppVersionRequestData::setDownloadUrl(const QUrl &url)
{
    d_func()->downloadUrl = url;
}

void TSetLatestAppVersionRequestData::setOs(BeQt::OSType os)
{
    d_func()->os = os;
}

void TSetLatestAppVersionRequestData::setPortable(bool portable)
{
    d_func()->portable = portable;
}

void TSetLatestAppVersionRequestData::setProcessorArchitecture(BeQt::ProcessorArchitecture arch)
{
    d_func()->processorArchitecture = arch;
}

void TSetLatestAppVersionRequestData::setVersion(const BVersion &version)
{
    d_func()->version = version;
}

BVersion TSetLatestAppVersionRequestData::version() const
{
    return d_func()->version;
}

/*============================== Public operators ==========================*/

TSetLatestAppVersionRequestData &TSetLatestAppVersionRequestData::operator =(const TSetLatestAppVersionRequestData &other)
{
    B_D(TSetLatestAppVersionRequestData);
    const TSetLatestAppVersionRequestDataPrivate *dd = other.d_func();
    d->clientName = dd->clientName;
    d->downloadUrl = dd->downloadUrl;
    d->os = dd->os;
    d->portable = dd->portable;
    d->processorArchitecture = dd->processorArchitecture;
    d->version = dd->version;
    return *this;
}

bool TSetLatestAppVersionRequestData::operator ==(const TSetLatestAppVersionRequestData &other) const
{
    const B_D(TSetLatestAppVersionRequestData);
    const TSetLatestAppVersionRequestDataPrivate *dd = other.d_func();
    return d->clientName == dd->clientName && d->downloadUrl == dd->downloadUrl && d->os == dd->os
            && d->portable == dd->portable && d->processorArchitecture == dd->processorArchitecture
            && d->version == dd->version;
}

bool TSetLatestAppVersionRequestData::operator !=(const TSetLatestAppVersionRequestData &other) const
{
    return !(*this == other);
}

TSetLatestAppVersionRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSetLatestAppVersionRequestData &data)
{
    const TSetLatestAppVersionRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("client_name", d->clientName);
    m.insert("download_url", d->downloadUrl);
    m.insert("os", int(d->os));
    m.insert("portable", d->portable);
    m.insert("processor_architecture", int(d->processorArchitecture));
    m.insert("version", d->version);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSetLatestAppVersionRequestData &data)
{
    TSetLatestAppVersionRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->clientName = m.value("client_name").toString();
    d->downloadUrl = m.value("download_url").toUrl();
    static const QList<BeQt::OSType> Os = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS << BeQt::WindowsOS
                                                                << BeQt::LinuxOS << BeQt::MacOS;
    d->os = enum_cast<BeQt::OSType>(m.value("os"), Os, BeQt::UnknownOS);
    d->portable = m.value("portable").toBool();
    d->processorArchitecture = enum_cast<BeQt::ProcessorArchitecture>(
                m.value("processor_architecture"), BeQt::UnknownArchitecture, BeQt::Tms470Architecture);
    d->version = m.value("version").value<BVersion>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSetLatestAppVersionRequestData &/*data*/)
{
    //const TSetLatestAppVersionRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TSetLatestAppVersionRequestData(" << ")";
    return dbg.space();
}
