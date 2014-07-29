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

#include "tchangepasswordreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TChangePasswordReplyDataPrivate =============
============================================================================*/

class TChangePasswordReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TChangePasswordReplyData)
public:
    explicit TChangePasswordReplyDataPrivate(TChangePasswordReplyData *q);
    ~TChangePasswordReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TChangePasswordReplyDataPrivate)
};

/*============================================================================
================================ TChangePasswordReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TChangePasswordReplyDataPrivate::TChangePasswordReplyDataPrivate(TChangePasswordReplyData *q) :
    BBasePrivate(q)
{
    //
}

TChangePasswordReplyDataPrivate::~TChangePasswordReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TChangePasswordReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TChangePasswordReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TChangePasswordReplyData::TChangePasswordReplyData() :
    BBase(*new TChangePasswordReplyDataPrivate(this))
{
    d_func()->init();
}

TChangePasswordReplyData::TChangePasswordReplyData(const TChangePasswordReplyData &other) :
    BBase(*new TChangePasswordReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TChangePasswordReplyData::~TChangePasswordReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TChangePasswordReplyData &TChangePasswordReplyData::operator =(const TChangePasswordReplyData &/*other*/)
{
    //B_D(TChangePasswordReplyData);
    //const TChangePasswordReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TChangePasswordReplyData::operator ==(const TChangePasswordReplyData &/*other*/) const
{
    //const B_D(TChangePasswordReplyData);
    //const TChangePasswordReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TChangePasswordReplyData::operator !=(const TChangePasswordReplyData &other) const
{
    return !(*this == other);
}

TChangePasswordReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TChangePasswordReplyData &/*data*/)
{
    //const TChangePasswordReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TChangePasswordReplyData &/*data*/)
{
    //TChangePasswordReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TChangePasswordReplyData &/*data*/)
{
    //const TChangePasswordReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TChangePasswordReplyData(" << ")";
    return dbg.space();
}
