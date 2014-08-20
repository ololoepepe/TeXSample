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

#include "tgetuserconnectioninfolistrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
============================= TGetUserConnectionInfoListRequestDataPrivate ===
============================================================================*/

class TGetUserConnectionInfoListRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserConnectionInfoListRequestData)
public:
    QString matchPattern;
    TGetUserConnectionInfoListRequestData::MatchType matchType;
public:
    explicit TGetUserConnectionInfoListRequestDataPrivate(TGetUserConnectionInfoListRequestData *q);
    ~TGetUserConnectionInfoListRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserConnectionInfoListRequestDataPrivate)
};


/*============================================================================
============================= TGetUserConnectionInfoListRequestDataPrivate ===
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserConnectionInfoListRequestDataPrivate::TGetUserConnectionInfoListRequestDataPrivate(
        TGetUserConnectionInfoListRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserConnectionInfoListRequestDataPrivate::~TGetUserConnectionInfoListRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserConnectionInfoListRequestDataPrivate::init()
{
    matchType = TGetUserConnectionInfoListRequestData::MatchLoginAndUniqueId;
}

/*============================================================================
================================ TGetUserConnectionInfoListRequestData =======
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserConnectionInfoListRequestData::TGetUserConnectionInfoListRequestData() :
    BBase(*new TGetUserConnectionInfoListRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserConnectionInfoListRequestData::TGetUserConnectionInfoListRequestData(
        const TGetUserConnectionInfoListRequestData &other) :
    BBase(*new TGetUserConnectionInfoListRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserConnectionInfoListRequestData::~TGetUserConnectionInfoListRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserConnectionInfoListRequestData::clear()
{
    B_D(TGetUserConnectionInfoListRequestData);
    d->matchPattern.clear();
    d->matchType = MatchLoginAndUniqueId;
}

bool TGetUserConnectionInfoListRequestData::isValid() const
{
    return !d_func()->matchPattern.isEmpty();
}

QString TGetUserConnectionInfoListRequestData::matchPattern() const
{
    return d_func()->matchPattern;
}

TGetUserConnectionInfoListRequestData::MatchType TGetUserConnectionInfoListRequestData::matchType() const
{
    return d_func()->matchType;
}

void TGetUserConnectionInfoListRequestData::setMatchPattern(const QString &pattern)
{
    d_func()->matchPattern = pattern;
}

void TGetUserConnectionInfoListRequestData::setMatchType(MatchType type)
{
    d_func()->matchType = enum_cast<MatchType>(type, MatchLoginAndUniqueId, MatchUniqueId);
}

/*============================== Public operators ==========================*/

TGetUserConnectionInfoListRequestData &TGetUserConnectionInfoListRequestData::operator =(
        const TGetUserConnectionInfoListRequestData &other)
{
    B_D(TGetUserConnectionInfoListRequestData);
    const TGetUserConnectionInfoListRequestDataPrivate *dd = other.d_func();
    d->matchPattern = dd->matchPattern;
    d->matchType = dd->matchType;
    return *this;
}

bool TGetUserConnectionInfoListRequestData::operator ==(const TGetUserConnectionInfoListRequestData &other) const
{
    const B_D(TGetUserConnectionInfoListRequestData);
    const TGetUserConnectionInfoListRequestDataPrivate *dd = other.d_func();
    return d->matchPattern == dd->matchPattern && d->matchType == dd->matchType;
}

bool TGetUserConnectionInfoListRequestData::operator !=(const TGetUserConnectionInfoListRequestData &other) const
{
    return !(*this == other);
}

TGetUserConnectionInfoListRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserConnectionInfoListRequestData &data)
{
    const TGetUserConnectionInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("match_pattern", d->matchPattern);
    m.insert("match_type", int(d->matchType));
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserConnectionInfoListRequestData &data)
{
    TGetUserConnectionInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->matchPattern = m.value("match_pattern").toString();
    d->matchType = enum_cast<TGetUserConnectionInfoListRequestData::MatchType>(
                m.value("match_type"), TGetUserConnectionInfoListRequestData::MatchLoginAndUniqueId,
                TGetUserConnectionInfoListRequestData::MatchUniqueId);
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserConnectionInfoListRequestData &/*data*/)
{
    //const TGetUserConnectionInfoListRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserConnectionInfoListRequestData(" << ")";
    return dbg.space();
}
