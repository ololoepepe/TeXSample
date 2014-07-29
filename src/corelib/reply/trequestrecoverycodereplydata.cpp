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

#include "trequestrecoverycodereplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRequestRecoveryCodeReplyDataPrivate ========
============================================================================*/

class TRequestRecoveryCodeReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRequestRecoveryCodeReplyData)
public:
    explicit TRequestRecoveryCodeReplyDataPrivate(TRequestRecoveryCodeReplyData *q);
    ~TRequestRecoveryCodeReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRequestRecoveryCodeReplyDataPrivate)
};

/*============================================================================
================================ TRequestRecoveryCodeReplyDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TRequestRecoveryCodeReplyDataPrivate::TRequestRecoveryCodeReplyDataPrivate(TRequestRecoveryCodeReplyData *q) :
    BBasePrivate(q)
{
    //
}

TRequestRecoveryCodeReplyDataPrivate::~TRequestRecoveryCodeReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRequestRecoveryCodeReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRequestRecoveryCodeReplyData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TRequestRecoveryCodeReplyData::TRequestRecoveryCodeReplyData() :
    BBase(*new TRequestRecoveryCodeReplyDataPrivate(this))
{
    d_func()->init();
}

TRequestRecoveryCodeReplyData::TRequestRecoveryCodeReplyData(const TRequestRecoveryCodeReplyData &other) :
    BBase(*new TRequestRecoveryCodeReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRequestRecoveryCodeReplyData::~TRequestRecoveryCodeReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TRequestRecoveryCodeReplyData &TRequestRecoveryCodeReplyData::operator =(
        const TRequestRecoveryCodeReplyData &/*other*/)
{
    //B_D(TRequestRecoveryCodeReplyData);
    //const TRequestRecoveryCodeReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TRequestRecoveryCodeReplyData::operator ==(const TRequestRecoveryCodeReplyData &/*other*/) const
{
    //const B_D(TRequestRecoveryCodeReplyData);
    //const TRequestRecoveryCodeReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TRequestRecoveryCodeReplyData::operator !=(const TRequestRecoveryCodeReplyData &other) const
{
    return !(*this == other);
}

TRequestRecoveryCodeReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeReplyData &/*data*/)
{
    //const TRequestRecoveryCodeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeReplyData &/*data*/)
{
    //TRequestRecoveryCodeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeReplyData &/*data*/)
{
    //const TRequestRecoveryCodeReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TRequestRecoveryCodeReplyData(" << ")";
    return dbg.space();
}
