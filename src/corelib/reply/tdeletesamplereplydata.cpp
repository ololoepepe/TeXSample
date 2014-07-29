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

#include "tdeletesamplereplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteSampleReplyDataPrivate ===============
============================================================================*/

class TDeleteSampleReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteSampleReplyData)
public:
    explicit TDeleteSampleReplyDataPrivate(TDeleteSampleReplyData *q);
    ~TDeleteSampleReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteSampleReplyDataPrivate)
};

/*============================================================================
================================ TDeleteSampleReplyDataPrivate ===============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteSampleReplyDataPrivate::TDeleteSampleReplyDataPrivate(TDeleteSampleReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteSampleReplyDataPrivate::~TDeleteSampleReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteSampleReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteSampleReplyData ======================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteSampleReplyData::TDeleteSampleReplyData() :
    BBase(*new TDeleteSampleReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteSampleReplyData::TDeleteSampleReplyData(const TDeleteSampleReplyData &other) :
    BBase(*new TDeleteSampleReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteSampleReplyData::~TDeleteSampleReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TDeleteSampleReplyData &TDeleteSampleReplyData::operator =(const TDeleteSampleReplyData &/*other*/)
{
    //B_D(TDeleteSampleReplyData);
    //const TDeleteSampleReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TDeleteSampleReplyData::operator ==(const TDeleteSampleReplyData &/*other*/) const
{
    //const B_D(TDeleteSampleReplyData);
    //const TDeleteSampleReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TDeleteSampleReplyData::operator !=(const TDeleteSampleReplyData &other) const
{
    return !(*this == other);
}

TDeleteSampleReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteSampleReplyData &/*data*/)
{
    //const TDeleteSampleReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteSampleReplyData &/*data*/)
{
    //TDeleteSampleReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteSampleReplyData &/*data*/)
{
    //const TDeleteSampleReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteSampleReplyData(" << ")";
    return dbg.space();
}
