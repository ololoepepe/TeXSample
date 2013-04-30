#include "tsampleinfo.h"
#include "tglobal.h"
#include "tuserinfo.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QRegExp>
#include <QVariant>
#include <QDebug>
#include <QFileInfo>
#include <QList>

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

class TSampleInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSampleInfo)
public:
   static TSampleInfo::Context contextFromInt(int c);
public:
   explicit TSampleInfoPrivate(TSampleInfo *q);
    ~TSampleInfoPrivate();
public:
    void init();
public:
    TSampleInfo::Context context;
    quint64 id;
    TUserInfo author;
    QList<TUserInfo> extraAuthors;
    QString title;
    TSampleInfo::Type type;
    QString fileName;
    QStringList tags;
    QString comment;
    QString remark;
    quint8 rating;
    QDateTime creationDT;
    QDateTime modificationDT;
    QDateTime updateDT;
private:
    Q_DISABLE_COPY(TSampleInfoPrivate)
};

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

/*============================== Static public methods =====================*/

TSampleInfo::Context TSampleInfoPrivate::contextFromInt(int c)
{
    static const QList<int> contexts = bRangeD(TSampleInfo::GeneralContext, TSampleInfo::UpdateContext);
    return contexts.contains(c) ? static_cast<TSampleInfo::Context>(c) : TSampleInfo::GeneralContext;
}

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
    context = TSampleInfo::GeneralContext;
    id = 0;
    type = TSampleInfo::Unverified;
    rating = 0;
    creationDT.setTimeSpec(Qt::UTC);
    modificationDT.setTimeSpec(Qt::UTC);
    updateDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TSampleInfo::typeToString(Type t, bool singular)
{
    if (singular)
    {
        switch (t)
        {
        case Approved:
            return tr("Approved", "type (singular)");
        case Rejected:
            return tr("Rejected", "type (singular)");
        case Unverified:
        default:
            return tr("Unverified", "type (singular)");
        }
    }
    else
    {
        switch (t)
        {
        case Approved:
            return tr("Approved", "type (plural)");
        case Rejected:
            return tr("Rejected", "type (plural)");
        case Unverified:
        default:
            return tr("Unverified", "type (plural)");
        }
    }
}

QString TSampleInfo::tagsToString(const QStringList &tags)
{
    return tags.join(", ");
}

QStringList TSampleInfo::tagsFromString(const QString &s)
{
    static QRegExp rx("\\,\\s*");
    return s.split(rx, QString::SkipEmptyParts);
}

/*============================== Public constructors =======================*/

TSampleInfo::TSampleInfo(Context c) :
    BBase(*new TSampleInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
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

void TSampleInfo::setContext(int c, bool clear)
{
    B_D(TSampleInfo);
    Context cc = TSampleInfoPrivate::contextFromInt(c);
    if (cc == d->context)
        return;
    d->context = cc;
    if (!clear)
        return;
    switch (cc)
    {
    case AddContext:
        d->id = 0;
        break;
    case UpdateContext:
        //
        break;
    case GeneralContext:
    default:
        break;
    }
}

void TSampleInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TSampleInfo::setAuthor(const TUserInfo &author)
{
    d_func()->author = author;
}

void TSampleInfo::setExtraAuthors(const QList<TUserInfo> &list)
{
    d_func()->extraAuthors = list;
}

void TSampleInfo::setTitle(const QString &title)
{
    d_func()->title = title;
}

void TSampleInfo::setType(Type t)
{
    d_func()->type = t;
}

void TSampleInfo::setFileName(const QString &fileName)
{
    d_func()->fileName = !fileName.isEmpty() ? QFileInfo(fileName).fileName() : QString();
}

void TSampleInfo::setTags(const QStringList &list)
{
    d_func()->tags = list;
}

void TSampleInfo::setTags(const QString &s)
{
    setTags(tagsFromString(s));
}

void TSampleInfo::setComment(const QString &s)
{
    d_func()->comment = s;
}

void TSampleInfo::setAdminRemark(const QString &s)
{
    d_func()->remark = s;
}

void TSampleInfo::setRating(quint8 r)
{
    d_func()->rating = r;
}

void TSampleInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
}

void TSampleInfo::setModificationDateTime(const QDateTime &dt)
{
    d_func()->modificationDT = dt.toUTC();
}

void TSampleInfo::setUpdateDateTime(const QDateTime &dt)
{
    d_func()->updateDT = dt.toUTC();
}

TSampleInfo::Context TSampleInfo::context() const
{
    return d_func()->context;
}

quint64 TSampleInfo::id() const
{
    return d_func()->id;
}

QString TSampleInfo::idString(int fixedLength) const
{
    QString s = QString::number(d_func()->id);
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend( QString().fill('0', dlen) );
    return s;
}

