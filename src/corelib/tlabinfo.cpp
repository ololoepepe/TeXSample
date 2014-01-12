#include "tlabinfo.h"
#include "tglobal.h"
#include "tuserinfo.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>

#include <QObject>
#include <QDataStream>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QRegExp>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>
#include <QFileInfo>
#include <QList>

/*============================================================================
================================ TLabInfoPrivate =============================
============================================================================*/

class TLabInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabInfo)
public:
    static TLabInfo::Context contextFromInt(int c);
public:
    explicit TLabInfoPrivate(TLabInfo *q);
    ~TLabInfoPrivate();
public:
    void init();
public:
    TLabInfo::Context context;
    quint64 id;
    TUserInfo sender;
    QString title;
    QStringList authors;
    TLabInfo::Type type;
    QStringList groups;
    int size;
    QStringList tags;
    QString comment;
    QDateTime creationDT;
    QDateTime updateDT;
    QStringList extraFiles;
private:
    Q_DISABLE_COPY(TLabInfoPrivate)
};

/*============================================================================
================================ TLabInfoPrivate =============================
============================================================================*/

/*============================== Static public methods =====================*/

TLabInfo::Context TLabInfoPrivate::contextFromInt(int c)
{
    static const QList<int> contexts = bRangeD(TLabInfo::GeneralContext, TLabInfo::EditContext);
    return contexts.contains(c) ? static_cast<TLabInfo::Context>(c) : TLabInfo::GeneralContext;
}

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
    context = TLabInfo::GeneralContext;
    id = 0;
    type = TLabInfo::NoType;
    size = 0;
    creationDT.setTimeSpec(Qt::UTC);
    updateDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TLabInfo ====================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TLabInfo::typeToString(Type t, bool singular)
{
    return tr(typeToStringNoTr(t, singular).toUtf8().constData());
}

QString TLabInfo::typeToStringNoTr(Type t, bool singular)
{
    if (singular)
    {
        switch (t)
        {
        case DesktopType:
            return QT_TRANSLATE_NOOP("TLabInfo", "Desktop application");
        case WebType:
            return QT_TRANSLATE_NOOP("TLabInfo", "Web application");
        case UrlType:
            return QT_TRANSLATE_NOOP("TLabInfo", "External URL");
        case NoType:
        default:
            return QT_TRANSLATE_NOOP("TLabInfo", "No");
        }
    }
    else
    {
        switch (t)
        {
        case DesktopType:
            return QT_TRANSLATE_NOOP("TLabInfo", "Desktop applications");
        case WebType:
            return QT_TRANSLATE_NOOP("TLabInfo", "Web applications");
        case UrlType:
            return QT_TRANSLATE_NOOP("TLabInfo", "External URLs");
        case NoType:
        default:
            return QT_TRANSLATE_NOOP("TLabInfo", "No");
        }
    }
}

QString TLabInfo::listToString(const QStringList &list)
{
    return list.join(", ");
}

QStringList TLabInfo::listFromString(const QString &s)
{
    QStringList sl = s.split(QRegExp("(\\,|\n+\\,?)\\s*"), QString::SkipEmptyParts);
    sl.removeAll("");
    sl.removeDuplicates();
    return sl;
}

TLabInfo::Type TLabInfo::typeFromInt(int t)
{
    static const QList<int> types = bRangeD(DesktopType, UrlType);
    return types.contains(t) ? static_cast<Type>(t) : NoType;
}

QList<TLabInfo::Type> TLabInfo::allTypes(bool includeNoType)
{
    QList<Type> list = QList<Type>() << DesktopType << WebType << UrlType;
    if (includeNoType)
        list << NoType;
    return list;
}

/*============================== Public constructors =======================*/

TLabInfo::TLabInfo(Context c) :
    BBase(*new TLabInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
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

void TLabInfo::setContext(int c, bool clear)
{
    B_D(TLabInfo);
    Context cc = TLabInfoPrivate::contextFromInt(c);
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
        d->type = NoType;
        d->size = 0;
        d->creationDT = QDateTime().toUTC();
        d->updateDT = QDateTime().toUTC();
        d->extraFiles.clear();
        break;
    case EditContext:
        d->sender.clear();
        d->size = 0;
        d->creationDT = QDateTime().toUTC();
        d->updateDT = QDateTime().toUTC();
        d->extraFiles.clear();
        break;
    case GeneralContext:
    default:
        break;
    }
}

void TLabInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TLabInfo::setSender(const TUserInfo &sender)
{
    d_func()->sender = sender.toContext(TUserInfo::BriefInfoContext);
}

void TLabInfo::setTitle(const QString &title)
{
    d_func()->title = title;
}

void TLabInfo::setAuthors(const QStringList &list)
{
    d_func()->authors = bWithoutDuplicates(list);
    d_func()->authors.removeAll("");
}

void TLabInfo::setType(int t)
{
    d_func()->type = typeFromInt(t);
}

void TLabInfo::setGroups(const QStringList &list)
{
    d_func()->groups = bWithoutDuplicates(list);
    d_func()->groups.removeAll("");
}

void TLabInfo::setProjectSize(int sz)
{
    d_func()->size = (sz > 0) ? sz : 0;
}

void TLabInfo::setTags(const QStringList &list)
{
    d_func()->tags = bWithoutDuplicates(list);
    d_func()->tags.removeAll("");
}

void TLabInfo::setTags(const QString &s)
{
    setTags(listFromString(s));
}

void TLabInfo::setComment(const QString &s)
{
    d_func()->comment = s;
}

void TLabInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
}

void TLabInfo::setUpdateDateTime(const QDateTime &dt)
{
    d_func()->updateDT = dt.toUTC();
}

