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

#include "tgetsamplepreviewreplydata.h"

#include "tbinaryfile.h"
#include "tbinaryfilelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSamplePreviewReplyDataPrivate ===========
============================================================================*/

class TGetSamplePreviewReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSamplePreviewReplyData)
public:
    TBinaryFileList extraFiles;
    TBinaryFile mainFile;
public:
    explicit TGetSamplePreviewReplyDataPrivate(TGetSamplePreviewReplyData *q);
    ~TGetSamplePreviewReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSamplePreviewReplyDataPrivate)
};

/*============================================================================
================================ TGetSamplePreviewReplyDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSamplePreviewReplyDataPrivate::TGetSamplePreviewReplyDataPrivate(TGetSamplePreviewReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetSamplePreviewReplyDataPrivate::~TGetSamplePreviewReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSamplePreviewReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSamplePreviewReplyData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSamplePreviewReplyData::TGetSamplePreviewReplyData() :
    BBase(*new TGetSamplePreviewReplyDataPrivate(this))
{
    d_func()->init();
}

TGetSamplePreviewReplyData::TGetSamplePreviewReplyData(const TGetSamplePreviewReplyData &other) :
    BBase(*new TGetSamplePreviewReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSamplePreviewReplyData::~TGetSamplePreviewReplyData()
{
    //
}

/*============================== Public methods ============================*/

TBinaryFileList &TGetSamplePreviewReplyData::extraFiles()
{
    return d_func()->extraFiles;
}

const TBinaryFileList &TGetSamplePreviewReplyData::extraFiles() const
{
    return d_func()->extraFiles;
}

TBinaryFile &TGetSamplePreviewReplyData::mainFile()
{
    return d_func()->mainFile;
}

const TBinaryFile &TGetSamplePreviewReplyData::mainFile() const
{
    return d_func()->mainFile;
}

void TGetSamplePreviewReplyData::setExtraFiles(const TBinaryFileList &extraFiles)
{
    d_func()->extraFiles = extraFiles;
}

void TGetSamplePreviewReplyData::setMainFile(const TBinaryFile &file)
{
    d_func()->mainFile = file;
}

/*============================== Public operators ==========================*/

TGetSamplePreviewReplyData &TGetSamplePreviewReplyData::operator =(const TGetSamplePreviewReplyData &other)
{
    B_D(TGetSamplePreviewReplyData);
    const TGetSamplePreviewReplyDataPrivate *dd = other.d_func();
    d->extraFiles = dd->extraFiles;
    d->mainFile = dd->mainFile;
    return *this;
}

bool TGetSamplePreviewReplyData::operator ==(const TGetSamplePreviewReplyData &other) const
{
    const B_D(TGetSamplePreviewReplyData);
    const TGetSamplePreviewReplyDataPrivate *dd = other.d_func();
    return d->extraFiles == dd->extraFiles && d->mainFile == dd->mainFile;
}

bool TGetSamplePreviewReplyData::operator !=(const TGetSamplePreviewReplyData &other) const
{
    return !(*this == other);
}

TGetSamplePreviewReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSamplePreviewReplyData &data)
{
    const TGetSamplePreviewReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("extra_files", d->extraFiles);
    m.insert("main_file", d->mainFile);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSamplePreviewReplyData &data)
{
    TGetSamplePreviewReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->extraFiles = m.value("extra_files").value<TBinaryFileList>();
    d->mainFile = m.value("main_file").value<TBinaryFile>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSamplePreviewReplyData &/*data*/)
{
    //const TGetSamplePreviewReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSamplePreviewReplyData(" << ")";
    return dbg.space();
}
