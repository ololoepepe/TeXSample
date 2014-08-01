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

#include "tdeleteinvitesreplydata.h"

#include "tidlist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteInvitesReplyDataPrivate ==============
============================================================================*/

class TDeleteInvitesReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteInvitesReplyData)
public:
    TIdList identifiers;
public:
    explicit TDeleteInvitesReplyDataPrivate(TDeleteInvitesReplyData *q);
    ~TDeleteInvitesReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteInvitesReplyDataPrivate)
};

/*============================================================================
================================ TDeleteInvitesReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesReplyDataPrivate::TDeleteInvitesReplyDataPrivate(TDeleteInvitesReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteInvitesReplyDataPrivate::~TDeleteInvitesReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteInvitesReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteInvitesReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesReplyData::TDeleteInvitesReplyData() :
    BBase(*new TDeleteInvitesReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteInvitesReplyData::TDeleteInvitesReplyData(const TDeleteInvitesReplyData &other) :
    BBase(*new TDeleteInvitesReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteInvitesReplyData::~TDeleteInvitesReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TDeleteInvitesReplyData::identifiers() const
{
    return d_func()->identifiers;
}

void TDeleteInvitesReplyData::setIdentifiers(const TIdList &identifiers)
{
    d_func()->identifiers = identifiers;
    bRemoveDuplicates(d_func()->identifiers);
    d_func()->identifiers.removeAll(0);
}

/*============================== Public operators ==========================*/

TDeleteInvitesReplyData &TDeleteInvitesReplyData::operator =(const TDeleteInvitesReplyData &other)
{
    B_D(TDeleteInvitesReplyData);
    const TDeleteInvitesReplyDataPrivate *dd = other.d_func();
    d->identifiers = dd->identifiers;
    return *this;
}

bool TDeleteInvitesReplyData::operator ==(const TDeleteInvitesReplyData &other) const
{
    const B_D(TDeleteInvitesReplyData);
    const TDeleteInvitesReplyDataPrivate *dd = other.d_func();
    return d->identifiers == dd->identifiers;
}

bool TDeleteInvitesReplyData::operator !=(const TDeleteInvitesReplyData &other) const
{
    return !(*this == other);
}

TDeleteInvitesReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesReplyData &data)
{
    const TDeleteInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifiers", d->identifiers);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteInvitesReplyData &data)
{
    TDeleteInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifiers = m.value("identifiers").value<TIdList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteInvitesReplyData &/*data*/)
{
    //const TDeleteInvitesReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteInvitesReplyData(" << ")";
    return dbg.space();
}
