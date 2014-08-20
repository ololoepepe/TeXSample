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

#include "tsampletype.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSampleTypePrivate ===========================
============================================================================*/

class TSampleTypePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSampleType)
public:
    TSampleType::SampleType type;
public:
   explicit TSampleTypePrivate(TSampleType *q);
    ~TSampleTypePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSampleTypePrivate)
};

/*============================================================================
================================ TSampleTypePrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TSampleTypePrivate::TSampleTypePrivate(TSampleType *q) :
    BBasePrivate(q)
{
    //
}

TSampleTypePrivate::~TSampleTypePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSampleTypePrivate::init()
{
    type = TSampleType::Unverified;
}

/*============================================================================
================================ TSampleType =================================
============================================================================*/

/*============================== Static public methods =====================*/

QList<TSampleType> TSampleType::allTypes()
{
    QList<TSampleType> list;
    list << Unverified;
    list << Approved;
    list << Rejected;
    return list;
}

QString TSampleType::sampleTypeToString(TSampleType type, bool singular)
{
    return tr(sampleTypeToStringNoTr(type, singular).toUtf8().constData());
}

QString TSampleType::sampleTypeToStringNoTr(TSampleType type, bool singular)
{
    switch (type)
    {
    case Unverified:
        return singular ? QT_TRANSLATE_NOOP("TSampleType singular", "Unverified") :
                          QT_TRANSLATE_NOOP("TSampleType plural", "Unverified");
    case Approved:
        return singular ? QT_TRANSLATE_NOOP("TSampleType singular", "Approved") :
                          QT_TRANSLATE_NOOP("TSampleType plural", "Approved");
    case Rejected:
        return singular ? QT_TRANSLATE_NOOP("TSampleType singular", "Rejected") :
                          QT_TRANSLATE_NOOP("TSampleType plural", "Rejected");
    default:
        return "";
    }
}

/*============================== Public constructors =======================*/

TSampleType::TSampleType(int type) :
    BBase(*new TSampleTypePrivate(this))
{
    d_func()->init();
    *this = type;
}

TSampleType::TSampleType(const TSampleType &other) :
    BBase(*new TSampleTypePrivate(this))
{
    d_func()->init();
    *this = other;
}

TSampleType::~TSampleType()
{
    //
}

/*============================== Public methods ============================*/

QString TSampleType::toString() const
{
    return sampleTypeToString(d_func()->type);
}

QString TSampleType::toStringNoTr() const
{
    return sampleTypeToStringNoTr(d_func()->type);
}

TSampleType::SampleType TSampleType::type() const
{
    return d_func()->type;
}

/*============================== Public operators ==========================*/

TSampleType &TSampleType::operator =(const TSampleType &other)
{
    d_func()->type = other.d_func()->type;
    return *this;
}

TSampleType &TSampleType::operator =(int type)
{
    static const QList<SampleType> Types = QList<SampleType>() << Unverified << Approved << Rejected;
    d_func()->type = enum_cast<SampleType>(type, Types, Unverified);
    return *this;
}

bool TSampleType::operator ==(const TSampleType &other) const
{
    return d_func()->type == other.d_func()->type;
}

bool TSampleType::operator !=(const TSampleType &other) const
{
    return !(*this == other);
}

TSampleType::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TSampleType::operator int() const
{
    return (int) d_func()->type;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSampleType &type)
{
    QVariantMap m;
    m.insert("type", (int) type.d_func()->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSampleType &type)
{
    QVariantMap m;
    stream >> m;
    type = m.value("type").toInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSampleType &type)
{
    dbg.nospace() << "TSampleType(" << type.toStringNoTr() << ")";
    return dbg.space();
}
