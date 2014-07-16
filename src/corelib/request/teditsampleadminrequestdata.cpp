#include "teditsampleadminrequestdata.h"

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
================================ TEditSampleAdminRequestDataPrivate ==========
============================================================================*/

class TEditSampleAdminRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSampleAdminRequestData)
public:
    TAuthorInfoList authors;
    QString description;
    bool editProject;
    TIdList groups;
    TTexProject project;
    quint8 rating;
    QString remark;
    QStringList tags;
    QString title;
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
    d->groups.clear();
    d->project.clear();
    d->rating = 0;
    d->remark.clear();
    d->tags.clear();
    d->title.clear();
}

QString TEditSampleAdminRequestData::description() const
{
    return d_func()->description;
}

bool TEditSampleAdminRequestData::editProject() const
{
    return d_func()->editProject;
}

TIdList TEditSampleAdminRequestData::groups() const
{
    return d_func()->groups;
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

void TEditSampleAdminRequestData::setGroups(const TIdList &groups)
{
    B_D(TEditSampleAdminRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
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

QStringList TEditSampleAdminRequestData::tags() const
{
    return d_func()->tags;
}

QString TEditSampleAdminRequestData::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TEditSampleAdminRequestData &TEditSampleAdminRequestData::operator =(const TEditSampleAdminRequestData &other)
{
    B_D(TEditSampleAdminRequestData);
    const TEditSampleAdminRequestDataPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->description = dd->description;
    d->editProject = dd->editProject;
    d->groups = dd->groups;
    d->project = dd->project;
    d->rating = dd->rating;
    d->remark = dd->remark;
    d->tags = dd->tags;
    d->title = dd->title;
    return *this;
}

bool TEditSampleAdminRequestData::operator ==(const TEditSampleAdminRequestData &other) const
{
    const B_D(TEditSampleAdminRequestData);
    const TEditSampleAdminRequestDataPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->description == dd->description && d->editProject == dd->editProject
            && d->groups == dd->groups && d->project == dd->project && d->rating == dd->rating
            && d->remark == dd->remark && d->tags == dd->tags && d->title == dd->title;
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
    m.insert("groups", d->groups);
    m.insert("project", d->project);
    m.insert("rating", d->rating);
    m.insert("remark", d->remark);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
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
    d->groups = m.value("groups").value<TIdList>();
    d->project = m.value("project").value<TTexProject>();
    d->rating = m.value("rating").toUInt();
    d->remark = m.value("remark").toString();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSampleAdminRequestData &/*data*/)
{
    //const TEditSampleAdminRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSampleAdminRequestData(" << ")";
    return dbg.space();
}
