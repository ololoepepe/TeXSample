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

#include "tgetserverstaterequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetServerStateRequestDataPrivate ===========
============================================================================*/

class TGetServerStateRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetServerStateRequestData)
public:
    explicit TGetServerStateRequestDataPrivate(TGetServerStateRequestData *q);
    ~TGetServerStateRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetServerStateRequestDataPrivate)
};


/*============================================================================
================================ TGetServerStateRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TGetServerStateRequestDataPrivate::TGetServerStateRequestDataPrivate(TGetServerStateRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetServerStateRequestDataPrivate::~TGetServerStateRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetServerStateRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetServerStateRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TGetServerStateRequestData::TGetServerStateRequestData() :
    BBase(*new TGetServerStateRequestDataPrivate(this))
{
    d_func()->init();
}

TGetServerStateRequestData::TGetServerStateRequestData(const TGetServerStateRequestData &other) :
    BBase(*new TGetServerStateRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetServerStateRequestData::~TGetServerStateRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetServerStateRequestData &TGetServerStateRequestData::operator =(const TGetServerStateRequestData &/*other*/)
{
    //B_D(TGetServerStateRequestData);
    //const TGetServerStateRequestDataPrivate *dd = other.d_func();
    //
    return *this;
}

bool TGetServerStateRequestData::operator ==(const TGetServerStateRequestData &/*other*/) const
{
    //const B_D(TGetServerStateRequestData);
    //const TGetServerStateRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetServerStateRequestData::operator !=(const TGetServerStateRequestData &other) const
{
    return !(*this == other);
}

TGetServerStateRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetServerStateRequestData &/*data*/)
{
    //const TGetServerStateRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    //
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetServerStateRequestData &/*data*/)
{
    //TGetServerStateRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    //
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetServerStateRequestData &/*data*/)
{
    //const TGetServerStateRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetServerStateRequestData(" << ")";
    return dbg.space();
}
