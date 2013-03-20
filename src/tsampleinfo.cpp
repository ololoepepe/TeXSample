#include "tsampleinfo.h"

#include "tglobal.h"

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

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

class TSampleInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSampleInfo)
public:
   static QString numberToString(quint64 number, int fixedLength = -1);
public:
   explicit TSampleInfoPrivate(TSampleInfo *q);
    ~TSampleInfoPrivate();
public:
    void init();
public:
    quint64 id;
    quint64 authorId;
    QString authorName;
    QString title;
    TSampleInfo::Type type;
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

QString TSampleInfoPrivate::numberToString(quint64 number, int fixedLength)
{
    QString s = QString::number(number);
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend( QString().fill('0', dlen) );
    return s;
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
    id = 0;
    authorId = 0;
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

void TSampleInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TSampleInfo::setAuthorId(quint64 id)
{
    d_func()->authorId = id;
}

void TSampleInfo::setAuthorName(const QString &name)
{
    d_func()->authorName = name;
}

void TSampleInfo::setTitle(const QString &title)
{
    d_func()->title = title;
}

void TSampleInfo::setType(Type t)
{
    d_func()->type = t;
}

void TSampleInfo::setTags(const QStringList &list)
{
    d_func()->tags = list;
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

quint64 TSampleInfo::id() const
{
    return d_func()->id;
}

QString TSampleInfo::idString(int fixedLength) const
{
    return TSampleInfoPrivate::numberToString(d_func()->id, fixedLength);
}

quint64 TSampleInfo::authorId() const
{
    return d_func()->authorId;
}

QString TSampleInfo::authorIdString(int fixedLength) const
{
    return TSampleInfoPrivate::numberToString(d_func()->authorId, fixedLength);
}

QString TSampleInfo::authorName() const
{
    return d_func()->authorName;
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
    QString f = (format.count("%r") == 1 && !format.contains("%1")) ? format : "%r";
    return f.replace("%r", "%1").arg(d_func()->rating);
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

bool TSampleInfo::isValid() const
{
    const B_D(TSampleInfo);
    return d->id && d->authorId && !d->authorName.isEmpty() && !d->title.isEmpty()
            && d->creationDT.isValid() && d->modificationDT.isValid();
}

/*============================== Public operators ==========================*/

TSampleInfo &TSampleInfo::operator =(const TSampleInfo &other)
{
    B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    d->id = dd->id;
    d->authorId = dd->authorId;
    d->authorName = dd->authorName;
    d->title = dd->title;
    d->type = dd->type;
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
    stream << d->authorId;
    stream << d->authorName;
    stream << d->title;
    stream << (int) d->type;
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
    TSampleInfoPrivate *d = info.d_func();
    stream >> d->id;
    stream >> d->authorId;
    stream >> d->authorName;
    stream >> d->title;
    int t = TSampleInfo::Unverified;
    stream >> t;
    d->type = static_cast<TSampleInfo::Type>(t);
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
    dbg.nospace() << "TSampleInfo(" << d->id << "," << d->authorId << "," << d->authorName << "," << d->title << ","
                  << info.typeString() << "," << info.ratingString() << "," << d->creationDT << ","
                  << d->modificationDT << "," << d->updateDT << ")";
    return dbg.space();
}
