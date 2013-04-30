#include "tuserinfo.h"
#include "tglobal.h"

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
   static TUserInfo::AccessLevel accessLevelFromInt(int lvl);
public:
   explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
    QString storageKey(const QString &subkey) const;
public:
    TUserInfo::Context context;
    quint64 id;
    QString login;
    QByteArray password;
    TUserInfo::AccessLevel accessLevel;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime modificationDT;
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
    static const QList<int> contexts = bRangeD(TUserInfo::GeneralContext, TUserInfo::AuthorizeContext);
    return contexts.contains(c) ? static_cast<TUserInfo::Context>(c) : TUserInfo::GeneralContext;
}

TUserInfo::AccessLevel TUserInfoPrivate::accessLevelFromInt(int lvl)
{
    static const QList<int> levels = bRangeD(TUserInfo::NoLevel, TUserInfo::AdminLevel);
    return levels.contains(lvl) ? static_cast<TUserInfo::AccessLevel>(lvl) : TUserInfo::NoLevel;
}

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
    accessLevel = TUserInfo::NoLevel;
    creationDT.setTimeSpec(Qt::UTC);
    modificationDT.setTimeSpec(Qt::UTC);
    updateDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TUserInfo::accessLevelToString(AccessLevel lvl, bool singular)
{
    if (singular)
    {
        switch (lvl)
        {
        case UserLevel:
            return tr("User", "accessLevel (singular)");
        case ModeratorLevel:
            return tr("Moderator", "accessLevel (singular)");
        case AdminLevel:
            return tr("Administrator", "accessLevel (singular)");
        case NoLevel:
        default:
            return tr("No", "accessLevel (singular)");
        }
    }
    else
    {
        switch (lvl)
        {
        case UserLevel:
            return tr("Users", "accessLevel (plural)");
        case ModeratorLevel:
            return tr("Moderators", "accessLevel (plural)");
        case AdminLevel:
            return tr("Administrators", "accessLevel (plural)");
        case NoLevel:
        default:
            return tr("No", "accessLevel (singular)");
        }
    }
}

/*============================== Public constructors =======================*/

TUserInfo::TUserInfo(Context c) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
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
    switch (cc)
    {
    case ShortInfoContext:
        //
        break;
    case AddContext:
        d->id = 0;
        break;
    case RegisterContext:
        d->id = 0;
        break;
    case UpdateContext:
        //
        break;
    case AuthorizeContext:
        //
        break;
    case GeneralContext:
    default:
        break;
    }
}

/*
    quint64 id;
    QString login;
    QByteArray password;
    TUserInfo::AccessLevel accessLevel;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime modificationDT;
    QDateTime updateDT;
*/

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
    setPassword(QCryptographicHash::hash(s.toUtf8(), QCryptographicHash::Sha1));
}

void TUserInfo::setPassword(const QByteArray &data)
{
    d_func()->password = data;
}

void TUserInfo::setAccessLevel(int lvl)
{
    d_func()->accessLevel = TUserInfoPrivate::accessLevelFromInt(lvl);
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

void TUserInfo::setUpdateDateTime(const QDateTime &dt)
{
    d_func()->updateDT = dt.toUTC();
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

TUserInfo::AccessLevel TUserInfo::accessLevel() const
{
    return d_func()->accessLevel;
}

QString TUserInfo::accessLevelString() const
{
    return accessLevelToString(accessLevel());
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

QDateTime TUserInfo::updateDateTime(Qt::TimeSpec spec) const
{
    return d_func()->updateDT.toTimeSpec(spec);
}

bool TUserInfo::isValid(Context c) const
{
    const B_D(TUserInfo);
    switch ((CurrentContext == c) ? d->context : c)
    {
    case ShortInfoContext:
        return (d->id && !d->login.isEmpty()) || !d->realName.isEmpty();
    case AddContext:
    case RegisterContext:
        return !d->login.isEmpty() && !d->password.isEmpty();
    case UpdateContext:
        return d->id;
    case AuthorizeContext:
        return !d->login.isEmpty() && !d->password.isEmpty();
    case GeneralContext:
    default:
        return d->id && !d->login.isEmpty() && d->creationDT.isValid() && d->modificationDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    setContext(other.context());
    setId(other.id());
    setLogin(other.login());
    setPassword(other.password());
    setAccessLevel(other.accessLevel());
    setRealName(other.realName());
    setAvatar(other.avatar());
    setCreationDateTime(other.creationDateTime());
    setModificationDateTime(other.modificationDateTime());
    setUpdateDateTime(other.updateDateTime());
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    if (context() != other.context())
        return false;
    switch (context())
    {
    case AddContext:
        return login() == other.login() && password() == other.password() && accessLevel() == other.accessLevel()
                && realName() == other.realName() && avatar() == other.avatar();
    case RegisterContext:
        return login() == other.login() && password() == other.password() && realName() == other.realName()
                && avatar() == other.avatar();
    case UpdateContext:
        return 0;
    case AuthorizeContext:
        return 0;
    case GeneralContext:
    default:
        return id() == other.id();
    }
}

TUserInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserInfo &info)
{
    stream << (int) info.context();
    //
    stream << info.id();
    stream << info.login();
    stream << info.password();
    stream << (int) info.accessLevel();
    stream << info.realName();
    stream << info.avatar();
    stream << info.creationDateTime();
    stream << info.modificationDateTime();
    stream << info.updateDateTime();
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    int context = 0;
    stream >> context;
    info.setContext(context);
    //
    quint64 id = 0;
    QString login;
    QByteArray password;
    int accessLevel = 0;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime modificationDT;
    QDateTime updateDT;
    stream >> id;
    stream >> login;
    stream >> password;
    stream >> accessLevel;
    stream >> realName;
    stream >> avatar;
    stream >> creationDT;
    stream >> modificationDT;
    stream >> updateDT;
    info.setId(id);
    info.setLogin(login);
    info.setPassword(password);
    info.setAccessLevel(TUserInfoPrivate::accessLevelFromInt(accessLevel));
    info.setRealName(realName);
    info.setAvatar(avatar);
    info.setCreationDateTime(creationDT);
    info.setModificationDateTime(modificationDT);
    info.setUpdateDateTime(updateDT);
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    dbg.nospace() << "TUserInfo(" << info.id() << "," << info.login() << "," << info.accessLevelString() << ")";
    return dbg.space();
}
