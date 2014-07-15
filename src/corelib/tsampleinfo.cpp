#include "tsampleinfo.h"

#include "tauthorinfolist.h"
#include "tfileinfo.h"
#include "tfileinfolist.h"
#include "tnamespace.h"
#include "tsampletype.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTextTools>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

class TSampleInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSampleInfo)
public:
    TAuthorInfoList authors;
    QDateTime creationDateTime;
    QString description;
    TFileInfoList extraPreviewFiles;
    TFileInfoList extraSourceFiles;
    quint64 id;
    QDateTime lastModificationDateTime;
    TFileInfo mainPreviewFile;
    TFileInfo mainSourceFile;
    quint8 rating;
    QString remark;
    quint64 senderId;
    QString senderLogin;
    QStringList tags;
    QString title;
    TSampleType type;
public:
    explicit TSampleInfoPrivate(TSampleInfo *q);
    ~TSampleInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSampleInfoPrivate)
};

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TSampleInfoPrivate::TSampleInfoPrivate(TSampleInfo *q) :
    BBasePrivate(q)
{
    //
}

TSampleInfoPrivate::~TSampleInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSampleInfoPrivate::init()
{
    creationDateTime.setTimeSpec(Qt::UTC);
    id = 0;
    lastModificationDateTime.setTimeSpec(Qt::UTC);
    rating = 0;
    senderId = 0;
}

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

/*============================== Public constructors =======================*/

TSampleInfo::TSampleInfo() :
    BBase(*new TSampleInfoPrivate(this))
{
    d_func()->init();
}

