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

#include "tgetlabextrafilereplydata.h"

#include "tbinaryfile.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLabExtraFileReplyDataPrivate ============
============================================================================*/

class TGetLabExtraFileReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLabExtraFileReplyData)
public:
    TBinaryFile file;
public:
    explicit TGetLabExtraFileReplyDataPrivate(TGetLabExtraFileReplyData *q);
    ~TGetLabExtraFileReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLabExtraFileReplyDataPrivate)
};

/*============================================================================
================================ TGetLabExtraFileReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabExtraFileReplyDataPrivate::TGetLabExtraFileReplyDataPrivate(TGetLabExtraFileReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetLabExtraFileReplyDataPrivate::~TGetLabExtraFileReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabExtraFileReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLabExtraFileReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabExtraFileReplyData::TGetLabExtraFileReplyData() :
    BBase(*new TGetLabExtraFileReplyDataPrivate(this))
{
    d_func()->init();
}

TGetLabExtraFileReplyData::TGetLabExtraFileReplyData(const TGetLabExtraFileReplyData &other) :
    BBase(*new TGetLabExtraFileReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLabExtraFileReplyData::~TGetLabExtraFileReplyData()
{
    //
}

/*============================== Public methods ============================*/

TBinaryFile &TGetLabExtraFileReplyData::file()
{
    return d_func()->file;
}

const TBinaryFile &TGetLabExtraFileReplyData::file() const
{
    return d_func()->file;
}

void TGetLabExtraFileReplyData::setFile(const TBinaryFile &file)
{
    d_func()->file = file;
}

/*============================== Public operators ==========================*/

TGetLabExtraFileReplyData &TGetLabExtraFileReplyData::operator =(const TGetLabExtraFileReplyData &other)
{
    B_D(TGetLabExtraFileReplyData);
    const TGetLabExtraFileReplyDataPrivate *dd = other.d_func();
    d->file = dd->file;
    return *this;
}

bool TGetLabExtraFileReplyData::operator ==(const TGetLabExtraFileReplyData &other) const
{
    const B_D(TGetLabExtraFileReplyData);
    const TGetLabExtraFileReplyDataPrivate *dd = other.d_func();
    return d->file == dd->file;
}

bool TGetLabExtraFileReplyData::operator !=(const TGetLabExtraFileReplyData &other) const
{
    return !(*this == other);
}

TGetLabExtraFileReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLabExtraFileReplyData &data)
{
    const TGetLabExtraFileReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("file", d->file);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLabExtraFileReplyData &data)
{
    TGetLabExtraFileReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->file = m.value("file").value<TBinaryFile>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLabExtraFileReplyData &/*data*/)
{
    //const TGetLabExtraFileReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLabExtraFileReplyData(" << ")";
    return dbg.space();
}