TUserInfo TSampleInfo::author() const
{
    return d_func()->author;
}

QList<TUserInfo> TSampleInfo::extraAuthors() const
{
    return d_func()->extraAuthors;
}

QString TSampleInfo::title() const
{
    return d_func()->title;
}

TSampleInfo::Type TSampleInfo::type() const
{
    return d_func()->type;
}

QString TSampleInfo::typeString() const
{
    return typeToString(d_func()->type);
}

QString TSampleInfo::fileName() const
{
    return d_func()->fileName;
}

QStringList TSampleInfo::tags() const
{
    return d_func()->tags;
}

QString TSampleInfo::tagsString() const
{
    return tagsToString(d_func()->tags);
}

QString TSampleInfo::comment() const
{
    return d_func()->comment;
}

QString TSampleInfo::adminRemark() const
{
    return d_func()->remark;
}

quint8 TSampleInfo::rating() const
{
    return d_func()->rating;
}

QString TSampleInfo::ratingString(const QString &format) const
{
    QString f = !format.isEmpty() ? format : QString("%r");
    return f.replace("%r", QString::number(d_func()->rating));
}

QDateTime TSampleInfo::creationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->creationDT.toTimeSpec(spec);
}

QDateTime TSampleInfo::modificationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->modificationDT.toTimeSpec(spec);
}

QDateTime TSampleInfo::updateDateTime(Qt::TimeSpec spec) const
{
    return d_func()->updateDT.toTimeSpec(spec);
}

bool TSampleInfo::isValid(Context c) const
{
    const B_D(TSampleInfo);
    switch (c)
    {
    case GeneralContext:
    default:
        return d->id && d->author.isValid() && !d->title.isEmpty() && !d->fileName.isEmpty()
                && d->creationDT.isValid() && d->modificationDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TSampleInfo &TSampleInfo::operator =(const TSampleInfo &other)
{
    B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    d->id = dd->id;
    d->author = dd->author;
    d->extraAuthors = dd->extraAuthors;
    d->title = dd->title;
    d->type = dd->type;
    d->fileName = dd->fileName;
    d->tags = dd->tags;
    d->comment = dd->comment;
    d->remark = dd->remark;
    d->rating = dd->rating;
    d->creationDT = dd->creationDT;
    d->modificationDT = dd->modificationDT;
    d->updateDT = dd->updateDT;
    return *this;
}

bool TSampleInfo::operator ==(const TSampleInfo &other) const
{
    const B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    return d->id == dd->id;
    /* && d->authorId == dd->authorId && d->authorName == dd->authorName && d->title == dd->title
            && d->type == dd->type && d->tags == dd->tags && d->comment == dd->comment && d->remark == dd->remark
            && d->rating == dd->rating && d->creationDT == dd->creationDT && d->modificationDT == dd->modificationDT*/
}

TSampleInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSampleInfo &info)
{
    const TSampleInfoPrivate *d = info.d_func();
    stream << d->id;
    stream << d->author;
    stream << d->extraAuthors;
    stream << d->title;
    stream << (int) d->type;
    stream << d->fileName;
    stream << d->tags;
    stream << d->comment;
    stream << d->remark;
    stream << d->rating;
    stream << d->creationDT;
    stream << d->modificationDT;
    stream << d->updateDT;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSampleInfo &info)
{
    static const QList<int> types = bRangeD(TSampleInfo::Unverified, TSampleInfo::Rejected);
    TSampleInfoPrivate *d = info.d_func();
    stream >> d->id;
    stream >> d->author;
    stream >> d->extraAuthors;
    stream >> d->title;
    int t = TSampleInfo::Unverified;
    stream >> t;
    d->type = types.contains(t) ? static_cast<TSampleInfo::Type>(t) : TSampleInfo::Unverified;
    stream >> d->fileName;
    stream >> d->tags;
    stream >> d->comment;
    stream >> d->remark;
    stream >> d->rating;
    stream >> d->creationDT;
    if (d->creationDT.timeSpec() != Qt::UTC)
        d->creationDT = d->creationDT.toUTC();
    stream >> d->modificationDT;
    if (d->modificationDT.timeSpec() != Qt::UTC)
        d->modificationDT = d->modificationDT.toUTC();
    stream >> d->updateDT;
    if (d->updateDT.timeSpec() != Qt::UTC)
        d->updateDT = d->updateDT.toUTC();
    return stream;
}

QDebug operator <<(QDebug dbg, const TSampleInfo &info)
{
    const TSampleInfoPrivate *d = info.d_func();
    dbg.nospace() << "TSampleInfo(" << d->id << "," << d->author.login() << "," << d->title << ","
                  << info.typeString() << "," << d->fileName << "," << info.ratingString() << "," << d->creationDT << ","
                  << d->modificationDT << "," << d->updateDT << ")";
    return dbg.space();
}
