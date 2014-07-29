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

#include "texecutecommandrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TExecuteCommandRequestDataPrivate ===========
============================================================================*/

class TExecuteCommandRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TExecuteCommandRequestData)
public:
    QStringList arguments;
    QString command;
public:
    explicit TExecuteCommandRequestDataPrivate(TExecuteCommandRequestData *q);
    ~TExecuteCommandRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TExecuteCommandRequestDataPrivate)
};

/*============================================================================
================================ TExecuteCommandRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TExecuteCommandRequestDataPrivate::TExecuteCommandRequestDataPrivate(TExecuteCommandRequestData *q) :
    BBasePrivate(q)
{
    //
}

TExecuteCommandRequestDataPrivate::~TExecuteCommandRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TExecuteCommandRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TExecuteCommandRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TExecuteCommandRequestData::TExecuteCommandRequestData() :
    BBase(*new TExecuteCommandRequestDataPrivate(this))
{
    d_func()->init();
}

TExecuteCommandRequestData::TExecuteCommandRequestData(const TExecuteCommandRequestData &other) :
    BBase(*new TExecuteCommandRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TExecuteCommandRequestData::~TExecuteCommandRequestData()
{
    //
}

/*============================== Public methods ============================*/

QStringList TExecuteCommandRequestData::arguments() const
{
    return d_func()->arguments;
}

void TExecuteCommandRequestData::clear()
{
    B_D(TExecuteCommandRequestData);
    d->arguments.clear();
    d->command.clear();
}

QString TExecuteCommandRequestData::command() const
{
    return d_func()->command;
}

bool TExecuteCommandRequestData::isValid() const
{
    const B_D(TExecuteCommandRequestData);
    return !d->command.isEmpty();
}

void TExecuteCommandRequestData::setArguments(const QStringList &arguments)
{
    d_func()->arguments = arguments;
}

void TExecuteCommandRequestData::setCommand(const QString &command)
{
    d_func()->command = Texsample::testCommand(command) ? command : QString();
}

/*============================== Public operators ==========================*/

TExecuteCommandRequestData &TExecuteCommandRequestData::operator =(const TExecuteCommandRequestData &other)
{
    B_D(TExecuteCommandRequestData);
    const TExecuteCommandRequestDataPrivate *dd = other.d_func();
    d->arguments = dd->arguments;
    d->command = dd->command;
    return *this;
}

bool TExecuteCommandRequestData::operator ==(const TExecuteCommandRequestData &other) const
{
    const B_D(TExecuteCommandRequestData);
    const TExecuteCommandRequestDataPrivate *dd = other.d_func();
    return d->arguments == dd->arguments && d->command == dd->command;
}

bool TExecuteCommandRequestData::operator !=(const TExecuteCommandRequestData &other) const
{
    return !(*this == other);
}

TExecuteCommandRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TExecuteCommandRequestData &data)
{
    const TExecuteCommandRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("arguments", d->arguments);
    m.insert("command", d->command);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TExecuteCommandRequestData &data)
{
    TExecuteCommandRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->arguments = m.value("arguments").toStringList();
    d->command = m.value("command").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TExecuteCommandRequestData &/*data*/)
{
    //const TExecuteCommandRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TExecuteCommandRequestData(" << ")";
    return dbg.space();
}
