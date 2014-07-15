#include "tlabinfo.h"

#include "tauthorinfolist.h"
#include "tfileinfolist.h"
#include "tidlist.h"
#include "tlabdatainfolist.h"
#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTextTools>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLabInfoPrivate =============================
============================================================================*/

class TLabInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabInfo)
public:
    TAuthorInfoList authors;
    QDateTime creationDateTime;
    TLabDataInfoList dataInfos;
    QString description;
    TFileInfoList extraFiles;
    TIdList groups;
    quint64 id;
    QDateTime lastModificationDateTime;
    quint64 senderId;
    QString senderLogin;
    QStringList tags;
    QString title;
public:
    explicit TLabInfoPrivate(TLabInfo *q);
    ~TLabInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLabInfoPrivate)
};

/*============================================================================
================================ TLabInfoPrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TLabInfoPrivate::TLabInfoPrivate(TLabInfo *q) :
    BBasePrivate(q)
{
    //
}

TLabInfoPrivate::~TLabInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabInfoPrivate::init()
{
    creationDateTime.setTimeSpec(Qt::UTC);
    id = 0;
    lastModificationDateTime.setTimeSpec(Qt::UTC);
    senderId = 0;
}

/*============================================================================
================================ TLabInfo ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TLabInfo::TLabInfo() :
    BBase(*new TLabInfoPrivate(this))
{
    d_func()->init();
}

TLabInfo::TLabInfo(const TLabInfo &other) :
    BBase(*new TLabInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLabInfo::~TLabInfo()
{
    //
}

/*============================== Protected constructors ====================*/

TLabInfo::TLabInfo(TLabInfoPrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

TAuthorInfoList TLabInfo::authors() const
{
    return d_func()->authors;
}

QDateTime TLabInfo::creationDateTime() const
{
    return d_func()->creationDateTime;
}

TLabDataInfoList TLabInfo::dataInfos() const
{
    return d_func()->dataInfos;
}

QString TLabInfo::description() const
{
    return d_func()->description;
}

TFileInfoList TLabInfo::extraFiles() const
{
    return d_func()->extraFiles;
}

TIdList TLabInfo::groups() const
{
    return d_func()->groups;
}

quint64 TLabInfo::id() const
{
    return d_func()->id;
}

bool TLabInfo::isValid() const
{
    const B_D(TLabInfo);
    return  !d->dataInfos.isEmpty() && d->creationDateTime.isValid() && d->id && d->lastModificationDateTime.isValid()
            && d->senderId && !d->senderLogin.isEmpty() && !d->title.isEmpty();
}

QDateTime TLabInfo::lastModificationDateTime() const
{
    return d_func()->lastModificationDateTime;
}

quint64 TLabInfo::senderId() const
{
    return d_func()->senderId;
}

QString TLabInfo::senderLogin() const
{
    return d_func()->senderLogin;
}

void TLabInfo::setAuthors(const TAuthorInfoList &authors)
{
    d_func()->authors = authors;
}

void TLabInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDateTime = dt.toUTC();
}

void TLabInfo::setDataInfos(const TLabDataInfoList &dataInfos)
{
    d_func()->dataInfos = dataInfos;
}

void TLabInfo::setDescription(const QString &description)
{
    d_func()->description = Texsample::testLabDescription(description) ? description : QString();
}

void TLabInfo::setExtraFiles(const TFileInfoList &extraFiles)
{
    d_func()->extraFiles = extraFiles;
}

void TLabInfo::setGroups(const TIdList &groups)
{
    B_D(TLabInfo);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TLabInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TLabInfo::setLastModificationDateTime(const QDateTime &dt)
{
    d_func()->lastModificationDateTime = dt.toUTC();
}

void TLabInfo::setSenderId(quint64 id)
{
    d_func()->senderId = id;
}

void TLabInfo::setSenderLogin(const QString &login)
{
    d_func()->senderLogin = Texsample::testLogin(login) ? login : QString();
}

void TLabInfo::setTags(const QStringList &list)
{
    d_func()->tags = BTextTools::removeDuplicates(list, Qt::CaseInsensitive);
    d_func()->tags.removeAll("");
}

void TLabInfo::setTitle(const QString &title)
{
    d_func()->title = Texsample::testLabTitle(title) ? title : QString();
}

QStringList TLabInfo::tags() const
{
    return d_func()->tags;
}

QString TLabInfo::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TLabInfo &TLabInfo::operator =(const TLabInfo &other)
{
    B_D(TLabInfo);
    const TLabInfoPrivate *dd = other.d_func();
    d->authors = dd->authors;
    d->creationDateTime = dd->creationDateTime;
    d->dataInfos = dd->dataInfos;
    d->description = dd->description;
    d->extraFiles = dd->extraFiles;
    d->groups = dd->groups;
    d->id = dd->id;
    d->lastModificationDateTime = dd->lastModificationDateTime;
    d->senderId = dd->senderId;
    d->senderLogin = dd->senderLogin;
    d->tags = dd->tags;
    d->title = dd->title;
    return *this;
}

bool TLabInfo::operator ==(const TLabInfo &other) const
{
    const B_D(TLabInfo);
    const TLabInfoPrivate *dd = other.d_func();
    return d->authors == dd->authors && d->creationDateTime == dd->creationDateTime && d->dataInfos == dd->dataInfos
            && d->description == dd->description && d->extraFiles == dd->extraFiles && d->groups == dd->groups
            && d->id == dd->id && d->lastModificationDateTime == dd->lastModificationDateTime
            && d->senderId == dd->senderId && d->senderLogin == dd->senderLogin && d->tags == dd->tags
            && d->title == dd->title;
}

bool TLabInfo::operator !=(const TLabInfo &other) const
{
    return !(*this == other);
}

TLabInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLabInfo &info)
{
    const TLabInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("authors", d->authors);
    m.insert("creation_date_time", d->creationDateTime);
    m.insert("data_infos", d->dataInfos);
    m.insert("description", d->description);
    m.insert("extra_files", d->extraFiles);
    m.insert("groups", d->groups);
    m.insert("id", d->id);
    m.insert("last_modification_date_time", d->lastModificationDateTime);
    m.insert("sender_id", d->senderId);
    m.insert("sender_login", d->senderLogin);
    m.insert("tags", d->tags);
    m.insert("title", d->title);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabInfo &info)
{
    TLabInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->authors = m.value("authors").value<TAuthorInfoList>();
    d->creationDateTime = m.value("creation_date_time").toDateTime().toUTC();
    d->dataInfos = m.value("data_infos").value<TLabDataInfoList>();
    d->description = m.value("description").toString();
    d->extraFiles = m.value("extra_files").value<TFileInfoList>();
    d->groups = m.value("groups").value<TIdList>();
    d->id = m.value("id").toULongLong();
    d->lastModificationDateTime = m.value("last_modification_date_time").toDateTime().toUTC();
    d->senderId = m.value("sender_id").toULongLong();
    d->senderLogin = m.value("sender_login").toString();
    d->tags = m.value("tags").toStringList();
    d->title = m.value("title").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabInfo &info)
{
    const TLabInfoPrivate *d = info.d_func();
    dbg.nospace() << "TLabInfo(" << d->id << "," << d->title << ")";
    return dbg.space();
}
