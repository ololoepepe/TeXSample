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

#include "teditsamplereplydata.h"

#include "tsampleinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSampleReplyDataPrivate =================
============================================================================*/

class TEditSampleReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSampleReplyData)
public:
    TSampleInfo sampleInfo;
public:
    explicit TEditSampleReplyDataPrivate(TEditSampleReplyData *q);
    ~TEditSampleReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSampleReplyDataPrivate)
};

/*============================================================================
================================ TEditSampleReplyDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleReplyDataPrivate::TEditSampleReplyDataPrivate(TEditSampleReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditSampleReplyDataPrivate::~TEditSampleReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditSampleReplyData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleReplyData::TEditSampleReplyData() :
    BBase(*new TEditSampleReplyDataPrivate(this))
{
    d_func()->init();
}

TEditSampleReplyData::TEditSampleReplyData(const TEditSampleReplyData &other) :
    BBase(*new TEditSampleReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSampleReplyData::~TEditSampleReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleReplyData::setSampleInfo(const TSampleInfo &info)
{
    d_func()->sampleInfo = info;
}

TSampleInfo TEditSampleReplyData::sampleInfo() const
{
    return d_func()->sampleInfo;
}

/*============================== Public operators ==========================*/

TEditSampleReplyData &TEditSampleReplyData::operator =(const TEditSampleReplyData &other)
{
    B_D(TEditSampleReplyData);
    const TEditSampleReplyDataPrivate *dd = other.d_func();
    d->sampleInfo = dd->sampleInfo;
    return *this;
}

bool TEditSampleReplyData::operator ==(const TEditSampleReplyData &other) const
{
    const B_D(TEditSampleReplyData);
    const TEditSampleReplyDataPrivate *dd = other.d_func();
    return d->sampleInfo == dd->sampleInfo;
}

bool TEditSampleReplyData::operator !=(const TEditSampleReplyData &other) const
{
    return !(*this == other);
}

TEditSampleReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSampleReplyData &data)
{
    const TEditSampleReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("sample_info", d->sampleInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSampleReplyData &data)
{
    TEditSampleReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->sampleInfo = m.value("sample_info").value<TSampleInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSampleReplyData &/*data*/)
{
    //const TEditSampleReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSampleReplyData(" << ")";
    return dbg.space();
}
