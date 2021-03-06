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

#include "tclientinfo.h"

#include "tnamespace.h"

#include <BApplicationBase>
#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>
#include <BVersion>

#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TClientInfoPrivate ==========================
============================================================================*/

class TClientInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TClientInfo)
public:
    Texsample::ClientType applicationType;
    BVersion applicationVersion;
    BVersion beqtVersion;
    QString os;
    BeQt::OSType osType;
    bool portable;
    BeQt::ProcessorArchitecture processorArchitecture;
    BVersion qtVersion;
    BVersion texsampleVersion;
public:
   explicit TClientInfoPrivate(TClientInfo *q);
    ~TClientInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TClientInfoPrivate)
};

/*============================================================================
================================ TClientInfoPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TClientInfoPrivate::TClientInfoPrivate(TClientInfo *q) :
    BBasePrivate(q)
{
    //
}

TClientInfoPrivate::~TClientInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TClientInfoPrivate::init()
{
    applicationType = Texsample::UnknownClient;
    osType = BeQt::UnknownOS;
    portable = false;
    processorArchitecture = BeQt::UnknownArchitecture;
}

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

/*============================== Static public methods =====================*/

TClientInfo TClientInfo::create()
{
    TClientInfo info;
    TClientInfoPrivate *d = info.d_func();
    d->applicationType = Texsample::clientType();
    d->applicationVersion = BVersion(QCoreApplication::applicationVersion());
    d->beqtVersion = BVersion(bVersion());
    d->os = BeQt::osVersion();
    d->osType = BeQt::osType();
    d->portable = BApplicationBase::isPortable();
    d->processorArchitecture = BeQt::processorArchitecture();
    d->qtVersion = BVersion(qVersion());
    d->texsampleVersion = BVersion(tVersion());
    return info;
}

/*============================== Public constructors =======================*/

TClientInfo::TClientInfo() :
    BBase(*new TClientInfoPrivate(this))
{
    d_func()->init();
}

TClientInfo::TClientInfo(const TClientInfo &other) :
    BBase(*new TClientInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TClientInfo::~TClientInfo()
{
    //
}

/*============================== Public methods ============================*/

Texsample::ClientType TClientInfo::applicationType() const
{
    return d_func()->applicationType;
}

BVersion TClientInfo::applicationVersion() const
{
    return d_func()->applicationVersion;
}

BVersion TClientInfo::beqtVersion() const
{
    return d_func()->beqtVersion;
}

bool TClientInfo::isPortable() const
{
    return d_func()->portable;
}

bool TClientInfo::isValid() const
{
    const B_D(TClientInfo);
    return Texsample::UnknownClient != d->applicationType && d->applicationVersion.isValid()
            && d->beqtVersion.isValid() && d->qtVersion.isValid() && d->texsampleVersion.isValid();
}

QString TClientInfo::os() const
{
    return d_func()->os;
}

BeQt::OSType TClientInfo::osType() const
{
    return d_func()->osType;
}

BeQt::ProcessorArchitecture TClientInfo::processorArchitecture() const
{
    return d_func()->processorArchitecture;
}

QString TClientInfo::processorArchitectureString() const
{
    return BeQt::processorArchitectureToString(d_func()->processorArchitecture);
}

BVersion TClientInfo::qtVersion() const
{
    return d_func()->qtVersion;
}

BVersion TClientInfo::texsampleVersion() const
{
    return d_func()->texsampleVersion;
}

QString TClientInfo::toString(const QString &format) const
{
    //%n - applicationType
    //%v - applicationVersion
    //%b - beqtVersion
    //%p - isPortable
    //%o - os
    //%a - processorArchitecture
    //%q - qtVersion
    //%t - texsampleVersion
    const B_D(TClientInfo);
    QString f = format;
    if (f.isEmpty())
        f = "%n v%v (%p)\nTeXSample v%t; BeQt v%b; Qt v%q\nOS: %o";
    f.replace("%n", Texsample::clientTypeToString(d->applicationType));
    f.replace("%v", d->applicationVersion);
    f.replace("%b", d->beqtVersion);
    f.replace("%p", d->portable ? "portable" : "non-portable");
    f.replace("%o", d->os);
    f.replace("%a", processorArchitectureString());
    f.replace("%q", d->qtVersion);
    f.replace("%t", d->texsampleVersion);
    return f;
}

/*============================== Public operators ==========================*/

TClientInfo &TClientInfo::operator =(const TClientInfo &other)
{
    B_D(TClientInfo);
    const TClientInfoPrivate *dd = other.d_func();
    d->applicationType = dd->applicationType;
    d->applicationVersion = dd->applicationVersion;
    d->beqtVersion = dd->beqtVersion;
    d->os = dd->os;
    d->osType = dd->osType;
    d->portable = dd->portable;
    d->processorArchitecture = dd->processorArchitecture;
    d->qtVersion = dd->qtVersion;
    d->texsampleVersion = dd->texsampleVersion;
    return *this;
}

bool TClientInfo::operator ==(const TClientInfo &other) const
{
    const B_D(TClientInfo);
    const TClientInfoPrivate *dd = other.d_func();
    return d->applicationType == dd->applicationType && d->applicationVersion == dd->applicationVersion
            && d->beqtVersion == dd->beqtVersion && d->os == dd->os && d->osType == dd->osType
            && d->portable == dd->portable && d->processorArchitecture == dd->processorArchitecture
            && d->qtVersion == dd->qtVersion && d->texsampleVersion == dd->texsampleVersion;
}

TClientInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TClientInfo &info)
{
    const TClientInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("application_name", int(d->applicationType));
    m.insert("application_version", d->applicationVersion);
    m.insert("beqt_version", d->beqtVersion);
    m.insert("os", d->os);
    m.insert("os_type", int(d->osType));
    m.insert("portable", d->portable);
    m.insert("processor_architecture", int(d->processorArchitecture));
    m.insert("qt_version", d->qtVersion);
    m.insert("texsample_version", d->texsampleVersion);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TClientInfo &info)
{
    static const QList<int> Types = bRangeD(BeQt::LinuxOS, BeQt::WindowsOS);
    TClientInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->applicationType = enum_cast<Texsample::ClientType>(m.value("application_name"), Texsample::UnknownClient,
                                                          Texsample::TexsampleConsole);
    d->applicationVersion = m.value("application_version").value<BVersion>();
    d->beqtVersion = m.value("beqt_version").value<BVersion>();
    d->os = m.value("os").toString();
    d->osType = enum_cast<BeQt::OSType>(m.value("os_type"), BeQt::UnknownOS, BeQt::MacOS);
    d->portable = m.value("portable").toBool();
    d->processorArchitecture = enum_cast<BeQt::ProcessorArchitecture>(
                m.value("processor_architecture"), BeQt::UnknownArchitecture, BeQt::Tms470Architecture);
    d->qtVersion = m.value("qt_version").value<BVersion>();
    d->texsampleVersion = m.value("texsample_version").value<BVersion>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TClientInfo &/*info*/)
{
    dbg.nospace() << "TClientInfo(" << ")";
    return dbg.space();
}
