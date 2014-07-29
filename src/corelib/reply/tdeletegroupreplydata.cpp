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

#include "tdeletegroupreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteGroupReplyDataPrivate ================
============================================================================*/

class TDeleteGroupReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteGroupReplyData)
public:
    explicit TDeleteGroupReplyDataPrivate(TDeleteGroupReplyData *q);
    ~TDeleteGroupReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteGroupReplyDataPrivate)
};

/*============================================================================
================================ TDeleteGroupReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteGroupReplyDataPrivate::TDeleteGroupReplyDataPrivate(TDeleteGroupReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteGroupReplyDataPrivate::~TDeleteGroupReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteGroupReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteGroupReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteGroupReplyData::TDeleteGroupReplyData() :
    BBase(*new TDeleteGroupReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteGroupReplyData::TDeleteGroupReplyData(const TDeleteGroupReplyData &other) :
    BBase(*new TDeleteGroupReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteGroupReplyData::~TDeleteGroupReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TDeleteGroupReplyData &TDeleteGroupReplyData::operator =(const TDeleteGroupReplyData &/*other*/)
{
    //B_D(TDeleteGroupReplyData);
    //const TDeleteGroupReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TDeleteGroupReplyData::operator ==(const TDeleteGroupReplyData &/*other*/) const
{
    //const B_D(TDeleteGroupReplyData);
    //const TDeleteGroupReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TDeleteGroupReplyData::operator !=(const TDeleteGroupReplyData &other) const
{
    return !(*this == other);
}

TDeleteGroupReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteGroupReplyData &/*data*/)
{
    //const TDeleteGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteGroupReplyData &/*data*/)
{
    //TDeleteGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteGroupReplyData &/*data*/)
{
    //const TDeleteGroupReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteGroupReplyData(" << ")";
    return dbg.space();
}
