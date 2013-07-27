#include "tsampleinfo.h"
#include "tglobal.h"
#include "tuserinfo.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTranslator>
#include <BeQt>

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
#include <QVariantMap>

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
    TUserInfo sender;
    QStringList authors;
    QString title;
    TSampleInfo::Type type;
    QString fileName;
    int size;
    QStringList tags;
    QString comment;
    QString remark;
    quint8 rating;
    QDateTime creationDT;
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
    size = 0;
    rating = 0;
    creationDT.setTimeSpec(Qt::UTC);
    updateDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TSampleInfo::typeToString(Type t, bool singular)
{
    switch (t)
    {
    case Approved:
        return singular ? tr("Approved", "type (singular)") : tr("Approved", "type (plural)");
    case Rejected:
        return singular ? tr("Rejected", "type (singular)") : tr("Rejected", "type (plural)");
    default:
    case Unverified:
        return singular ? tr("Unverified", "type (singular)") : tr("Unverified", "type (plural)");
    }
}

QString TSampleInfo::typeToStringNoTr(Type t, bool)
{
    switch (t)
    {
    case Approved:
        return "Approved";
    case Rejected:
        return "Rejected";
    default:
    case Unverified:
        return "Unverified";
    }
}

QList<TSampleInfo::Type> TSampleInfo::allTypes()
{
    return QList<Type>() << Unverified << Approved << Rejected;
}

QString TSampleInfo::listToString(const QStringList &list)
{
    QStringList nlist = list;
    nlist.removeAll("");
    nlist.removeDuplicates();
    return nlist.join(", ");
}

QStringList TSampleInfo::listFromString(const QString &s)
{
    QStringList sl = s.split(QRegExp("(\\,|\n+\\,?)\\s*"), QString::SkipEmptyParts);
    sl.removeAll("");
    sl.removeDuplicates();
    return sl;
}

