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

#include "tgetgroupinfolistrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetGroupInfoListRequestDataPrivate =========
============================================================================*/

class TGetGroupInfoListRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetGroupInfoListRequestData)
public:
    explicit TGetGroupInfoListRequestDataPrivate(TGetGroupInfoListRequestData *q);
    ~TGetGroupInfoListRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetGroupInfoListRequestDataPrivate)
};

/*============================================================================
================================ TGetGroupInfoListRequestDataPrivate =========
============================================================================*/

/*============================== Public constructors =======================*/

TGetGroupInfoListRequestDataPrivate::TGetGroupInfoListRequestDataPrivate(TGetGroupInfoListRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetGroupInfoListRequestDataPrivate::~TGetGroupInfoListRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetGroupInfoListRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetGroupInfoListRequestData ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetGroupInfoListRequestData::TGetGroupInfoListRequestData() :
    BBase(*new TGetGroupInfoListRequestDataPrivate(this))
{
    d_func()->init();
}

TGetGroupInfoListRequestData::TGetGroupInfoListRequestData(const TGetGroupInfoListRequestData &other) :
    BBase(*new TGetGroupInfoListRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetGroupInfoListRequestData::~TGetGroupInfoListRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetGroupInfoListRequestData &TGetGroupInfoListRequestData::operator =(const TGetGroupInfoListRequestData &/*other*/)
{
    //B_D(TGetGroupInfoListRequestData);
    //const TGetGroupInfoListRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetGroupInfoListRequestData::operator ==(const TGetGroupInfoListRequestData &/*other*/) const
{
    //const B_D(TGetGroupInfoListRequestData);
    //const TGetGroupInfoListRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetGroupInfoListRequestData::operator !=(const TGetGroupInfoListRequestData &other) const
{
    return !(*this == other);
}

TGetGroupInfoListRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetGroupInfoListRequestData &/*data*/)
{
    //const TGetGroupInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetGroupInfoListRequestData &/*data*/)
{
    //TGetGroupInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetGroupInfoListRequestData &/*data*/)
{
    //const TGetGroupInfoListRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetGroupInfoListRequestData(" << ")";
    return dbg.space();
}
