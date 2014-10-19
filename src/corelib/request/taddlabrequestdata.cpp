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

#include "taddlabrequestdata.h"

#include "tauthorinfolist.h"
#include "tbinaryfilelist.h"
#include "tidlist.h"
#include "tlabdata.h"
#include "tlabdatalist.h"
#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTextTools>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddLabRequestDataPrivate ===================
============================================================================*/

class TAddLabRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddLabRequestData)
public:
    TAuthorInfoList authors;
    TLabDataList dataList;
    QString description;
    TBinaryFileList extraFiles;
    TIdList groups;
    QStringList tags;
    QString title;
public:
    explicit TAddLabRequestDataPrivate(TAddLabRequestData *q);
    ~TAddLabRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddLabRequestDataPrivate)
};

/*============================================================================
================================ TAddLabRequestDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TAddLabRequestDataPrivate::TAddLabRequestDataPrivate(TAddLabRequestData *q) :
    BBasePrivate(q)
{
    //
}

TAddLabRequestDataPrivate::~TAddLabRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddLabRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddLabRequestData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddLabRequestData::TAddLabRequestData() :
    BBase(*new TAddLabRequestDataPrivate(this))
{
    d_func()->init();
}

TAddLabRequestData::TAddLabRequestData(const TAddLabRequestData &other) :
    BBase(*new TAddLabRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddLabRequestData::~TAddLabRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAuthorInfoList TAddLabRequestData::authors() const
{
    return d_func()->authors;
}

void TAddLabRequestData::clear()
{
    B_D(TAddLabRequestData);
    d->authors.clear();
    d->dataList.clear();
    d->description.clear();
    d->extraFiles.clear();
    d->groups.clear();
    d->tags.clear();
    d->title.clear();
}

TLabDataList TAddLabRequestData::dataList() const
{
    return d_func()->dataList;
}

QString TAddLabRequestData::description() const
{
    return d_func()->description;
}

TBinaryFileList TAddLabRequestData::extraFiles() const
{
    return d_func()->extraFiles;
}

TIdList TAddLabRequestData::groups() const
{
    return d_func()->groups;
}

bool TAddLabRequestData::isValid() const
{
    const B_D(TAddLabRequestData);
    if (d->dataList.isEmpty())
        return false;
    bool osLinux = false;
    bool osMac = false;
    bool osWin = false;
    bool osNo = false;
    foreach (const TLabData &data, d->dataList) {
        if (!data.isValid())
            return false;
        switch (data.os()) {
        case BeQt::LinuxOS:
            if (osLinux || osNo)
                return false;
            osLinux = true;
            break;
        case BeQt::MacOS:
            if (osMac || osNo)
                return false;
            osMac = true;
            break;
        case BeQt::WindowsOS:
            if (osWin || osNo)
                return false;
            osWin = true;
            break;
        case BeQt::UnknownOS:
            if (osNo || (osLinux || osMac || osWin))
                return false;
            osNo = true;
            break;
        default:
            return false;
        }
    }
    return !d->title.isEmpty();
}

void TAddLabRequestData::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TAddLabRequestData::setDataList(const TLabDataList &dataList)
{
    d_func()->dataList = dataList;
}

void TAddLabRequestData::setDescritpion(const QString &description)
{
    d_func()->description = Texsample::testLabDescription(description) ? description : QString();
}

void TAddLabRequestData::setExtraFiles(const TBinaryFileList &extraFiles)
{
    d_func()->extraFiles = extraFiles;
}

void TAddLabRequestData::setGroups(const TIdList &groups)
{
    B_D(TAddLabRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TAddLabRequestData::setTags(const QStringList &tags)
{
    B_D(TAddLabRequestData);
    d->tags = BTextTools::removeDuplicates(tags, Qt::CaseInsensitive);
    d->tags.removeAll("");
}

void TAddLabRequestData::setTitle(const QString &title)
{
    d_func()->title = Texsample::testLabTitle(title) ? title : QString();
}

QStringList TAddLabRequestData::tags() const
{
    return d_func()->tags;
}

QString TAddLabRequestData::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TAddLabRequestData &TAddLabRequestData::operator =(const TAddLabRequestData &other)
{
    B_D(TAddLabRequestData);
    const TAddLabRequestDataPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->dataList = dd->dataList;
    d->description = dd->description;
    d->extraFiles = dd->extraFiles;
    d->groups = dd->groups;
    d->tags = dd->tags;
    d->title = dd->title;
    return *this;
}

bool TAddLabRequestData::operator ==(const TAddLabRequestData &other) const
{
    const B_D(TAddLabRequestData);
    const TAddLabRequestDataPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->dataList == dd->dataList && d->description == dd->description
            && d->extraFiles == dd->extraFiles && d->groups == dd->groups && d->tags == dd->tags
            && d->title == dd->title;
}

bool TAddLabRequestData::operator !=(const TAddLabRequestData &other) const
{
    return !(*this == other);
}

TAddLabRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddLabRequestData &data)
{
    const TAddLabRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("data_list", d->dataList);
    m.insert("description", d->description);
    m.insert("extra_files", d->extraFiles);
    m.insert("groups", d->groups);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddLabRequestData &data)
{
    TAddLabRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->dataList = m.value("data_list").value<TLabDataList>();
    d->description = m.value("description").toString();
    d->extraFiles = m.value("extra_files").value<TBinaryFileList>();
    d->groups = m.value("groups").value<TIdList>();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddLabRequestData &/*data*/)
{
    //const TAddLabRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddLabRequestData(" << ")";
    return dbg.space();
}
