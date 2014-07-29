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

#include "tlabdatainfo.h"

#include "tlabtype.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLabDataInfoPrivate =========================
============================================================================*/

class TLabDataInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabDataInfo)
public:
    BeQt::OSType os;
    int size;
    TLabType type;
public:
    explicit TLabDataInfoPrivate(TLabDataInfo *q);
    ~TLabDataInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLabDataInfoPrivate)
};

/*============================================================================
================================ TLabDataInfoPrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TLabDataInfoPrivate::TLabDataInfoPrivate(TLabDataInfo *q) :
    BBasePrivate(q)
{
    //
}

TLabDataInfoPrivate::~TLabDataInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabDataInfoPrivate::init()
{
    os = BeQt::UnknownOS;
    size = 0;
}

/*============================================================================
================================ TLabDataInfo ================================
============================================================================*/

/*============================== Public constructors =======================*/

TLabDataInfo::TLabDataInfo() :
    BBase(*new TLabDataInfoPrivate(this))
{
    d_func()->init();
}

TLabDataInfo::TLabDataInfo(const TLabDataInfo &other) :
    BBase(*new TLabDataInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLabDataInfo::~TLabDataInfo()
{
    //
}

/*============================== Public methods ============================*/

void TLabDataInfo::clear()
{
    B_D(TLabDataInfo);
    d->os = BeQt::UnknownOS;
    d->size = 0;
    d->type = TLabType();
}

bool TLabDataInfo::isValid() const
{
    const B_D(TLabDataInfo);
    return d->type.isValid() && (d->type == TLabType(TLabType::Url) || BeQt::UnknownOS != d->os);
}

BeQt::OSType TLabDataInfo::os() const
{
    return d_func()->os;
}

void TLabDataInfo::setOs(BeQt::OSType os)
{
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d_func()->os = enum_cast<BeQt::OSType>(os, Types, BeQt::UnknownOS);
}

void TLabDataInfo::setSize(int size)
{
    d_func()->size = (size > 0) ? size : 0;
}

void TLabDataInfo::setType(const TLabType &type)
{
    d_func()->type = type;
}

int TLabDataInfo::size() const
{
    return d_func()->size;
}

TLabType TLabDataInfo::type() const
{
    return d_func()->type;
}

/*============================== Public operators ==========================*/

TLabDataInfo &TLabDataInfo::operator =(const TLabDataInfo &other)
{
    B_D(TLabDataInfo);
    const TLabDataInfoPrivate *dd = other.d_func();
    d->os = dd->os;
    d->size = dd->size;
    d->type = dd->type;
    return *this;
}

bool TLabDataInfo::operator ==(const TLabDataInfo &other) const
{
    const B_D(TLabDataInfo);
    const TLabDataInfoPrivate *dd = other.d_func();
    return d->os == dd->os && d->size == dd->size && d->type == dd->type;
}

bool TLabDataInfo::operator !=(const TLabDataInfo &other) const
{
    return !(*this == other);
}

TLabDataInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLabDataInfo &data)
{
    const TLabDataInfoPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("os", int(d->os));
    m.insert("size", d->size);
    m.insert("type", d->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabDataInfo &data)
{
    TLabDataInfoPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d->os = enum_cast<BeQt::OSType>(m.value("os"), Types, BeQt::UnknownOS);
    d->size = m.value("size").toInt();
    d->type = m.value("type").value<TLabType>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabDataInfo &/*data*/)
{
    //const TLabDataInfoPrivate *d = data.d_func();
    dbg.nospace() << "TLabDataInfo(" << ")";
    return dbg.space();
}
