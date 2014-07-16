#include "teditlabrequestdata.h"

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
================================ TEditLabRequestDataPrivate ==================
============================================================================*/

class TEditLabRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditLabRequestData)
public:
    TAuthorInfoList authors;
    TLabDataList dataList;
    QStringList deletedExtraFiles;
    QString description;
    bool editData;
    TIdList groups;
    quint64 id;
    TBinaryFileList newExtraFiles;
    QStringList tags;
    QString title;
public:
    explicit TEditLabRequestDataPrivate(TEditLabRequestData *q);
    ~TEditLabRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditLabRequestDataPrivate)
};

/*============================================================================
================================ TEditLabRequestDataPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TEditLabRequestDataPrivate::TEditLabRequestDataPrivate(TEditLabRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditLabRequestDataPrivate::~TEditLabRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditLabRequestDataPrivate::init()
{
    editData = false;
    id = 0;
}

/*============================================================================
================================ TEditLabRequestData =========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditLabRequestData::TEditLabRequestData() :
    BBase(*new TEditLabRequestDataPrivate(this))
{
    d_func()->init();
}

TEditLabRequestData::TEditLabRequestData(const TEditLabRequestData &other) :
    BBase(*new TEditLabRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditLabRequestData::~TEditLabRequestData()
{
    //
}

/*============================== Public methods ============================*/

TAuthorInfoList TEditLabRequestData::authors() const
{
    return d_func()->authors;
}

void TEditLabRequestData::clear()
{
    B_D(TEditLabRequestData);
    d->authors.clear();
    d->dataList.clear();
    d->deletedExtraFiles.clear();
    d->description.clear();
    d->editData = false;
    d->groups.clear();
    d->id = 0;
    d->newExtraFiles.clear();
    d->tags.clear();
    d->title.clear();
}

TLabDataList TEditLabRequestData::dataList() const
{
    return d_func()->dataList;
}

QStringList TEditLabRequestData::deletedExtraFiles() const
{
    return d_func()->deletedExtraFiles;
}

QString TEditLabRequestData::description() const
{
    return d_func()->description;
}

bool TEditLabRequestData::editData() const
{
    return d_func()->editData;
}

TIdList TEditLabRequestData::groups() const
{
    return d_func()->groups;
}

quint64 TEditLabRequestData::id() const
{
    return d_func()->id;
}

bool TEditLabRequestData::isValid() const
{
    const B_D(TEditLabRequestData);
    if (d->editData) {
        if (d->dataList.isEmpty())
            return false;
        foreach (const TLabData &data, d->dataList) {
            if (!data.isValid())
                return false;
        }
    }
    return d->id && !d->title.isEmpty();
}

TBinaryFileList TEditLabRequestData::newExtraFiles() const
{
    return d_func()->newExtraFiles;
}

void TEditLabRequestData::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TEditLabRequestData::setDataList(const TLabDataList &dataList)
{
    d_func()->dataList = dataList;
}

void TEditLabRequestData::setDeletedExtraFiles(const QStringList &extraFiles)
{
    B_D(TEditLabRequestData);
    d->deletedExtraFiles = BTextTools::removeDuplicates(extraFiles, Qt::CaseInsensitive);
    d->deletedExtraFiles.removeAll("");
}

void TEditLabRequestData::setDescritpion(const QString &description)
{
    d_func()->description = Texsample::testLabDescription(description) ? description : QString();
}

void TEditLabRequestData::setEditData(bool edit)
{
    d_func()->editData = edit;
}

void TEditLabRequestData::setGroups(const TIdList &groups)
{
    B_D(TEditLabRequestData);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TEditLabRequestData::setNewExtraFiles(const TBinaryFileList &extraFiles)
{
    d_func()->newExtraFiles = extraFiles;
}

void TEditLabRequestData::setTags(const QStringList &tags)
{
    B_D(TEditLabRequestData);
    d->tags = BTextTools::removeDuplicates(tags, Qt::CaseInsensitive);
    d->tags.removeAll("");
}

void TEditLabRequestData::setTitle(const QString &title)
{
    d_func()->title = Texsample::testLabTitle(title) ? title : QString();
}

QStringList TEditLabRequestData::tags() const
{
    return d_func()->tags;
}

QString TEditLabRequestData::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TEditLabRequestData &TEditLabRequestData::operator =(const TEditLabRequestData &other)
{
    B_D(TEditLabRequestData);
    const TEditLabRequestDataPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->dataList = dd->dataList;
    d->deletedExtraFiles = dd->deletedExtraFiles;
    d->description = dd->description;
    d->editData = dd->editData;
    d->groups = dd->groups;
    d->id = dd->id;
    d->newExtraFiles = dd->newExtraFiles;
    d->tags = dd->tags;
    d->title = dd->title;
    return *this;
}

bool TEditLabRequestData::operator ==(const TEditLabRequestData &other) const
{
    const B_D(TEditLabRequestData);
    const TEditLabRequestDataPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->dataList == dd->dataList && d->deletedExtraFiles == dd->deletedExtraFiles
            && d->description == dd->description && d->editData == dd->editData && d->groups == dd->groups
            && d->id == dd->id && d->newExtraFiles == dd->newExtraFiles && d->tags == dd->tags
            && d->title == dd->title;
}

bool TEditLabRequestData::operator !=(const TEditLabRequestData &other) const
{
    return !(*this == other);
}

TEditLabRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditLabRequestData &data)
{
    const TEditLabRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("data_list", d->dataList);
    m.insert("deleted_extra_files", d->deletedExtraFiles);
    m.insert("description", d->description);
    m.insert("edit_data", d->editData);
    m.insert("groups", d->groups);
    m.insert("id", d->id);
    m.insert("new_extra_files", d->newExtraFiles);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditLabRequestData &data)
{
    TEditLabRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->dataList = m.value("data_list").value<TLabDataList>();
    d->deletedExtraFiles = m.value("deleted_extra_files").toStringList();
    d->description = m.value("description").toString();
    d->editData = m.value("edit_data").toBool();
    d->groups = m.value("groups").value<TIdList>();
    d->id = m.value("id").toULongLong();
    d->newExtraFiles = m.value("new_extra_files").value<TBinaryFileList>();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditLabRequestData &/*data*/)
{
    //const TEditLabRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditLabRequestData(" << ")";
    return dbg.space();
}
