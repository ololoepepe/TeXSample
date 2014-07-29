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

#include "tlabdata.h"

#include "tlabapplication.h"
#include "tlabtype.h"
#include "tnamespace.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLabDataPrivate =============================
============================================================================*/

class TLabDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabData)
public:
    explicit TLabDataPrivate(TLabData *q);
    ~TLabDataPrivate();
public:
    void init();
public:
    TLabApplication application;
    QString url;
private:
    Q_DISABLE_COPY(TLabDataPrivate)
};

/*============================================================================
================================ TLabDataPrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TLabDataPrivate::TLabDataPrivate(TLabData *q) :
    BBasePrivate(q)
{
    //
}

TLabDataPrivate::~TLabDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabDataPrivate::init()
{
    //
}

/*============================================================================
================================ TLabData ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TLabData::TLabData() :
    BBase(*new TLabDataPrivate(this))
{
    d_func()->init();
}

TLabData::TLabData(const TLabData &other) :
    BBase(*new TLabDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLabData::~TLabData()
{
    //
}

/*============================== Public methods ============================*/

TLabApplication &TLabData::application()
{
    return d_func()->application;
}

const TLabApplication &TLabData::application() const
{
    return d_func()->application;
}

void TLabData::clear()
{
    B_D(TLabData);
    d->application.clear();
    d->url.clear();
}

bool TLabData::isValid() const
{
    return type() != TLabType(TLabType::NoType);
}

BeQt::OSType TLabData::os() const
{
    const B_D(TLabData);
    return d->application.isValid() ? d->application.os() : BeQt::UnknownOS;
}

void TLabData::setApplication(const TLabApplication &application)
{
    clear();
    d_func()->application = application;
}

void TLabData::setUrl(const QString &url)
{
    clear();
    d_func()->url = Texsample::testUrl(url) ? url : QString();
}

int TLabData::size() const
{
    if (!isValid())
        return 0;
    const B_D(TLabData);
    return d->application.isValid() ? d->application.size() : (d->url.length() * 2);
}

TLabType TLabData::type() const
{
    const B_D(TLabData);
    if (d->application.isValid()) {
        if (d->application.mayBeExecutable())
            return TLabType::DesktopApplication;
        else
            return TLabType::WebApplication;
    } else if (!d->url.isEmpty()) {
        return TLabType::Url;
    } else {
        return TLabType::NoType;
    }
}

QString TLabData::url() const
{
    return d_func()->url;
}

/*============================== Public operators ==========================*/

TLabData &TLabData::operator =(const TLabData &other)
{
    B_D(TLabData);
    const TLabDataPrivate *dd = other.d_func();
    d->application = dd->application;
    d->url = dd->url;
    return *this;
}

bool TLabData::operator ==(const TLabData &other) const
{
    const B_D(TLabData);
    const TLabDataPrivate *dd = other.d_func();
    return d->application == dd->application && d->url == dd->url;
}

bool TLabData::operator !=(const TLabData &other) const
{
    return !(*this == other);
}

TLabData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLabData &data)
{
    const TLabDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("application", d->application);
    m.insert("url", d->url);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabData &data)
{
    TLabDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->application = m.value("application").value<TLabApplication>();
    d->url = m.value("url").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabData &/*data*/)
{
    //const TLabDataPrivate *d = data.d_func();
    dbg.nospace() << "TLabData(" << ")";
    return dbg.space();
}
