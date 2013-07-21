#include "tuserinfo.h"
#include "tglobal.h"
#include "taccesslevel.h"
#include "tservice.h"
#include "tservicelist.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTranslator>

#include <QObject>
#include <QDataStream>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QCryptographicHash>
#include <QVariantMap>
#include <QList>

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
   static const QList<TUserInfo::Context> EmailContexts;
   static const QList<TUserInfo::Context> LoginContexts;
   static const QList<TUserInfo::Context> PasswordContexts;
   static const QList<TUserInfo::Context> AccessLevelContexts;
   static const QList<TUserInfo::Context> ServicesContexts;
   static const QList<TUserInfo::Context> RealNameContexts;
   static const QList<TUserInfo::Context> AvatarContexts;
   static const QList<TUserInfo::Context> CreationDTContexts;
   static const QList<TUserInfo::Context> UpdateDTContexts;
public:
   explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
public:
    TUserInfo::Context context;
    quint64 id;
    QString email;
    QString login;
    QByteArray password;
    TAccessLevel accessLevel;
    TServiceList services;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime updateDT;
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
    QList<TUserInfo::Context>() << TUserInfo::BriefInfoContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::EmailContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext;
const QList<TUserInfo::Context> TUserInfoPrivate::LoginContexts =
    QList<TUserInfo::Context>() << TUserInfo::BriefInfoContext << TUserInfo::AddContext
    << TUserInfo::RegisterContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::PasswordContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::AccessLevelContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::EditContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::ServicesContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::EditContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::RealNameContexts =
    QList<TUserInfo::Context>() << TUserInfo::BriefInfoContext << TUserInfo::AddContext << TUserInfo::RegisterContext
    << TUserInfo::EditContext << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::AvatarContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::CreationDTContexts =
    QList<TUserInfo::Context>() << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::UpdateDTContexts =
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
    updateDT.setTimeSpec(Qt::UTC);
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
    if (!TUserInfoPrivate::EmailContexts.contains(d->context))
        d->email.clear();
    if (!TUserInfoPrivate::LoginContexts.contains(d->context))
        d->login.clear();
    if (!TUserInfoPrivate::PasswordContexts.contains(d->context))
        d->password.clear();
    if (!TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        d->accessLevel = TAccessLevel();
    if (!TUserInfoPrivate::ServicesContexts.contains(d->context))
        d->services.clear();
    if (!TUserInfoPrivate::RealNameContexts.contains(d->context))
        d->realName.clear();
    if (!TUserInfoPrivate::AvatarContexts.contains(d->context))
        d->avatar.clear();
    if (!TUserInfoPrivate::CreationDTContexts.contains(d->context))
        d->creationDT = QDateTime().toUTC();
    if (!TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        d->updateDT = QDateTime().toUTC();
}

void TUserInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TUserInfo::setEmail(const QString &email)
{
    d_func()->email = email;
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

void TUserInfo::setServices(const TServiceList &list)
{
    d_func()->services = list;
    bRemoveDuplicates(d_func()->services);
}

void TUserInfo::setServices(const QList<int> &list)
{
    d_func()->services = TServiceList::serviceListFromIntList(list);
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

void TUserInfo::setUpdateDateTime(const QDateTime &dt)
{
    d_func()->updateDT = dt.toUTC();
}

void TUserInfo::clear()
{
    B_D(TUserInfo);
    d->id = 0;
    d->email.clear();
    d->login.clear();
    d->password.clear();
    d->accessLevel = TAccessLevel();
    d->realName.clear();
    d->avatar.clear();
    d->creationDT = QDateTime().toUTC();
    d->updateDT = QDateTime().toUTC();
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

QString TUserInfo::email() const
{
    return d_func()->email;
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
    return d_func()->accessLevel.toString();
}

QString TUserInfo::accessLevelStringNoTr() const
{
    return d_func()->accessLevel.toStringNoTr();
}

TServiceList TUserInfo::services() const
{
    return d_func()->services;
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

QDateTime TUserInfo::updateDateTime(Qt::TimeSpec spec) const
{
    return d_func()->updateDT.toTimeSpec(spec);
}

bool TUserInfo::isValid(Context c) const
{
    const B_D(TUserInfo);
    switch ((CurrentContext == c) ? d->context : c)
    {
    case BriefInfoContext:
        return d->id && !d->login.isEmpty();
    case AddContext:
    case RegisterContext:
        return !d->email.isEmpty() && !d->login.isEmpty() && !d->password.isEmpty();
    case EditContext:
        return d->id;
    case UpdateContext:
        return d->id && !d->password.isEmpty();
    case GeneralContext:
    default:
        return d->id && !d->login.isEmpty() && d->creationDT.isValid() && d->updateDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    d->context = dd->context;
    d->id = dd->id;
    d->email = dd->email;
    d->login = dd->login;
    d->password = dd->password;
    d->accessLevel = dd->accessLevel;
    d->services = dd->services;
    d->realName = dd->realName;
    d->avatar = dd->avatar;
    d->creationDT = dd->creationDT;
    d->updateDT = dd->updateDT;
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
    if (TUserInfoPrivate::EmailContexts.contains(d->context))
        b = b && d->email == dd->email;
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        b = b && d->login == dd->login;
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        b = b && d->password == dd->password;
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        b = b && d->accessLevel == dd->accessLevel;
    if (TUserInfoPrivate::ServicesContexts.contains(d->context))
        b = b && d->services == dd->services;
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        b = b && d->realName == dd->realName;
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        b = b && d->avatar == dd->avatar;
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        b = b && d->creationDT == dd->creationDT;
    if (TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        b = b && d->updateDT == dd->updateDT;
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
    QVariantMap m;
    m.insert("context", (int) d->context);
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        m.insert("id", d->id);
    if (TUserInfoPrivate::EmailContexts.contains(d->context))
        m.insert("email", d->email);
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        m.insert("login", d->login);
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        m.insert("password", d->password);
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        m.insert("access_level", d->accessLevel);
    if (TUserInfoPrivate::ServicesContexts.contains(d->context))
        m.insert("services", d->services);
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        m.insert("real_name", d->realName);
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        m.insert("avatar", d->avatar);
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        m.insert("creation_dt", d->creationDT);
    if (TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        m.insert("update_dt", d->updateDT);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    TUserInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->context = TUserInfoPrivate::contextFromInt(m.value("context").toInt());
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        d->id = m.value("id").toULongLong();
    if (TUserInfoPrivate::EmailContexts.contains(d->context))
        d->email = m.value("email").toString();
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        d->login = m.value("login").toString();
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        d->password = m.value("password").toByteArray();
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        d->accessLevel = m.value("access_level").value<TAccessLevel>();
    if (TUserInfoPrivate::ServicesContexts.contains(d->context))
    {
        d->services = m.value("services").value<TServiceList>();
        bRemoveDuplicates(d->services);
    }
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        d->realName = m.value("real_name").toString();
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        d->avatar = m.value("avatar").toByteArray();
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        d->creationDT = m.value("creation_dt").toDateTime().toTimeSpec(Qt::UTC);
    if (TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        d->updateDT = m.value("update_dt").toDateTime().toTimeSpec(Qt::UTC);
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    dbg.nospace() << "TUserInfo(" << d->context << "," << d->id << "," << d->login << ")";
    return dbg.space();
}
