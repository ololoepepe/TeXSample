#include "tuserinfo.h"
#include "tglobal.h"
#include "taccesslevel.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QCryptographicHash>

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

class TUserInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserInfo)
public:
   static TUserInfo::Context contextFromInt(int c);
public:
   static const QList<TUserInfo::Context> IdContexts;
   static const QList<TUserInfo::Context> LoginContexts;
   static const QList<TUserInfo::Context> PasswordContexts;
   static const QList<TUserInfo::Context> AccessLevelContexts;
   static const QList<TUserInfo::Context> RealNameContexts;
   static const QList<TUserInfo::Context> AvatarContexts;
   static const QList<TUserInfo::Context> CreationDTContexts;
   static const QList<TUserInfo::Context> ModificationDTContexts;
public:
   explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
public:
    TUserInfo::Context context;
    quint64 id;
    QString login;
    QByteArray password;
    TAccessLevel accessLevel;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime modificationDT;
private:
    Q_DISABLE_COPY(TUserInfoPrivate)
};

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

/*============================== Static public methods =====================*/

TUserInfo::Context TUserInfoPrivate::contextFromInt(int c)
{
    static const QList<int> contexts = bRangeD(TUserInfo::GeneralContext, TUserInfo::UpdateContext);
    return contexts.contains(c) ? static_cast<TUserInfo::Context>(c) : TUserInfo::GeneralContext;
}

/*============================== Static public constants ===================*/

const QList<TUserInfo::Context> TUserInfoPrivate::IdContexts =
    QList<TUserInfo::Context>() << TUserInfo::ShortInfoContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::LoginContexts =
    QList<TUserInfo::Context>() << TUserInfo::ShortInfoContext << TUserInfo::AddContext
    << TUserInfo::RegisterContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::PasswordContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::AccessLevelContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::EditContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::RealNameContexts =
    QList<TUserInfo::Context>() << TUserInfo::ShortInfoContext << TUserInfo::AddContext << TUserInfo::RegisterContext
    << TUserInfo::EditContext << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::AvatarContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::CreationDTContexts =
    QList<TUserInfo::Context>() << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::ModificationDTContexts =
    QList<TUserInfo::Context>() << TUserInfo::GeneralContext;

/*============================== Public constructors =======================*/

TUserInfoPrivate::TUserInfoPrivate(TUserInfo *q) :
    BBasePrivate(q)
{
    //
}

TUserInfoPrivate::~TUserInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserInfoPrivate::init()
{
    context = TUserInfo::GeneralContext;
    id = 0;
    creationDT.setTimeSpec(Qt::UTC);
    modificationDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserInfo::TUserInfo(Context c) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
}

TUserInfo::TUserInfo(quint64 id, Context c) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
    setId(id);
}

TUserInfo::TUserInfo(const TUserInfo &other) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TUserInfo::~TUserInfo()
{
    //
}

/*============================== Public methods ============================*/

void TUserInfo::setContext(int c, bool clear)
{
    B_D(TUserInfo);
    Context cc = TUserInfoPrivate::contextFromInt(c);
    if (cc == d->context)
        return;
    d->context = cc;
    if (!clear)
        return;
    if (!TUserInfoPrivate::IdContexts.contains(d->context))
        d->id = 0;
    if (!TUserInfoPrivate::LoginContexts.contains(d->context))
        d->login.clear();
    if (!TUserInfoPrivate::PasswordContexts.contains(d->context))
        d->password.clear();
    if (!TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        d->accessLevel = TAccessLevel();
    if (!TUserInfoPrivate::RealNameContexts.contains(d->context))
        d->realName.clear();
    if (!TUserInfoPrivate::AvatarContexts.contains(d->context))
        d->avatar.clear();
    if (!TUserInfoPrivate::CreationDTContexts.contains(d->context))
        d->creationDT = QDateTime().toUTC();
    if (!TUserInfoPrivate::ModificationDTContexts.contains(d->context))
        d->modificationDT = QDateTime().toUTC();
}

void TUserInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TUserInfo::setLogin(const QString &login)
{
    d_func()->login = login;
}

void TUserInfo::setPassword(const QString &s)
{
    setPassword(!s.isEmpty() ? QCryptographicHash::hash(s.toUtf8(), QCryptographicHash::Sha1) : QByteArray());
}

void TUserInfo::setPassword(const QByteArray &data)
{
    d_func()->password = data;
}

void TUserInfo::setAccessLevel(const TAccessLevel &lvl)
{
    d_func()->accessLevel = lvl;
}

void TUserInfo::setRealName(const QString &name)
{
    d_func()->realName = name;
}

void TUserInfo::setAvatar(const QByteArray &data)
{
    d_func()->avatar = data;
}

void TUserInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
}

