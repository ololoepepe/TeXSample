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

#include "taddsamplerequestdata.h"

#include "tauthorinfolist.h"
#include "tidlist.h"
#include "tnamespace.h"
#include "ttexproject.h"

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
================================ TAddSampleRequestDataPrivate ================
============================================================================*/

class TAddSampleRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddSampleRequestData)
public:
    TAuthorInfoList authors;
    QString description;
    TIdList groups;
    TTexProject project;
    QStringList tags;
    QString title;
public:
    explicit TAddSampleRequestDataPrivate(TAddSampleRequestData *q);
    ~TAddSampleRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddSampleRequestDataPrivate)
};

/*============================================================================
================================ TAddSampleRequestDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TAddSampleRequestDataPrivate::TAddSampleRequestDataPrivate(TAddSampleRequestData *q) :
    BBasePrivate(q)
{
    //
}

TAddSampleRequestDataPrivate::~TAddSampleRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddSampleRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddSampleRequestData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TAddSampleRequestData::TAddSampleRequestData() :
    BBase(*new TAddSampleRequestDataPrivate(this))
{
    d_func()->init();
}

TAddSampleRequestData::TAddSampleRequestData(const TAddSampleRequestData &other) :
    BBase(*new TAddSampleRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddSampleRequestData::~TAddSampleRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAuthorInfoList TAddSampleRequestData::authors() const
{
    return d_func()->authors;
}

void TAddSampleRequestData::clear()
{
    B_D(TAddSampleRequestData);
    d->authors.clear();
    d->description.clear();
    d->groups.clear();
    d->project.clear();
    d->tags.clear();
    d->title.clear();
}

QString TAddSampleRequestData::description() const
{
    return d_func()->description;
}

TIdList TAddSampleRequestData::groups() const
{
    return d_func()->groups;
}

bool TAddSampleRequestData::isValid() const
{
    const B_D(TAddSampleRequestData);
    return d->project.isValid() && !d->title.isEmpty();
}

TTexProject TAddSampleRequestData::project() const
{
    return d_func()->project;
}

void TAddSampleRequestData::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TAddSampleRequestData::setDescritpion(const QString &description)
{
    d_func()->description = Texsample::testLabDescription(description) ? description : QString();
}

void TAddSampleRequestData::setGroups(const TIdList &groups)
{
    B_D(TAddSampleRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TAddSampleRequestData::setProject(const TTexProject &project)
{
    d_func()->project = project;
}

void TAddSampleRequestData::setTags(const QStringList &tags)
{
    B_D(TAddSampleRequestData);
    d->tags = BTextTools::removeDuplicates(tags, Qt::CaseInsensitive);
    d->tags.removeAll("");
}

void TAddSampleRequestData::setTitle(const QString &title)
{
    d_func()->title = Texsample::testLabTitle(title) ? title : QString();
}

QStringList TAddSampleRequestData::tags() const
{
    return d_func()->tags;
}

QString TAddSampleRequestData::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TAddSampleRequestData &TAddSampleRequestData::operator =(const TAddSampleRequestData &other)
{
    B_D(TAddSampleRequestData);
    const TAddSampleRequestDataPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->description = dd->description;
    d->groups = dd->groups;
    d->project = dd->project;
    d->tags = dd->tags;
    d->title = dd->title;
    return *this;
}

bool TAddSampleRequestData::operator ==(const TAddSampleRequestData &other) const
{
    const B_D(TAddSampleRequestData);
    const TAddSampleRequestDataPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->description == dd->description && d->groups == dd->groups
            && d->project == dd->project && d->tags == dd->tags && d->title == dd->title;
}

bool TAddSampleRequestData::operator !=(const TAddSampleRequestData &other) const
{
    return !(*this == other);
}

TAddSampleRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddSampleRequestData &data)
{
    const TAddSampleRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("description", d->description);
    m.insert("groups", d->groups);
    m.insert("project", d->project);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddSampleRequestData &data)
{
    TAddSampleRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->description = m.value("description").toString();
    d->groups = m.value("groups").value<TIdList>();
    d->project = m.value("project").value<TTexProject>();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddSampleRequestData &/*data*/)
{
    //const TAddSampleRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddSampleRequestData(" << ")";
    return dbg.space();
}
