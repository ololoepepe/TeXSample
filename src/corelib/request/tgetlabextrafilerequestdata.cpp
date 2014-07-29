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

#include "tgetlabextrafilerequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLabExtraFileRequestDataPrivate ==========
============================================================================*/

class TGetLabExtraFileRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLabExtraFileRequestData)
public:
    QString fileName;
    quint64 labId;
public:
    explicit TGetLabExtraFileRequestDataPrivate(TGetLabExtraFileRequestData *q);
    ~TGetLabExtraFileRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLabExtraFileRequestDataPrivate)
};

/*============================================================================
================================ TGetLabExtraFileRequestDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabExtraFileRequestDataPrivate::TGetLabExtraFileRequestDataPrivate(TGetLabExtraFileRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetLabExtraFileRequestDataPrivate::~TGetLabExtraFileRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabExtraFileRequestDataPrivate::init()
{
    labId = 0;
}

/*============================================================================
================================ TGetLabExtraFileRequestData =================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabExtraFileRequestData::TGetLabExtraFileRequestData() :
    BBase(*new TGetLabExtraFileRequestDataPrivate(this))
{
    d_func()->init();
}

TGetLabExtraFileRequestData::TGetLabExtraFileRequestData(const TGetLabExtraFileRequestData &other) :
    BBase(*new TGetLabExtraFileRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLabExtraFileRequestData::~TGetLabExtraFileRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabExtraFileRequestData::clear()
{
    d_func()->fileName.clear();
    d_func()->labId = 0;
}

QString TGetLabExtraFileRequestData::fileName() const
{
    return d_func()->fileName;
}

quint64 TGetLabExtraFileRequestData::labId() const
{
    return d_func()->labId;
}

bool TGetLabExtraFileRequestData::isValid() const
{
    return d_func()->labId;
}

void TGetLabExtraFileRequestData::setFileName(const QString &fileName)
{
    d_func()->fileName = fileName;
}

void TGetLabExtraFileRequestData::setLabId(quint64 id)
{
    d_func()->labId = id;
}

/*============================== Public operators ==========================*/

TGetLabExtraFileRequestData &TGetLabExtraFileRequestData::operator =(const TGetLabExtraFileRequestData &other)
{
    B_D(TGetLabExtraFileRequestData);
    const TGetLabExtraFileRequestDataPrivate *dd = other.d_func();
    d->fileName = dd->fileName;
    d->labId = dd->labId;
    return *this;
}

bool TGetLabExtraFileRequestData::operator ==(const TGetLabExtraFileRequestData &other) const
{
    const B_D(TGetLabExtraFileRequestData);
    const TGetLabExtraFileRequestDataPrivate *dd = other.d_func();
    return d->fileName == dd->fileName && d->labId == dd->labId;
}

bool TGetLabExtraFileRequestData::operator !=(const TGetLabExtraFileRequestData &other) const
{
    return !(*this == other);
}

TGetLabExtraFileRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLabExtraFileRequestData &data)
{
    const TGetLabExtraFileRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("file_name", d->fileName);
    m.insert("lab_id", d->labId);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLabExtraFileRequestData &data)
{
    TGetLabExtraFileRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->fileName = m.value("file_name").toString();
    d->labId = m.value("lab_id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLabExtraFileRequestData &/*data*/)
{
    //const TGetLabExtraFileRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLabExtraFileRequestData(" << ")";
    return dbg.space();
}