void TUserInfo::setModificationDateTime(const QDateTime &dt)
{
    d_func()->modificationDT = dt.toUTC();
}

void TUserInfo::clear()
{
    B_D(TUserInfo);
    d->id = 0;
    d->login.clear();
    d->password.clear();
    d->accessLevel = TAccessLevel();
    d->realName.clear();
    d->avatar.clear();
    d->creationDT = QDateTime().toUTC();
    d->modificationDT = QDateTime().toUTC();
}

TUserInfo::Context TUserInfo::context() const
{
    return d_func()->context;
}

quint64 TUserInfo::id() const
{
    return d_func()->id;
}

QString TUserInfo::idString(int fixedLength) const
{
    QString s = QString::number(id());
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend(QString().fill('0', dlen));
    return s;
}

QString TUserInfo::login() const
{
    return d_func()->login;
}

QByteArray TUserInfo::password() const
{
    return d_func()->password;
}

TAccessLevel TUserInfo::accessLevel() const
{
    return d_func()->accessLevel;
}

QString TUserInfo::accessLevelString() const
{
    return d_func()->accessLevel.string();
}

QString TUserInfo::realName() const
{
    return d_func()->realName;
}

QByteArray TUserInfo::avatar() const
{
    return d_func()->avatar;
}

QDateTime TUserInfo::creationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->creationDT.toTimeSpec(spec);
}

QDateTime TUserInfo::modificationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->modificationDT.toTimeSpec(spec);
}

bool TUserInfo::isValid(Context c) const
{
    const B_D(TUserInfo);
    switch ((CurrentContext == c) ? d->context : c)
    {
    case ShortInfoContext:
        return d->id && !d->login.isEmpty();
    case AddContext:
    case RegisterContext:
        return !d->login.isEmpty() && !d->password.isEmpty();
    case EditContext:
        return d->id;
    case UpdateContext:
        return d->id && !d->password.isEmpty();
    case GeneralContext:
    default:
        return d->id && !d->login.isEmpty() && d->creationDT.isValid() && d->modificationDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    d->context = dd->context;
    d->id = dd->id;
    d->login = dd->login;
    d->password = dd->password;
    d->accessLevel = dd->accessLevel;
    d->realName = dd->realName;
    d->avatar = dd->avatar;
    d->creationDT = dd->creationDT;
    d->modificationDT = dd->modificationDT;
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    const B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    if (context() != other.context())
        return false;
    bool b = true;
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        b = b && d->id == dd->id;
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        b = b && d->login == dd->login;
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        b = b && d->password == dd->password;
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        b = b && d->accessLevel == dd->accessLevel;
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        b = b && d->realName == dd->realName;
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        b = b && d->avatar == dd->avatar;
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        b = b && d->creationDT == dd->creationDT;
    if (TUserInfoPrivate::ModificationDTContexts.contains(d->context))
        b = b && d->modificationDT == dd->modificationDT;
    return b;
}

bool TUserInfo::operator !=(const TUserInfo &other) const
{
    return !(*this == other);
}

TUserInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    stream << (int) d->context;
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        stream << d->id;
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        stream << d->login;
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        stream << d->password;
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        stream << d->accessLevel;
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        stream << d->realName;
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        stream << d->avatar;
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        stream << d->creationDT;
    if (TUserInfoPrivate::ModificationDTContexts.contains(d->context))
        stream << d->modificationDT;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    TUserInfoPrivate *d = info.d_func();
    int context = 0;
    stream >> context;
    info.setContext(context);
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        stream >> d->id;
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        stream >> d->login;
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        stream >> d->password;
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        stream >> d->accessLevel;
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        stream >> d->realName;
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        stream >> d->avatar;
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
    {
        QDateTime creationDT;
        stream >> creationDT;
        info.setCreationDateTime(creationDT);
    }
    if (TUserInfoPrivate::ModificationDTContexts.contains(d->context))
    {
        QDateTime modificationDT;
        stream >> modificationDT;
        info.setModificationDateTime(modificationDT);
    }
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    dbg.nospace() << "TUserInfo(" << d->id << "," << d->login << "," << info.accessLevelString() << ")";
    return dbg.space();
}
