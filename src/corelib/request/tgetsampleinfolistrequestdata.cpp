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

#include "tgetsampleinfolistrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleInfoListRequestDataPrivate ========
============================================================================*/

class TGetSampleInfoListRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleInfoListRequestData)
public:
    explicit TGetSampleInfoListRequestDataPrivate(TGetSampleInfoListRequestData *q);
    ~TGetSampleInfoListRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleInfoListRequestDataPrivate)
};

/*============================================================================
================================ TGetSampleInfoListRequestDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListRequestDataPrivate::TGetSampleInfoListRequestDataPrivate(TGetSampleInfoListRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleInfoListRequestDataPrivate::~TGetSampleInfoListRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleInfoListRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSampleInfoListRequestData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListRequestData::TGetSampleInfoListRequestData() :
    BBase(*new TGetSampleInfoListRequestDataPrivate(this))
{
    d_func()->init();
}

TGetSampleInfoListRequestData::TGetSampleInfoListRequestData(const TGetSampleInfoListRequestData &other) :
    BBase(*new TGetSampleInfoListRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleInfoListRequestData::~TGetSampleInfoListRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetSampleInfoListRequestData &TGetSampleInfoListRequestData::operator =(
        const TGetSampleInfoListRequestData &/*other*/)
{
    //B_D(TGetSampleInfoListRequestData);
    //const TGetSampleInfoListRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetSampleInfoListRequestData::operator ==(const TGetSampleInfoListRequestData &/*other*/) const
{
    //const B_D(TGetSampleInfoListRequestData);
    //const TGetSampleInfoListRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetSampleInfoListRequestData::operator !=(const TGetSampleInfoListRequestData &other) const
{
    return !(*this == other);
}

TGetSampleInfoListRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListRequestData &/*data*/)
{
    //const TGetSampleInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListRequestData &/*data*/)
{
    //TGetSampleInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleInfoListRequestData &/*data*/)
{
    //const TGetSampleInfoListRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleInfoListRequestData(" << ")";
    return dbg.space();
}
