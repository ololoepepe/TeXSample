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

#include "tgetsamplesourcereplydata.h"

#include "ttexproject.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleSourceReplyDataPrivate ============
============================================================================*/

class TGetSampleSourceReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleSourceReplyData)
public:
    TTexProject project;
public:
    explicit TGetSampleSourceReplyDataPrivate(TGetSampleSourceReplyData *q);
    ~TGetSampleSourceReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleSourceReplyDataPrivate)
};

/*============================================================================
================================ TGetSampleSourceReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleSourceReplyDataPrivate::TGetSampleSourceReplyDataPrivate(TGetSampleSourceReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleSourceReplyDataPrivate::~TGetSampleSourceReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleSourceReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSampleSourceReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleSourceReplyData::TGetSampleSourceReplyData() :
    BBase(*new TGetSampleSourceReplyDataPrivate(this))
{
    d_func()->init();
}

TGetSampleSourceReplyData::TGetSampleSourceReplyData(const TGetSampleSourceReplyData &other) :
    BBase(*new TGetSampleSourceReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleSourceReplyData::~TGetSampleSourceReplyData()
{
    //
}

/*============================== Public methods ============================*/

TTexProject &TGetSampleSourceReplyData::project()
{
    return d_func()->project;
}

const TTexProject &TGetSampleSourceReplyData::project() const
{
    return d_func()->project;
}

void TGetSampleSourceReplyData::setProject(const TTexProject &project)
{
    d_func()->project = project;
}

/*============================== Public operators ==========================*/

TGetSampleSourceReplyData &TGetSampleSourceReplyData::operator =(const TGetSampleSourceReplyData &other)
{
    B_D(TGetSampleSourceReplyData);
    const TGetSampleSourceReplyDataPrivate *dd = other.d_func();
    d->project = dd->project;
    return *this;
}

bool TGetSampleSourceReplyData::operator ==(const TGetSampleSourceReplyData &other) const
{
    const B_D(TGetSampleSourceReplyData);
    const TGetSampleSourceReplyDataPrivate *dd = other.d_func();
    return d->project == dd->project;
}

bool TGetSampleSourceReplyData::operator !=(const TGetSampleSourceReplyData &other) const
{
    return !(*this == other);
}

TGetSampleSourceReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceReplyData &data)
{
    const TGetSampleSourceReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("project", d->project);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleSourceReplyData &data)
{
    TGetSampleSourceReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->project = m.value("project").value<TTexProject>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleSourceReplyData &/*data*/)
{
    //const TGetSampleSourceReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleSourceReplyData(" << ")";
    return dbg.space();
}
