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

#include "teditsampleadminrequestdata.h"

#include "tauthorinfolist.h"
#include "tnamespace.h"
#include "tsampletype.h"
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
================================ TEditSampleAdminRequestDataPrivate ==========
============================================================================*/

class TEditSampleAdminRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSampleAdminRequestData)
public:
    TAuthorInfoList authors;
    QString description;
    bool editProject;
    TTexProject project;
    quint8 rating;
    QString remark;
    QStringList tags;
    QString title;
    TSampleType type;
public:
    explicit TEditSampleAdminRequestDataPrivate(TEditSampleAdminRequestData *q);
    ~TEditSampleAdminRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSampleAdminRequestDataPrivate)
};

/*============================================================================
================================ TEditSampleAdminRequestDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleAdminRequestDataPrivate::TEditSampleAdminRequestDataPrivate(TEditSampleAdminRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditSampleAdminRequestDataPrivate::~TEditSampleAdminRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleAdminRequestDataPrivate::init()
{
    editProject = false;
    rating = 0;
}

/*============================================================================
================================ TEditSampleAdminRequestData =================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleAdminRequestData::TEditSampleAdminRequestData() :
    BBase(*new TEditSampleAdminRequestDataPrivate(this))
{
    d_func()->init();
}

TEditSampleAdminRequestData::TEditSampleAdminRequestData(const TEditSampleAdminRequestData &other) :
    BBase(*new TEditSampleAdminRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSampleAdminRequestData::~TEditSampleAdminRequestData()
{
    //
}

/*============================== Public methods ============================*/

QString TEditSampleAdminRequestData::adminRemark() const
{
    return d_func()->remark;
}

TAuthorInfoList TEditSampleAdminRequestData::authors() const
{
    return d_func()->authors;
}

void TEditSampleAdminRequestData::clear()
{
    B_D(TEditSampleAdminRequestData);
    d->authors.clear();
    d->description.clear();
    d->editProject = false;
    d->project.clear();
    d->rating = 0;
    d->remark.clear();
    d->tags.clear();
    d->title.clear();
    d->type = TSampleType();
}

QString TEditSampleAdminRequestData::description() const
{
    return d_func()->description;
}

bool TEditSampleAdminRequestData::editProject() const
{
    return d_func()->editProject;
}

bool TEditSampleAdminRequestData::isValid() const
{
    const B_D(TEditSampleAdminRequestData);
    return (!d->editProject || d->project.isValid()) && !d->title.isEmpty();
}

TTexProject TEditSampleAdminRequestData::project() const
{
    return d_func()->project;
}

quint8 TEditSampleAdminRequestData::rating() const
{
    return d_func()->rating;
}

void TEditSampleAdminRequestData::setAdminRemark(const QString &remark)
{
    d_func()->remark = remark;
}

void TEditSampleAdminRequestData::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TEditSampleAdminRequestData::setDescritpion(const QString &description)
{
    d_func()->description = Texsample::testLabDescription(description) ? description : QString();
}

void TEditSampleAdminRequestData::setEditProject(bool edit)
{
    d_func()->editProject = edit;
}

void TEditSampleAdminRequestData::setProject(const TTexProject &project)
{
    d_func()->project = project;
}

void TEditSampleAdminRequestData::setRating(quint8 rating)
{
    d_func()->rating = (rating < 100) ? rating : 100;
}

void TEditSampleAdminRequestData::setTags(const QStringList &tags)
{
    B_D(TEditSampleAdminRequestData);
    d->tags = BTextTools::removeDuplicates(tags, Qt::CaseInsensitive);
    d->tags.removeAll("");
}

void TEditSampleAdminRequestData::setTitle(const QString &title)
{
    d_func()->title = Texsample::testLabTitle(title) ? title : QString();
}

void TEditSampleAdminRequestData::setType(const TSampleType &type)
{
    d_func()->type = type;
}

QStringList TEditSampleAdminRequestData::tags() const
{
    return d_func()->tags;
}

QString TEditSampleAdminRequestData::title() const
{
    return d_func()->title;
}

TSampleType TEditSampleAdminRequestData::type() const
{
    return d_func()->type;
}

/*============================== Public operators ==========================*/

TEditSampleAdminRequestData &TEditSampleAdminRequestData::operator =(const TEditSampleAdminRequestData &other)
{
    B_D(TEditSampleAdminRequestData);
    const TEditSampleAdminRequestDataPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->description = dd->description;
    d->editProject = dd->editProject;
    d->project = dd->project;
    d->rating = dd->rating;
    d->remark = dd->remark;
    d->tags = dd->tags;
    d->title = dd->title;
    d->type = dd->type;
    return *this;
}

bool TEditSampleAdminRequestData::operator ==(const TEditSampleAdminRequestData &other) const
{
    const B_D(TEditSampleAdminRequestData);
    const TEditSampleAdminRequestDataPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->description == dd->description && d->editProject == dd->editProject
            && d->project == dd->project && d->rating == dd->rating && d->remark == dd->remark && d->tags == dd->tags
            && d->title == dd->title && d->type == dd->type;
}

bool TEditSampleAdminRequestData::operator !=(const TEditSampleAdminRequestData &other) const
{
    return !(*this == other);
}

TEditSampleAdminRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminRequestData &data)
{
    const TEditSampleAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("description", d->description);
    m.insert("edit_project", d->editProject);
    m.insert("project", d->project);
    m.insert("rating", d->rating);
    m.insert("remark", d->remark);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    m.insert("type", d->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSampleAdminRequestData &data)
{
    TEditSampleAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->description = m.value("description").toString();
    d->editProject = m.value("edit_project").toBool();
    d->project = m.value("project").value<TTexProject>();
    d->rating = m.value("rating").toUInt();
    d->remark = m.value("remark").toString();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    d->type = m.value("type").value<TSampleType>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSampleAdminRequestData &/*data*/)
{
    //const TEditSampleAdminRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSampleAdminRequestData(" << ")";
    return dbg.space();
}
