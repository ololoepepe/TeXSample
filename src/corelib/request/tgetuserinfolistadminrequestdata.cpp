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

#include "tgetuserinfolistadminrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoListAdminRequestDataPrivate =====
============================================================================*/

class TGetUserInfoListAdminRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoListAdminRequestData)
public:
    explicit TGetUserInfoListAdminRequestDataPrivate(TGetUserInfoListAdminRequestData *q);
    ~TGetUserInfoListAdminRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoListAdminRequestDataPrivate)
};

/*============================================================================
================================ TGetUserInfoListAdminRequestDataPrivate =====
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoListAdminRequestDataPrivate::TGetUserInfoListAdminRequestDataPrivate(TGetUserInfoListAdminRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoListAdminRequestDataPrivate::~TGetUserInfoListAdminRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoListAdminRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoListAdminRequestData ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoListAdminRequestData::TGetUserInfoListAdminRequestData() :
    BBase(*new TGetUserInfoListAdminRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoListAdminRequestData::TGetUserInfoListAdminRequestData(const TGetUserInfoListAdminRequestData &other) :
    BBase(*new TGetUserInfoListAdminRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoListAdminRequestData::~TGetUserInfoListAdminRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetUserInfoListAdminRequestData &TGetUserInfoListAdminRequestData::operator =(
        const TGetUserInfoListAdminRequestData &/*other*/)
{
    //B_D(TGetUserInfoListAdminRequestData);
    //const TGetUserInfoListAdminRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetUserInfoListAdminRequestData::operator ==(const TGetUserInfoListAdminRequestData &/*other*/) const
{
    //const B_D(TGetUserInfoListAdminRequestData);
    //const TGetUserInfoListAdminRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetUserInfoListAdminRequestData::operator !=(const TGetUserInfoListAdminRequestData &other) const
{
    return !(*this == other);
}

TGetUserInfoListAdminRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminRequestData &/*data*/)
{
    //const TGetUserInfoListAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminRequestData &/*data*/)
{
    //TGetUserInfoListAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminRequestData &/*data*/)
{
    //const TGetUserInfoListAdminRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoListAdminRequestData(" << ")";
    return dbg.space();
}