void TLabInfo::setExtraAttachedFileNames(const QStringList &list)
{
    d_func()->extraFiles = list;
}

TLabInfo::Context TLabInfo::context() const
{
    return d_func()->context;
}

quint64 TLabInfo::id() const
{
    return d_func()->id;
}

QString TLabInfo::idString(int fixedLength) const
{
    QString s = QString::number(d_func()->id);
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend( QString().fill('0', dlen) );
    return s;
}

TUserInfo TLabInfo::sender() const
{
    return d_func()->sender;
}

QString TLabInfo::title() const
{
    return d_func()->title;
}

QStringList TLabInfo::authors() const
{
    return d_func()->authors;
}

TLabInfo::Type TLabInfo::type() const
{
    return d_func()->type;
}

QString TLabInfo::typeString() const
{
    return typeToString(d_func()->type);
}

QString TLabInfo::typeStringNoTr() const
{
    return typeToStringNoTr(d_func()->type);
}

QStringList TLabInfo::groups() const
{
    return d_func()->groups;
}

int TLabInfo::projectSize() const
{
    return d_func()->size;
}

QString TLabInfo::projectSizeString(BeQt::FileSizeFormat format, quint8 precision) const
{
    return BeQt::fileSizeToString(d_func()->size, format, precision);
}

QString TLabInfo::projectSizeStringNoTr(BeQt::FileSizeFormat format, quint8 precision) const
{
    return BeQt::fileSizeToStringNoTr(d_func()->size, format, precision);
}

QStringList TLabInfo::tags() const
{
    return d_func()->tags;
}

QString TLabInfo::tagsString() const
{
    return listToString(d_func()->tags);
}

QString TLabInfo::comment() const
{
    return d_func()->comment;
}

QDateTime TLabInfo::creationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->creationDT.toTimeSpec(spec);
}

QDateTime TLabInfo::updateDateTime(Qt::TimeSpec spec) const
{
    return d_func()->updateDT.toTimeSpec(spec);
}

QStringList TLabInfo::extraAttachedFileNames() const
{
    return d_func()->extraFiles;
}

bool TLabInfo::isValid(Context c) const
{
    const B_D(TLabInfo);

    switch ((CurrentContext == c) ? d->context : c)
    {
    case AddContext:
        return !d->title.isEmpty();
    case EditContext:
        return d->id && !d->title.isEmpty();
    case GeneralContext:
    default:
        return d->id && d->sender.isValid(TUserInfo::BriefInfoContext) && !d->title.isEmpty() && NoType != d->type
                && d->size && d->creationDT.isValid() && d->updateDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TLabInfo &TLabInfo::operator =(const TLabInfo &other)
{
    B_D(TLabInfo);
    const TLabInfoPrivate *dd = other.d_func();
    d->context = dd->context;
    d->id = dd->id;
    d->sender = dd->sender;
    d->title = dd->title;
    d->authors = dd->authors;
    d->type = dd->type;
    d->groups = dd->groups;
    d->size = dd->size;
    d->tags = dd->tags;
    d->comment = dd->comment;
    d->creationDT = dd->creationDT;
    d->updateDT = dd->updateDT;
    d->extraFiles = dd->extraFiles;
    return *this;
}

bool TLabInfo::operator ==(const TLabInfo &other) const
{
    const B_D(TLabInfo);
    const TLabInfoPrivate *dd = other.d_func();
    if (d->context != dd->context)
        return false;
    switch (d->context)
    {
    case AddContext:
        return d->title == dd->title;
    case EditContext:
        return d->id == dd->id;
    case GeneralContext:
    default:
        return d->id == dd->id && d->sender == dd->sender && d->title == dd->title && d->authors == dd->authors
                && d->type == dd->type &&d->groups == dd->groups && d->size == dd->size && d->tags == dd->tags
                && d->comment == dd->comment && d->creationDT == dd->creationDT && d->updateDT == dd->updateDT
                && d->extraFiles == dd->extraFiles;
    }
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
    m.insert("context", (int) d->context);
    m.insert("title", d->title);
    m.insert("authors", d->authors);
    m.insert("groups", d->groups);
    m.insert("size", d->size);
    m.insert("tags", d->tags);
    m.insert("comment", d->comment);
    if (TLabInfo::AddContext != d->context)
        m.insert("id", d->id);
    if (TLabInfo::GeneralContext == d->context)
        m.insert("sender", d->sender);
    if (TLabInfo::GeneralContext == d->context)
        m.insert("type", (int) d->type);
    if (TLabInfo::GeneralContext == d->context)
    {
        m.insert("creation_dt", d->creationDT);
        m.insert("update_dt", d->updateDT);
        m.insert("extra_file_names", d->extraFiles);
    }
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabInfo &info)
{
    TLabInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->context = TLabInfoPrivate::contextFromInt(m.value("context").toInt());
    d->title = m.value("title").toString();
    info.setAuthors(m.value("authors").toStringList());
    info.setGroups(m.value("groups").toStringList());
    info.setProjectSize(m.value("size").toInt());
    info.setTags(m.value("tags").toStringList());
    d->comment = m.value("comment").toString();
    d->id = m.value("id").toULongLong();
    info.setSender(m.value("sender").value<TUserInfo>());
    info.setType(m.value("type").toInt());
    d->creationDT = m.value("creation_dt").toDateTime().toUTC();
    d->updateDT = m.value("update_dt").toDateTime().toUTC();
    d->extraFiles = m.value("extra_file_names").toStringList();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabInfo &info)
{
    const TLabInfoPrivate *d = info.d_func();
    dbg.nospace() << "TLabInfo(" << d->id << "," << d->sender.login() << "," << d->title << ","
                  << info.typeStringNoTr() << ")";
    return dbg.space();
}