TSampleInfo::Type TSampleInfo::typeFromInt(int t)
{
    static const QList<int> types = bRangeM(Approved, Rejected);
    return types.contains(t) ? static_cast<Type>(t) : Unverified;
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
        d->sender.clear();
        d->type = Unverified;
        d->remark.clear();
        d->rating = 0;
        d->creationDT = QDateTime().toUTC();
        d->updateDT = QDateTime().toUTC();
        d->size = 0;
        break;
    case EditContext:
        d->sender.clear();
        d->creationDT = QDateTime().toUTC();
        d->updateDT = QDateTime().toUTC();
        d->size = 0;
        break;
    case UpdateContext:
        d->sender.clear();
        d->type = Unverified;
        d->remark.clear();
        d->rating = 0;
        d->creationDT = QDateTime().toUTC();
        d->updateDT = QDateTime().toUTC();
        d->size = 0;
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

void TSampleInfo::setSender(const TUserInfo &s)
{
    d_func()->sender = s.toContext(TUserInfo::BriefInfoContext);
}

void TSampleInfo::setAuthors(const QStringList &list)
{
    d_func()->authors = bWithoutDuplicates(list);
    d_func()->authors.removeAll("");
}

void TSampleInfo::setTitle(const QString &title)
{
    d_func()->title = (title.length() <= 120) ? title : QString();
}

void TSampleInfo::setType(int t)
{
    d_func()->type = typeFromInt(t);
}

void TSampleInfo::setFileName(const QString &fileName)
{
    d_func()->fileName = !fileName.isEmpty() ? QFileInfo(fileName).fileName() : QString();
    if (d_func()->fileName.indexOf(QRegExp("^[a-zA-Z0-9\\-]+\\.tex$")))
        d_func()->fileName.clear();
}

void TSampleInfo::setProjectSize(int size)
{
    d_func()->size = (size > 0) ? size : 0;
}

void TSampleInfo::setTags(const QStringList &list)
{
    d_func()->tags = bWithoutDuplicates(list);
    d_func()->tags.removeAll("");
}

void TSampleInfo::setTags(const QString &s)
{
    setTags(listFromString(s));
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
    d_func()->rating = (r < 100) ? r : 100;
}

void TSampleInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
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

TUserInfo TSampleInfo::sender() const
{
    return d_func()->sender;
}

QStringList TSampleInfo::authors() const
{
    return d_func()->authors;
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

QString TSampleInfo::typeStringNoTr() const
{
    return typeToStringNoTr(d_func()->type);
}

QString TSampleInfo::fileName() const
{
    return d_func()->fileName;
}

int TSampleInfo::projectSize() const
{
    return d_func()->size;
}

QString TSampleInfo::projectSizeString(BeQt::FileSizeFormat format, quint8 precision) const
{
    return BeQt::fileSizeToString(d_func()->size, format, precision);
}

QString TSampleInfo::projectSizeStringNoTr(BeQt::FileSizeFormat format, quint8 precision) const
{
    return BeQt::fileSizeToStringNoTr(d_func()->size, format, precision);
}

QStringList TSampleInfo::tags() const
{
    return d_func()->tags;
}

QString TSampleInfo::tagsString() const
{
    return listToString(d_func()->tags);
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

QDateTime TSampleInfo::updateDateTime(Qt::TimeSpec spec) const
{
    return d_func()->updateDT.toTimeSpec(spec);
}

bool TSampleInfo::isValid(Context c) const
{
    const B_D(TSampleInfo);

    switch ((CurrentContext == c) ? d->context : c)
    {
    case AddContext:
        return !d->title.isEmpty() && !d->fileName.isEmpty();
    case EditContext:
    case UpdateContext:
        return d->id && !d->title.isEmpty() && !d->fileName.isEmpty();
    case GeneralContext:
    default:
        return d->id && d->sender.isValid(TUserInfo::BriefInfoContext) && !d->title.isEmpty() && !d->fileName.isEmpty()
                && d->size && d->creationDT.isValid() && d->updateDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TSampleInfo &TSampleInfo::operator =(const TSampleInfo &other)
{
    B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    d->context = dd->context;
    d->id = dd->id;
    d->sender = dd->sender;
    d->authors = dd->authors;
    d->title = dd->title;
    d->type = dd->type;
    d->fileName = dd->fileName;
    d->size = dd->size;
    d->tags = dd->tags;
    d->comment = dd->comment;
    d->remark = dd->remark;
    d->rating = dd->rating;
    d->creationDT = dd->creationDT;
    d->updateDT = dd->updateDT;
    return *this;
}

bool TSampleInfo::operator ==(const TSampleInfo &other) const
{
    const B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    if (d->context != dd->context)
        return false;
    switch (d->context)
    {
    case AddContext:
        return d->title == dd->title && d->fileName == dd->fileName;
    case EditContext:
    case UpdateContext:
        return d->id == dd->id;
    case GeneralContext:
    default:
        return d->id == dd->id && d->sender == dd->sender && d->authors == dd->authors && d->title == dd->title
                && d->type == dd->type && d->fileName == dd->fileName && d->size == dd->size && d->tags == dd->tags
                && d->comment == dd->comment && d->remark == dd->remark && d->rating == dd->rating
                && d->creationDT == dd->creationDT && d->updateDT == dd->updateDT;
    }
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
    m.insert("context", (int) d->context);
    m.insert("authors", d->authors);
    m.insert("title", d->title);
    m.insert("file_name", d->fileName);
    m.insert("tags", d->tags);
    m.insert("comment", d->comment);
    if (TSampleInfo::AddContext != d->context)
        m.insert("id", d->id);
    if (TSampleInfo::GeneralContext == d->context)
        m.insert("sender", d->sender);
    if (TSampleInfo::EditContext == d->context || TSampleInfo::GeneralContext == d->context)
        m.insert("type", (int) d->type);
    if (TSampleInfo::EditContext == d->context || TSampleInfo::GeneralContext == d->context)
    {
        m.insert("remark", d->remark);
        m.insert("rating", d->rating);
    }
    if (TSampleInfo::GeneralContext == d->context)
    {
        m.insert("creation_dt", d->creationDT);
        m.insert("update_dt", d->updateDT);
        m.insert("size", d->size);
    }
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSampleInfo &info)
{
    TSampleInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->context = TSampleInfoPrivate::contextFromInt(m.value("context").toInt());
    info.setAuthors(m.value("authors").toStringList());
    d->title = m.value("title").toString();
    info.setFileName(m.value("file_name").toString());
    info.setProjectSize(m.value("size").toInt());
    info.setTags(m.value("tags").toStringList());
    d->comment = m.value("comment").toString();
    d->id = m.value("id").toULongLong();
    info.setSender(m.value("sender").value<TUserInfo>());
    d->type = TSampleInfo::typeFromInt(m.value("type").toInt());
    d->remark = m.value("remark").toString();
    d->rating = m.value("rating").toUInt();
    d->creationDT = m.value("creation_dt").toDateTime().toTimeSpec(Qt::UTC);
    d->updateDT = m.value("update_dt").toDateTime().toTimeSpec(Qt::UTC);
    return stream;
}

QDebug operator <<(QDebug dbg, const TSampleInfo &info)
{
    const TSampleInfoPrivate *d = info.d_func();
    dbg.nospace() << "TSampleInfo(" << d->context << "," << d->id << "," << d->title << ")";
    return dbg.space();
}
