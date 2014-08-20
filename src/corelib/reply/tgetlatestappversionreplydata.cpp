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

#include "tgetlatestappversionreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BVersion>

#include <QDataStream>
#include <QDebug>
#include <QUrl>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLatestAppVersionReplyDataPrivate ========
============================================================================*/

class TGetLatestAppVersionReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLatestAppVersionReplyData)
public:
    QUrl downloadUrl;
    BVersion version;
public:
    explicit TGetLatestAppVersionReplyDataPrivate(TGetLatestAppVersionReplyData *q);
    ~TGetLatestAppVersionReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLatestAppVersionReplyDataPrivate)
};

/*============================================================================
================================ TGetLatestAppVersionReplyDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TGetLatestAppVersionReplyDataPrivate::TGetLatestAppVersionReplyDataPrivate(TGetLatestAppVersionReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetLatestAppVersionReplyDataPrivate::~TGetLatestAppVersionReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLatestAppVersionReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLatestAppVersionReplyData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TGetLatestAppVersionReplyData::TGetLatestAppVersionReplyData() :
    BBase(*new TGetLatestAppVersionReplyDataPrivate(this))
{
    d_func()->init();
}

TGetLatestAppVersionReplyData::TGetLatestAppVersionReplyData(const TGetLatestAppVersionReplyData &other) :
    BBase(*new TGetLatestAppVersionReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLatestAppVersionReplyData::~TGetLatestAppVersionReplyData()
{
    //
}

/*============================== Public methods ============================*/

QUrl TGetLatestAppVersionReplyData::downloadUrl() const
{
    return d_func()->downloadUrl;
}

void TGetLatestAppVersionReplyData::setDownloadUrl(const QUrl &url)
{
    d_func()->downloadUrl = url;
}

void TGetLatestAppVersionReplyData::setVersion(const BVersion &version)
{
    d_func()->version = version;
}

BVersion TGetLatestAppVersionReplyData::version() const
{
    return d_func()->version;
}

/*============================== Public operators ==========================*/

TGetLatestAppVersionReplyData &TGetLatestAppVersionReplyData::operator =(const TGetLatestAppVersionReplyData &other)
{
    B_D(TGetLatestAppVersionReplyData);
    const TGetLatestAppVersionReplyDataPrivate *dd = other.d_func();
    d->downloadUrl = dd->downloadUrl;
    d->version = dd->version;
    return *this;
}

bool TGetLatestAppVersionReplyData::operator ==(const TGetLatestAppVersionReplyData &other) const
{
    const B_D(TGetLatestAppVersionReplyData);
    const TGetLatestAppVersionReplyDataPrivate *dd = other.d_func();
    return d->downloadUrl == dd->downloadUrl && d->version == dd->version;
}

bool TGetLatestAppVersionReplyData::operator !=(const TGetLatestAppVersionReplyData &other) const
{
    return !(*this == other);
}

TGetLatestAppVersionReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionReplyData &data)
{
    const TGetLatestAppVersionReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("download_url", d->downloadUrl);
    m.insert("version", d->version);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionReplyData &data)
{
    TGetLatestAppVersionReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->downloadUrl = m.value("download_url").toUrl();
    d->version = m.value("version").value<BVersion>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLatestAppVersionReplyData &/*data*/)
{
    //const TGetLatestAppVersionReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLatestAppVersionReplyData(" << ")";
    return dbg.space();
}
