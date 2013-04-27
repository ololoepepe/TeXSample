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

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

class TUserInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserInfo)
public:
   //
public:
   explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
public:
    quint64 id;
    QString login;
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

//

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
            return tr("User", "type (singular)");
        case ModeratorLevel:
            return tr("Moderator", "type (singular)");
        case AdminLevel:
            return tr("Administrator", "type (singular)");
        case NoLevel:
        default:
            return tr("No", "type (singular)");
        }
    }
    else
    {
        switch (lvl)
        {
        case UserLevel:
            return tr("Users", "type (plural)");
        case ModeratorLevel:
            return tr("Moderators", "type (plural)");
        case AdminLevel:
            return tr("Administrators", "type (plural)");
        case NoLevel:
        default:
            return tr("No", "type (singular)");
        }
    }
}

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

void TUserInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TUserInfo::setLogin(const QString &login)
{
    d_func()->login = login;
}

void TUserInfo::setAccessLevel(AccessLevel lvl)
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

void TUserInfo::setUpdateDateTime(const QDateTime &dt)
{
    d_func()->updateDT = dt.toUTC();
}

quint64 TUserInfo::id() const
{
    return d_func()->id;
}

QString TUserInfo::idString(int fixedLength) const
{
    QString s = QString::number(d_func()->id);
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend( QString().fill('0', dlen) );
    return s;
}

QString TUserInfo::login() const
{
    return d_func()->login;
}

TUserInfo::AccessLevel TUserInfo::accessLevel() const
{
    return d_func()->accessLevel;
}

QString TUserInfo::accessLevelString() const
{
    return accessLevelToString(d_func()->accessLevel);
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

bool TUserInfo::isValid() const
{
    const B_D(TUserInfo);
    return d->id && !d->login.isEmpty() && d->creationDT.isValid() && d->modificationDT.isValid();
    return true;
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    d->id = dd->id;
    d->login = dd->login;
    d->accessLevel = dd->accessLevel;
    d->realName = dd->realName;
    d->avatar = dd->avatar;
    d->creationDT = dd->creationDT;
    d->modificationDT = dd->modificationDT;
    d->updateDT = dd->updateDT;
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    const B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    return d->id == dd->id;
}

TUserInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    stream << d->id;
    stream << d->login;
    stream << (int) d->accessLevel;
    stream << d->realName;
    stream << d->avatar;
    stream << d->creationDT;
    stream << d->modificationDT;
    stream << d->updateDT;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    static const QList<int> levels = bRangeD(TUserInfo::NoLevel, TUserInfo::AdminLevel);
    TUserInfoPrivate *d = info.d_func();
    stream >> d->id;
    stream >> d->login;
    int l = TUserInfo::NoLevel;
    stream >> l;
    d->accessLevel = levels.contains(l) ? static_cast<TUserInfo::AccessLevel>(l) : TUserInfo::NoLevel;
    stream >> d->realName;
    stream >> d->avatar;
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

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    dbg.nospace() << "TUserInfo(" << d->id << "," << d->login << "," << info.accessLevelString() << ","
                  << d->creationDT << "," << d->modificationDT << "," << d->updateDT << ")";
    return dbg.space();
}
