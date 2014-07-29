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

#include "tlogreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLogReplyDataPrivate ========================
============================================================================*/

class TLogReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLogReplyData)
public:
    explicit TLogReplyDataPrivate(TLogReplyData *q);
    ~TLogReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLogReplyDataPrivate)
};

/*============================================================================
================================ TLogReplyDataPrivate ========================
============================================================================*/

/*============================== Public constructors =======================*/

TLogReplyDataPrivate::TLogReplyDataPrivate(TLogReplyData *q) :
    BBasePrivate(q)
{
    //
}

TLogReplyDataPrivate::~TLogReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLogReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TLogReplyData ===============================
============================================================================*/

/*============================== Public constructors =======================*/

TLogReplyData::TLogReplyData() :
    BBase(*new TLogReplyDataPrivate(this))
{
    d_func()->init();
}

TLogReplyData::TLogReplyData(const TLogReplyData &other) :
    BBase(*new TLogReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLogReplyData::~TLogReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TLogReplyData &TLogReplyData::operator =(const TLogReplyData &/*other*/)
{
    //B_D(TLogReplyData);
    //const TLogReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TLogReplyData::operator ==(const TLogReplyData &/*other*/) const
{
    //const B_D(TLogReplyData);
    //const TLogReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TLogReplyData::operator !=(const TLogReplyData &other) const
{
    return !(*this == other);
}

TLogReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLogReplyData &/*data*/)
{
    //const TLogReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLogReplyData &/*data*/)
{
    //TLogReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TLogReplyData &/*data*/)
{
    //const TLogReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TLogReplyData(" << ")";
    return dbg.space();
}
