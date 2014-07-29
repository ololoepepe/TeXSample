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

#include "teditsampleadminreplydata.h"

#include "tsampleinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSampleAdminReplyDataPrivate ============
============================================================================*/

class TEditSampleAdminReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSampleAdminReplyData)
public:
    TSampleInfo sampleInfo;
public:
    explicit TEditSampleAdminReplyDataPrivate(TEditSampleAdminReplyData *q);
    ~TEditSampleAdminReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSampleAdminReplyDataPrivate)
};

/*============================================================================
================================ TEditSampleAdminReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleAdminReplyDataPrivate::TEditSampleAdminReplyDataPrivate(TEditSampleAdminReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditSampleAdminReplyDataPrivate::~TEditSampleAdminReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleAdminReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditSampleAdminReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleAdminReplyData::TEditSampleAdminReplyData() :
    BBase(*new TEditSampleAdminReplyDataPrivate(this))
{
    d_func()->init();
}

TEditSampleAdminReplyData::TEditSampleAdminReplyData(const TEditSampleAdminReplyData &other) :
    BBase(*new TEditSampleAdminReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSampleAdminReplyData::~TEditSampleAdminReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleAdminReplyData::setSampleInfo(const TSampleInfo &info)
{
    d_func()->sampleInfo = info;
}

TSampleInfo TEditSampleAdminReplyData::sampleInfo() const
{
    return d_func()->sampleInfo;
}

/*============================== Public operators ==========================*/

TEditSampleAdminReplyData &TEditSampleAdminReplyData::operator =(const TEditSampleAdminReplyData &other)
{
    B_D(TEditSampleAdminReplyData);
    const TEditSampleAdminReplyDataPrivate *dd = other.d_func();
    d->sampleInfo = dd->sampleInfo;
    return *this;
}

bool TEditSampleAdminReplyData::operator ==(const TEditSampleAdminReplyData &other) const
{
    const B_D(TEditSampleAdminReplyData);
    const TEditSampleAdminReplyDataPrivate *dd = other.d_func();
    return d->sampleInfo == dd->sampleInfo;
}

bool TEditSampleAdminReplyData::operator !=(const TEditSampleAdminReplyData &other) const
{
    return !(*this == other);
}

TEditSampleAdminReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminReplyData &data)
{
    const TEditSampleAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("sample_info", d->sampleInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSampleAdminReplyData &data)
{
    TEditSampleAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->sampleInfo = m.value("sample_info").value<TSampleInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSampleAdminReplyData &/*data*/)
{
    //const TEditSampleAdminReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSampleAdminReplyData(" << ")";
    return dbg.space();
}