TSampleInfo::TSampleInfo(const TSampleInfo &other) :
    BBase(*new TSampleInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSampleInfo::~TSampleInfo()
{
    //
}

/*============================== Protected constructors ====================*/

TSampleInfo::TSampleInfo(TSampleInfoPrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

QString TSampleInfo::adminRemark() const
{
    return d_func()->remark;
}

TAuthorInfoList TSampleInfo::authors() const
{
    return d_func()->authors;
}

QDateTime TSampleInfo::creationDateTime() const
{
    return d_func()->creationDateTime;
}

QString TSampleInfo::description() const
{
    return d_func()->description;
}

TFileInfoList TSampleInfo::extraPreviewFiles() const
{
    return d_func()->extraPreviewFiles;
}

TFileInfoList TSampleInfo::extraSourceFiles() const
{
    return d_func()->extraSourceFiles;
}

quint64 TSampleInfo::id() const
{
    return d_func()->id;
}

bool TSampleInfo::isValid() const
{
    const B_D(TSampleInfo);
    return d->creationDateTime.isValid() && d->id && d->lastModificationDateTime.isValid() && d->mainPreviewFile.isValid()
            && d->mainSourceFile.isValid() && d->senderId && !d->senderLogin.isEmpty() && !d->title.isEmpty();
}

QDateTime TSampleInfo::lastModificationDateTime() const
{
    return d_func()->lastModificationDateTime;
}

TFileInfo TSampleInfo::mainPreviewFile() const
{
    return d_func()->mainPreviewFile;
}

TFileInfo TSampleInfo::mainSourceFile() const
{
    return d_func()->mainSourceFile;
}

int TSampleInfo::previewSize() const
{
    const B_D(TSampleInfo);
    int sz = d->mainPreviewFile.fileSize();
    foreach (const TFileInfo &f, d->extraPreviewFiles)
        sz += f.fileSize();
    return sz;
}

quint8 TSampleInfo::rating() const
{
    return d_func()->rating;
}

quint64 TSampleInfo::senderId() const
{
    return d_func()->senderId;
}

QString TSampleInfo::senderLogin() const
{
    return d_func()->senderLogin;
}

void TSampleInfo::setAdminRemark(const QString &remark)
{
    d_func()->remark = Texsample::testAdminRemark(remark) ? remark : QString();
}

void TSampleInfo::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TSampleInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDateTime = dt.toUTC();
}

void TSampleInfo::setDescription(const QString &description)
{
    d_func()->description = Texsample::testSampleDescription(description) ? description : QString();
}

void TSampleInfo::setExtraPreviewFiles(const TFileInfoList &files)
{
    d_func()->extraPreviewFiles = files;
}

void TSampleInfo::setExtraSourceFiles(const TFileInfoList &files)
{
    d_func()->extraSourceFiles = files;
}

void TSampleInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TSampleInfo::setLastModificationDateTime(const QDateTime &dt)
{
    d_func()->lastModificationDateTime = dt.toUTC();
}

void TSampleInfo::setMainPreviewFile(const TFileInfo &file)
{
    d_func()->mainPreviewFile = file;
}

void TSampleInfo::setMainSourceFile(const TFileInfo &file)
{
    d_func()->mainSourceFile = file;
}

void TSampleInfo::setRating(quint8 r)
{
    d_func()->rating = (r < 100) ? r : 100;
}

void TSampleInfo::setSenderId(quint64 id)
{
    d_func()->senderId = id;
}

void TSampleInfo::setSenderLogin(const QString &login)
{
    d_func()->senderLogin = Texsample::testLogin(login) ? login : QString();
}

void TSampleInfo::setTags(const QStringList &tags)
{
    B_D(TSampleInfo);
    d->tags = BTextTools::removeDuplicates(tags, Qt::CaseInsensitive);
    d->tags.removeAll("");
}

void TSampleInfo::setTitle(const QString &title)
{
    d_func()->title = Texsample::testSampleTitle(title) ? title : QString();
}

void TSampleInfo::setType(const TSampleType &type)
{
    d_func()->type = type;
}

int TSampleInfo::sourceSize() const
{
    const B_D(TSampleInfo);
    int sz = d->mainSourceFile.fileSize();
    foreach (const TFileInfo &f, d->extraSourceFiles)
        sz += f.fileSize();
    return sz;
}

QStringList TSampleInfo::tags() const
{
    return d_func()->tags;
}

QString TSampleInfo::title() const
{
    return d_func()->title;
}

TSampleType TSampleInfo::type() const
{
    return d_func()->type;
}

/*============================== Public operators ==========================*/

TSampleInfo &TSampleInfo::operator =(const TSampleInfo &other)
{
    B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->creationDateTime = dd->creationDateTime;
    d->description = dd->description;
    d->extraPreviewFiles = dd->extraPreviewFiles;
    d->extraSourceFiles = dd->extraSourceFiles;
    d->id = dd->id;
    d->lastModificationDateTime = dd->lastModificationDateTime;
    d->mainPreviewFile = dd->mainPreviewFile;
    d->mainSourceFile = dd->mainSourceFile;
    d->rating = dd->rating;
    d->remark = dd->remark;
    d->senderId = dd->senderId;
    d->senderLogin = dd->senderLogin;
    d->tags = dd->tags;
    d->title = dd->title;
    d->type = dd->type;
    return *this;
}

bool TSampleInfo::operator ==(const TSampleInfo &other) const
{
    const B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->creationDateTime == dd->creationDateTime
            && d->description == dd->description && d->extraPreviewFiles == dd->extraPreviewFiles
            && d->extraSourceFiles == dd->extraSourceFiles && d->id == dd->id
            && d->lastModificationDateTime == dd->lastModificationDateTime
            && d->mainPreviewFile == dd->mainPreviewFile && d->mainSourceFile == dd->mainSourceFile
            && d->rating == dd->rating && d->remark == dd->remark && d->senderId == dd->senderId
            && d->senderLogin == dd->senderLogin && d->tags == dd->tags && d->title == dd->title
            && d->type == dd->type;
}

bool TSampleInfo::operator !=(const TSampleInfo &other) const
{
    return !(*this == other);
}

TSampleInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSampleInfo &info)
{
    const TSampleInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("creation_date_time", d->creationDateTime);
    m.insert("description", d->description);
    m.insert("extra_preview_files", d->extraPreviewFiles);
    m.insert("extra_source_files", d->extraSourceFiles);
    m.insert("id", d->id);
    m.insert("last_modification_date_time", d->lastModificationDateTime);
    m.insert("main_preview_file", d->mainPreviewFile);
    m.insert("main_source_file", d->mainSourceFile);
    m.insert("rating", d->rating);
    m.insert("remark", d->remark);
    m.insert("sender_id", d->senderId);
    m.insert("sender_login", d->senderLogin);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    m.insert("type", d->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSampleInfo &info)
{
    TSampleInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->creationDateTime = m.value("creation_date_time").toDateTime().toUTC();
    d->description = m.value("descrtiption").toString();
    d->extraPreviewFiles = m.value("extra_preview_files").value<TFileInfoList>();
    d->extraSourceFiles = m.value("extra_source_files").value<TFileInfoList>();
    d->id = m.value("id").toULongLong();
    d->lastModificationDateTime = m.value("last_modification_date_time").toDateTime().toUTC();
    d->mainPreviewFile = m.value("main_preview_file").value<TFileInfo>();
    d->mainSourceFile = m.value("main_source_file").value<TFileInfo>();
    d->rating = m.value("rating").toUInt();
    d->remark = m.value("remark").toString();
    d->senderId = m.value("sender_id").toULongLong();
    d->senderLogin = m.value("sender_login").toString();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    d->type = m.value("type").value<TSampleType>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSampleInfo &info)
{
    const TSampleInfoPrivate *d = info.d_func();
    dbg.nospace() << "TSampleInfo(" << d->id << "," << d->title << ")";
    return dbg.space();
}
