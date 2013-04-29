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
#include <QSettings>
#include <QCryptographicHash>

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

class TUserInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserInfo)
public:
   static TUserInfo::AccessLevel accessLevelFromInt(int lvl);
public:
   explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
    QString storageKey(const QString &subkey) const;
public:
    quint64 id;
    QString login;
    QByteArray password;
    TUserInfo::AccessLevel accessLevel;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime modificationDT;
    QDateTime updateDT;
    QSettings *storage;
    QString storageSubkey;
private:
    Q_DISABLE_COPY(TUserInfoPrivate)
};

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

/*============================== Static public methods =====================*/

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
    id = 0;
    accessLevel = TUserInfo::NoLevel;
    creationDT.setTimeSpec(Qt::UTC);
    modificationDT.setTimeSpec(Qt::UTC);
    updateDT.setTimeSpec(Qt::UTC);
    storage = 0;
}

QString TUserInfoPrivate::storageKey(const QString &subkey) const
{
    return QString("user_info") + (!storageSubkey.isEmpty() ? "_" : "") + storageSubkey
            + (!subkey.isEmpty() ? "/" : "") + subkey;
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

TUserInfo::TUserInfo(QSettings *storage, const QString &storageSubkey) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    setStorage(storage);
    setStorageSubkey(storageSubkey);
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

void TUserInfo::setId(quint64 id)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("id"), d->id);
    else
        d->id = id;
}

void TUserInfo::setLogin(const QString &login)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("login"), login);
    else
        d->login = login;
}

void TUserInfo::setPassword(const QString &s)
{
    setPassword(QCryptographicHash::hash(s.toUtf8(), QCryptographicHash::Sha1));
}

void TUserInfo::setPassword(const QByteArray &data)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("password"), data);
    else
        d->password = data;
}

void TUserInfo::setAccessLevel(int lvl)
{
    AccessLevel alvl = TUserInfoPrivate::accessLevelFromInt(lvl);
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("access_level"), alvl);
    else
        d->accessLevel = alvl;
}

void TUserInfo::setRealName(const QString &name)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("real_name"), name);
    else
        d->realName = name;
}

void TUserInfo::setAvatar(const QByteArray &data)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("avatar"), data);
    else
        d->avatar = data;
}

void TUserInfo::setCreationDateTime(const QDateTime &dt)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("creation_dt"), dt.toUTC());
    else
        d->creationDT = dt.toUTC();
}

void TUserInfo::setModificationDateTime(const QDateTime &dt)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("modification_dt"), dt.toUTC());
    else
        d->modificationDT = dt.toUTC();
}

void TUserInfo::setUpdateDateTime(const QDateTime &dt)
{
    B_D(TUserInfo);
    if (d->storage)
        d->storage->setValue(d->storageKey("update_dt"), dt.toUTC());
    else
        d->updateDT = dt.toUTC();
}

void TUserInfo::setStorage(QSettings *s)
{
    d_func()->storage = s;
}

void TUserInfo::setStorageSubkey(const QString &subkey)
{
    d_func()->storageSubkey = subkey;
}

quint64 TUserInfo::id() const
{
    const B_D(TUserInfo);
    return d->storage ? d->storage->value(d->storageKey("id")).toULongLong() : d->id;
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
    const B_D(TUserInfo);
    return d->storage ? d->storage->value(d->storageKey("login")).toString() : d->login;
}

QByteArray TUserInfo::password() const
{
    const B_D(TUserInfo);
    return d->storage ? d->storage->value(d->storageKey("password")).toByteArray() : d->password;
}

TUserInfo::AccessLevel TUserInfo::accessLevel() const
{
    const B_D(TUserInfo);
    return d->storage ?
                TUserInfoPrivate::accessLevelFromInt(d->storage->value(d->storageKey("access_level")).toInt()) :
                d->accessLevel;
}

QString TUserInfo::accessLevelString() const
{
    return accessLevelToString(accessLevel());
}

QString TUserInfo::realName() const
{
    const B_D(TUserInfo);
    return d->storage ? d->storage->value(d->storageKey("real_name")).toString() : d->realName;
}

QByteArray TUserInfo::avatar() const
{
    const B_D(TUserInfo);
    return d->storage ? d->storage->value(d->storageKey("avatar")).toByteArray() : d->avatar;
}

QDateTime TUserInfo::creationDateTime(Qt::TimeSpec spec) const
{
    const B_D(TUserInfo);
    return (d->storage ? d->storage->value(d->storageKey("creation_dt")).toDateTime() :
                         d->creationDT).toTimeSpec(spec);
}

QDateTime TUserInfo::modificationDateTime(Qt::TimeSpec spec) const
{
    const B_D(TUserInfo);
    return (d->storage ? d->storage->value(d->storageKey("modification_dt")).toDateTime() :
                         d->modificationDT).toTimeSpec(spec);
}

QDateTime TUserInfo::updateDateTime(Qt::TimeSpec spec) const
{
    const B_D(TUserInfo);
    return (d->storage ? d->storage->value(d->storageKey("update_dt")).toDateTime() : d->updateDT).toTimeSpec(spec);
}

QSettings *TUserInfo::storage() const
{
    return d_func()->storage;
}

QString TUserInfo::storageSubkey() const
{
    return d_func()->storageSubkey;
}

bool TUserInfo::isValid(Context c) const
{
    const B_D(TUserInfo);
    switch (c)
    {
    case AddContext:
        return !d->login.isEmpty() && !d->password.isEmpty();
    case UpdateContext:
        return d->id;
    case GeneralContext:
    default:
        return d->id && !d->login.isEmpty() && d->creationDT.isValid() && d->modificationDT.isValid();
    }
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    setId(other.id());
    setLogin(other.login());
    setPassword(other.password());
    setAccessLevel(other.accessLevel());
    setRealName(other.realName());
    setAvatar(other.avatar());
    setCreationDateTime(other.creationDateTime());
    setModificationDateTime(other.modificationDateTime());
    setUpdateDateTime(other.updateDateTime());
    setStorage(other.storage());
    setStorageSubkey(other.storageSubkey());
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    return id() == other.id();
}

TUserInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserInfo &info)
{
    stream << info.id();
    stream << info.login();
    stream << info.password();
    stream << (int) info.accessLevel();
    stream << info.realName();
    stream << info.avatar();
    stream << info.creationDateTime();
    stream << info.modificationDateTime();
    stream << info.updateDateTime();
    stream << info.storageSubkey();
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    quint64 id = 0;
    QString login;
    QByteArray password;
    int accessLevel = 0;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime modificationDT;
    QDateTime updateDT;
    QString storageSubkey;
    stream >> id;
    stream >> login;
    stream >> password;
    stream >> accessLevel;
    stream >> realName;
    stream >> avatar;
    stream >> creationDT;
    stream >> modificationDT;
    stream >> updateDT;
    stream >> storageSubkey;
    info.setId(id);
    info.setLogin(login);
    info.setPassword(password);
    info.setAccessLevel(TUserInfoPrivate::accessLevelFromInt(accessLevel));
    info.setRealName(realName);
    info.setAvatar(avatar);
    info.setCreationDateTime(creationDT);
    info.setModificationDateTime(modificationDT);
    info.setUpdateDateTime(updateDT);
    info.setStorageSubkey(storageSubkey);
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    dbg.nospace() << "TUserInfo(" << info.id() << "," << info.login() << "," << info.accessLevelString() << ")";
    return dbg.space();
}
