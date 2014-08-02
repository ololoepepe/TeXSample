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

#include "texecutecommandreplydata.h"

#include "tcommandmessage.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TExecuteCommandReplyDataPrivate =============
============================================================================*/

class TExecuteCommandReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TExecuteCommandReplyData)
public:
    QStringList arguments;
    TCommandMessage message;
    bool success;
public:
    explicit TExecuteCommandReplyDataPrivate(TExecuteCommandReplyData *q);
    ~TExecuteCommandReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TExecuteCommandReplyDataPrivate)
};

/*============================================================================
================================ TExecuteCommandReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TExecuteCommandReplyDataPrivate::TExecuteCommandReplyDataPrivate(TExecuteCommandReplyData *q) :
    BBasePrivate(q)
{
    //
}

TExecuteCommandReplyDataPrivate::~TExecuteCommandReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TExecuteCommandReplyDataPrivate::init()
{
    success = false;
}

/*============================================================================
================================ TExecuteCommandReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TExecuteCommandReplyData::TExecuteCommandReplyData() :
    BBase(*new TExecuteCommandReplyDataPrivate(this))
{
    d_func()->init();
}

TExecuteCommandReplyData::TExecuteCommandReplyData(const TExecuteCommandReplyData &other) :
    BBase(*new TExecuteCommandReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TExecuteCommandReplyData::~TExecuteCommandReplyData()
{
    //
}

/*============================== Public methods ============================*/

QStringList TExecuteCommandReplyData::arguments() const
{
    return d_func()->arguments;
}

TCommandMessage TExecuteCommandReplyData::message() const
{
    return d_func()->message;
}

void TExecuteCommandReplyData::setArguments(const QStringList &arguments)
{
    d_func()->arguments = arguments;
}

void TExecuteCommandReplyData::setMessage(const TCommandMessage &message)
{
    d_func()->message = message;
}

void TExecuteCommandReplyData::setSuccess(bool success)
{
    d_func()->success = success;
}

bool TExecuteCommandReplyData::success() const
{
    return d_func()->success;
}

/*============================== Public operators ==========================*/

TExecuteCommandReplyData &TExecuteCommandReplyData::operator =(const TExecuteCommandReplyData &other)
{
    B_D(TExecuteCommandReplyData);
    const TExecuteCommandReplyDataPrivate *dd = other.d_func();
    d->arguments = dd->arguments;
    d->message = dd->message;
    d->success = dd->success;
    return *this;
}

bool TExecuteCommandReplyData::operator ==(const TExecuteCommandReplyData &other) const
{
    const B_D(TExecuteCommandReplyData);
    const TExecuteCommandReplyDataPrivate *dd = other.d_func();
    return d->arguments == dd->arguments && d->message == dd->message && d->success == dd->success;
}

bool TExecuteCommandReplyData::operator !=(const TExecuteCommandReplyData &other) const
{
    return !(*this == other);
}

TExecuteCommandReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TExecuteCommandReplyData &data)
{
    const TExecuteCommandReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("arguments", d->arguments);
    m.insert("message", d->message);
    m.insert("success", d->success);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TExecuteCommandReplyData &data)
{
    TExecuteCommandReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->arguments = m.value("arguments").toStringList();
    d->message = m.value("message").value<TCommandMessage>();
    d->success = m.value("success").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TExecuteCommandReplyData &/*data*/)
{
    //const TExecuteCommandReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TExecuteCommandReplyData(" << ")";
    return dbg.space();
}
