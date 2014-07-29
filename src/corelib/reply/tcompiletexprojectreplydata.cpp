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

#include "tcompiletexprojectreplydata.h"

#include "tbinaryfilelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCompileTexProjectReplyDataPrivate ==========
============================================================================*/

class TCompileTexProjectReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCompileTexProjectReplyData)
public:
    int exitCode;
    TBinaryFileList files;
    QString output;
public:
    explicit TCompileTexProjectReplyDataPrivate(TCompileTexProjectReplyData *q);
    ~TCompileTexProjectReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCompileTexProjectReplyDataPrivate)
};

/*============================================================================
================================ TCompileTexProjectReplyDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TCompileTexProjectReplyDataPrivate::TCompileTexProjectReplyDataPrivate(TCompileTexProjectReplyData *q) :
    BBasePrivate(q)
{
    //
}

TCompileTexProjectReplyDataPrivate::~TCompileTexProjectReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCompileTexProjectReplyDataPrivate::init()
{
    exitCode = 0;
}

/*============================================================================
================================ TCompileTexProjectReplyData =================
============================================================================*/

/*============================== Public constructors =======================*/

TCompileTexProjectReplyData::TCompileTexProjectReplyData() :
    BBase(*new TCompileTexProjectReplyDataPrivate(this))
{
    d_func()->init();
}

TCompileTexProjectReplyData::TCompileTexProjectReplyData(const TCompileTexProjectReplyData &other) :
    BBase(*new TCompileTexProjectReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCompileTexProjectReplyData::~TCompileTexProjectReplyData()
{
    //
}

/*============================== Public methods ============================*/

int TCompileTexProjectReplyData::exitCode() const
{
    return d_func()->exitCode;
}

TBinaryFileList TCompileTexProjectReplyData::files() const
{
    return d_func()->files;
}

QString TCompileTexProjectReplyData::output() const
{
    return d_func()->output;
}

void TCompileTexProjectReplyData::setExitCode(int code)
{
    d_func()->exitCode = code;
}

void TCompileTexProjectReplyData::setFiles(const TBinaryFileList &files)
{
    d_func()->files = files;
}

void TCompileTexProjectReplyData::setOutput(const QString &output)
{
    d_func()->output = output;
}

/*============================== Public operators ==========================*/

TCompileTexProjectReplyData &TCompileTexProjectReplyData::operator =(const TCompileTexProjectReplyData &other)
{
    B_D(TCompileTexProjectReplyData);
    const TCompileTexProjectReplyDataPrivate *dd = other.d_func();
    d->exitCode = dd->exitCode;
    d->files = dd->files;
    d->output = dd->output;
    return *this;
}

bool TCompileTexProjectReplyData::operator ==(const TCompileTexProjectReplyData &other) const
{
    const B_D(TCompileTexProjectReplyData);
    const TCompileTexProjectReplyDataPrivate *dd = other.d_func();
    return d->exitCode == dd->exitCode && d->files == dd->files && d->output == dd->output;
}

bool TCompileTexProjectReplyData::operator !=(const TCompileTexProjectReplyData &other) const
{
    return !(*this == other);
}

TCompileTexProjectReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompileTexProjectReplyData &data)
{
    const TCompileTexProjectReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("exit_code", d->exitCode);
    m.insert("files", d->files);
    m.insert("ouptut", d->output);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompileTexProjectReplyData &data)
{
    TCompileTexProjectReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->exitCode = m.value("exit_code").toInt();
    d->files = m.value("files").value<TBinaryFileList>();
    d->output = m.value("output").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompileTexProjectReplyData &/*data*/)
{
    //const TCompileTexProjectReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TCompileTexProjectReplyData(" << ")";
    return dbg.space();
}
