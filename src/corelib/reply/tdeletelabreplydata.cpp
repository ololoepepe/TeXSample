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

#include "tdeletelabreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteLabReplyDataPrivate ==============
============================================================================*/

class TDeleteLabReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteLabReplyData)
public:
    explicit TDeleteLabReplyDataPrivate(TDeleteLabReplyData *q);
    ~TDeleteLabReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteLabReplyDataPrivate)
};

/*============================================================================
================================ TDeleteLabReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteLabReplyDataPrivate::TDeleteLabReplyDataPrivate(TDeleteLabReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteLabReplyDataPrivate::~TDeleteLabReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteLabReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteLabReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteLabReplyData::TDeleteLabReplyData() :
    BBase(*new TDeleteLabReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteLabReplyData::TDeleteLabReplyData(const TDeleteLabReplyData &other) :
    BBase(*new TDeleteLabReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteLabReplyData::~TDeleteLabReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TDeleteLabReplyData &TDeleteLabReplyData::operator =(const TDeleteLabReplyData &/*other*/)
{
    //B_D(TDeleteLabReplyData);
    //const TDeleteLabReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TDeleteLabReplyData::operator ==(const TDeleteLabReplyData &/*other*/) const
{
    //const B_D(TDeleteLabReplyData);
    //const TDeleteLabReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TDeleteLabReplyData::operator !=(const TDeleteLabReplyData &other) const
{
    return !(*this == other);
}

TDeleteLabReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteLabReplyData &/*data*/)
{
    //const TDeleteLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteLabReplyData &/*data*/)
{
    //TDeleteLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteLabReplyData &/*data*/)
{
    //const TDeleteLabReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteLabReplyData(" << ")";
    return dbg.space();
}
