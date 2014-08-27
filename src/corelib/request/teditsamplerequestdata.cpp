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

#include "teditsamplerequestdata.h"

#include "tauthorinfolist.h"
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
================================ TEditSampleRequestDataPrivate ===============
============================================================================*/

class TEditSampleRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSampleRequestData)
public:
    TAuthorInfoList authors;
    QString description;
    bool editProject;
    quint64 id;
    TTexProject project;
    QStringList tags;
    QString title;
public:
    explicit TEditSampleRequestDataPrivate(TEditSampleRequestData *q);
    ~TEditSampleRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSampleRequestDataPrivate)
};

/*============================================================================
================================ TEditSampleRequestDataPrivate ===============
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleRequestDataPrivate::TEditSampleRequestDataPrivate(TEditSampleRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditSampleRequestDataPrivate::~TEditSampleRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleRequestDataPrivate::init()
{
    editProject = false;
    id = 0;
}

/*============================================================================
================================ TEditSampleRequestData ======================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleRequestData::TEditSampleRequestData() :
    BBase(*new TEditSampleRequestDataPrivate(this))
{
    d_func()->init();
}

TEditSampleRequestData::TEditSampleRequestData(const TEditSampleRequestData &other) :
    BBase(*new TEditSampleRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSampleRequestData::~TEditSampleRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAuthorInfoList TEditSampleRequestData::authors() const
{
    return d_func()->authors;
}

void TEditSampleRequestData::clear()
{
    B_D(TEditSampleRequestData);
    d->authors.clear();
    d->description.clear();
    d->editProject = false;
    d->id = 0;
    d->project.clear();
    d->tags.clear();
    d->title.clear();
}

QString TEditSampleRequestData::description() const
{
    return d_func()->description;
}

bool TEditSampleRequestData::editProject() const
{
    return d_func()->editProject;
}

quint64 TEditSampleRequestData::id() const
{
    return d_func()->id;
}

bool TEditSampleRequestData::isValid() const
{
    const B_D(TEditSampleRequestData);
    return d->id && (!d->editProject || d->project.isValid()) && !d->title.isEmpty();
}

TTexProject TEditSampleRequestData::project() const
{
    return d_func()->project;
}

void TEditSampleRequestData::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TEditSampleRequestData::setDescritpion(const QString &description)
{
    d_func()->description = Texsample::testLabDescription(description) ? description : QString();
}

void TEditSampleRequestData::setEditProject(bool edit)
{
    d_func()->editProject = edit;
}

void TEditSampleRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

void TEditSampleRequestData::setProject(const TTexProject &project)
{
    d_func()->project = project;
}

void TEditSampleRequestData::setTags(const QStringList &tags)
{
    B_D(TEditSampleRequestData);
    d->tags = BTextTools::removeDuplicates(tags, Qt::CaseInsensitive);
    d->tags.removeAll("");
}

void TEditSampleRequestData::setTitle(const QString &title)
{
    d_func()->title = Texsample::testLabTitle(title) ? title : QString();
}

QStringList TEditSampleRequestData::tags() const
{
    return d_func()->tags;
}

QString TEditSampleRequestData::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TEditSampleRequestData &TEditSampleRequestData::operator =(const TEditSampleRequestData &other)
{
    B_D(TEditSampleRequestData);
    const TEditSampleRequestDataPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->description = dd->description;
    d->editProject = dd->editProject;
    d->id = dd->id;
    d->project = dd->project;
    d->tags = dd->tags;
    d->title = dd->title;
    return *this;
}

bool TEditSampleRequestData::operator ==(const TEditSampleRequestData &other) const
{
    const B_D(TEditSampleRequestData);
    const TEditSampleRequestDataPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->description == dd->description && d->editProject == dd->editProject
            && d->id == dd->id && d->project == dd->project && d->tags == dd->tags && d->title == dd->title;
}

bool TEditSampleRequestData::operator !=(const TEditSampleRequestData &other) const
{
    return !(*this == other);
}

TEditSampleRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSampleRequestData &data)
{
    const TEditSampleRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("description", d->description);
    m.insert("edit_project", d->editProject);
    m.insert("id", d->id);
    m.insert("project", d->project);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSampleRequestData &data)
{
    TEditSampleRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->description = m.value("description").toString();
    d->editProject = m.value("edit_project").toBool();
    d->id = m.value("id").toULongLong();
    d->project = m.value("project").value<TTexProject>();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSampleRequestData &/*data*/)
{
    //const TEditSampleRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSampleRequestData(" << ")";
    return dbg.space();
}
