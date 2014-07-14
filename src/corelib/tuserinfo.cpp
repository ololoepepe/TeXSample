#include "tuserinfo.h"

#include "taccesslevel.h"
#include "tidlist.h"
#include "tnamespace.h"
#include "tservicelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

class TUserInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserInfo)
public:
    TAccessLevel accessLevel;
    bool active;
    QImage avatar;
    bool containsAvatar;
    QString email;
    TIdList groups;
    quint64 id;
    QDateTime lastModificationDateTime;
    QString login;
    QString name;
    QString patronymic;
    QDateTime registrationDateTime;
    TServiceList services;
    QString surename;
public:
    explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TUserInfoPrivate)
};

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

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
    active = true;
    containsAvatar = false;
    id = 0;
    lastModificationDateTime.setTimeSpec(Qt::UTC);
    registrationDateTime.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserInfo::TUserInfo() :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
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

TAccessLevel TUserInfo::accessLevel() const
{
    return d_func()->accessLevel;
}

bool TUserInfo::active() const
{
    return d_func()->active;
}

QImage TUserInfo::avatar() const
{
    return d_func()->avatar;
}

bool TUserInfo::containsAvatar() const
{
    return d_func()->containsAvatar;
}

void TUserInfo::clear()
{
    B_D(TUserInfo);
    d->accessLevel = TAccessLevel();
    d->active = true;
    d->avatar = QImage();
    d->containsAvatar = false;
    d->email.clear();
    d->id = 0;
    d->lastModificationDateTime = QDateTime().toUTC();
    d->login.clear();
    d->name.clear();
    d->patronymic.clear();
    d->registrationDateTime = QDateTime().toUTC();
    d->services.clear();
    d->surename.clear();
}

QString TUserInfo::email() const
{
    return d_func()->email;
}

TIdList TUserInfo::groups() const
{
    return d_func()->groups;
}

quint64 TUserInfo::id() const
{
    return d_func()->id;
}

bool TUserInfo::isValid() const
{
    const B_D(TUserInfo);
    return d->accessLevel.isValid() && d->id && !d->login.isEmpty() && d->registrationDateTime.isValid();
}

QDateTime TUserInfo::lastModificationDateTime() const
{
    return d_func()->lastModificationDateTime;
}

QString TUserInfo::login() const
{
    return d_func()->login;
}

QString TUserInfo::name() const
{
    return d_func()->name;
}

QString TUserInfo::patronymic() const
{
    return d_func()->patronymic;
}

QDateTime TUserInfo::registrationDateTime() const
{
    return d_func()->registrationDateTime;
}

TServiceList TUserInfo::services() const
{
    return d_func()->services;
}

void TUserInfo::setAccessLevel(const TAccessLevel &lvl)
{
    d_func()->accessLevel = lvl;
}

void TUserInfo::setActive(bool active)
{
    d_func()->active = active;
}

void TUserInfo::setAvatar(const QImage &avatar)
{
    d_func()->avatar = Texsample::testAvatar(avatar) ? avatar : QImage();
    d_func()->containsAvatar = true;
}

void TUserInfo::setContainsAvatar(bool contains)
{
    d_func()->containsAvatar = contains;
}

void TUserInfo::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

void TUserInfo::setGroups(const TIdList &groups)
{
    B_D(TUserInfo);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TUserInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TUserInfo::setLastModificationDateTime(const QDateTime &dt)
{
    d_func()->lastModificationDateTime = dt.toUTC();
}

void TUserInfo::setLogin(const QString &login)
{
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

void TUserInfo::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TUserInfo::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testName(patronymic) ? patronymic : QString();
}

void TUserInfo::setRegistrationDateTime(const QDateTime &dt)
{
    d_func()->registrationDateTime = dt.toUTC();
}

void TUserInfo::setServices(const TServiceList &services)
{
    B_D(TUserInfo);
    d->services = services;
    bRemoveDuplicates(d->services);
}

void TUserInfo::setSurename(const QString &surename)
{
    d_func()->surename = Texsample::testName(surename) ? surename : QString();
}

QString TUserInfo::surename() const
{
    return d_func()->surename;
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    d->accessLevel = dd->accessLevel;
    d->active = dd->active;
    d->avatar = dd->avatar;
    d->containsAvatar = dd->containsAvatar;
    d->email = dd->email;
    d->groups = dd->groups;
    d->id = dd->id;
    d->lastModificationDateTime = dd->lastModificationDateTime;
    d->login = dd->login;
    d->name = dd->name;
    d->patronymic = dd->patronymic;
    d->registrationDateTime = dd->registrationDateTime;
    d->services = dd->services;
    d->surename = dd->surename;
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    const B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    return d->accessLevel == dd->accessLevel && d->active == dd->active && d->avatar == dd->avatar
            && d->containsAvatar == dd->containsAvatar && d->email == dd->email && d->groups == dd->groups
            && d->id == dd->id && d->lastModificationDateTime == dd->lastModificationDateTime && d->login == dd->login
            && d->name == dd->name && d->patronymic == dd->patronymic
            && d->registrationDateTime == dd->registrationDateTime && d->services == dd->services
            && d->surename == dd->surename;
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
    m.insert("access_level", d->accessLevel);
    m.insert("active", d->active);
    m.insert("avatar", d->avatar);
    m.insert("contains_avatar", d->containsAvatar);
    m.insert("email", d->email);
    m.insert("groups", d->groups);
    m.insert("id", d->id);
    m.insert("last_modification_date_time", d->lastModificationDateTime);
    m.insert("login", d->login);
    m.insert("name", d->name);
    m.insert("patronymic", d->patronymic);
    m.insert("registration_date_time", d->registrationDateTime);
    m.insert("services", d->services);
    m.insert("surename", d->surename);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    TUserInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->accessLevel = m.value("access_level").value<TAccessLevel>();
    d->active = m.value("active", true).toBool();
    d->avatar = m.value("avatar").value<QImage>();
    d->containsAvatar = m.value("contains_avatar").toBool();
    d->email = m.value("email").toString();
    d->groups = m.value("groups").value<TIdList>();
    d->id = m.value("id").toULongLong();
    d->lastModificationDateTime = m.value("last_modification_date_time").toDateTime().toUTC();
    d->login = m.value("login").toString();
    d->name = m.value("name").toString();
    d->patronymic = m.value("patronymic").toString();
    d->registrationDateTime = m.value("registration_date_time").toDateTime().toUTC();
    d->services = m.value("services").value<TServiceList>();
    d->surename = m.value("surename").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    dbg.nospace() << "TUserInfo(" << d->id << "," << d->login << ")";
    return dbg.space();
}
