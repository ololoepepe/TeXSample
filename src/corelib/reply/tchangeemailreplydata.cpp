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

#include "tchangeemailreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TChangeEmailReplyDataPrivate ================
============================================================================*/

class TChangeEmailReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TChangeEmailReplyData)
public:
    explicit TChangeEmailReplyDataPrivate(TChangeEmailReplyData *q);
    ~TChangeEmailReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TChangeEmailReplyDataPrivate)
};

/*============================================================================
================================ TChangeEmailReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TChangeEmailReplyDataPrivate::TChangeEmailReplyDataPrivate(TChangeEmailReplyData *q) :
    BBasePrivate(q)
{
    //
}

TChangeEmailReplyDataPrivate::~TChangeEmailReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TChangeEmailReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TChangeEmailReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TChangeEmailReplyData::TChangeEmailReplyData() :
    BBase(*new TChangeEmailReplyDataPrivate(this))
{
    d_func()->init();
}

TChangeEmailReplyData::TChangeEmailReplyData(const TChangeEmailReplyData &other) :
    BBase(*new TChangeEmailReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TChangeEmailReplyData::~TChangeEmailReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TChangeEmailReplyData &TChangeEmailReplyData::operator =(const TChangeEmailReplyData &/*other*/)
{
    //B_D(TChangeEmailReplyData);
    //const TChangeEmailReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TChangeEmailReplyData::operator ==(const TChangeEmailReplyData &/*other*/) const
{
    //const B_D(TChangeEmailReplyData);
    //const TChangeEmailReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TChangeEmailReplyData::operator !=(const TChangeEmailReplyData &other) const
{
    return !(*this == other);
}

TChangeEmailReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TChangeEmailReplyData &/*data*/)
{
    //const TChangeEmailReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TChangeEmailReplyData &/*data*/)
{
    //TChangeEmailReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TChangeEmailReplyData &/*data*/)
{
    //const TChangeEmailReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TChangeEmailReplyData(" << ")";
    return dbg.space();
}
