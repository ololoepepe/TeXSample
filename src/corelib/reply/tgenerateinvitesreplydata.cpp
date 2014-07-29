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

#include "tgenerateinvitesreplydata.h"

#include "tinviteinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGenerateInvitesReplyDataPrivate ============
============================================================================*/

class TGenerateInvitesReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGenerateInvitesReplyData)
public:
    TInviteInfoList generatedInvites;
public:
    explicit TGenerateInvitesReplyDataPrivate(TGenerateInvitesReplyData *q);
    ~TGenerateInvitesReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGenerateInvitesReplyDataPrivate)
};

/*============================================================================
================================ TGenerateInvitesReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGenerateInvitesReplyDataPrivate::TGenerateInvitesReplyDataPrivate(TGenerateInvitesReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGenerateInvitesReplyDataPrivate::~TGenerateInvitesReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGenerateInvitesReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGenerateInvitesReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGenerateInvitesReplyData::TGenerateInvitesReplyData() :
    BBase(*new TGenerateInvitesReplyDataPrivate(this))
{
    d_func()->init();
}

TGenerateInvitesReplyData::TGenerateInvitesReplyData(const TGenerateInvitesReplyData &other) :
    BBase(*new TGenerateInvitesReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGenerateInvitesReplyData::~TGenerateInvitesReplyData()
{
    //
}

/*============================== Public methods ============================*/

TInviteInfoList TGenerateInvitesReplyData::generatedInvites() const
{
    return d_func()->generatedInvites;
}

void TGenerateInvitesReplyData::setGeneratedInvites(const TInviteInfoList &generatedInvites)
{
    d_func()->generatedInvites = generatedInvites;
}

/*============================== Public operators ==========================*/

TGenerateInvitesReplyData &TGenerateInvitesReplyData::operator =(const TGenerateInvitesReplyData &other)
{
    B_D(TGenerateInvitesReplyData);
    const TGenerateInvitesReplyDataPrivate *dd = other.d_func();
    d->generatedInvites = dd->generatedInvites;
    return *this;
}

bool TGenerateInvitesReplyData::operator ==(const TGenerateInvitesReplyData &other) const
{
    const B_D(TGenerateInvitesReplyData);
    const TGenerateInvitesReplyDataPrivate *dd = other.d_func();
    return d->generatedInvites == dd->generatedInvites;
}

bool TGenerateInvitesReplyData::operator !=(const TGenerateInvitesReplyData &other) const
{
    return !(*this == other);
}

TGenerateInvitesReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesReplyData &data)
{
    const TGenerateInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("generated_invites", d->generatedInvites);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGenerateInvitesReplyData &data)
{
    TGenerateInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->generatedInvites = m.value("generated_invites").value<TInviteInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGenerateInvitesReplyData &/*data*/)
{
    //const TGenerateInvitesReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGenerateInvitesReplyData(" << ")";
    return dbg.space();
}
