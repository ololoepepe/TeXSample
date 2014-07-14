#include "tinviteinfo.h"

#include "tidlist.h"
#include "tnamespace.h"
#include "tservicelist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TInviteInfoPrivate ==========================
============================================================================*/

class TInviteInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TInviteInfo)
public:
    BUuid code;
    QDateTime creationDT;
    QDateTime expirationDT;
    TIdList groups;
    quint64 id;
    quint64 ownerId;
    QString ownerLogin;
    TServiceList services;
public:
   explicit TInviteInfoPrivate(TInviteInfo *q);
    ~TInviteInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TInviteInfoPrivate)
};

/*============================================================================
================================ TInviteInfoPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteInfoPrivate::TInviteInfoPrivate(TInviteInfo *q) :
    BBasePrivate(q)
{
    //
}

TInviteInfoPrivate::~TInviteInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TInviteInfoPrivate::init()
{
    creationDT.setTimeSpec(Qt::UTC);
    expirationDT.setTimeSpec(Qt::UTC);
    id = 0;
    ownerId = 0;
}

/*============================================================================
================================ TInviteInfo =================================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteInfo::TInviteInfo() :
    BBase(*new TInviteInfoPrivate(this))
{
    d_func()->init();
}

TInviteInfo::TInviteInfo(const TInviteInfo &other) :
    BBase(*new TInviteInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TInviteInfo::~TInviteInfo()
{
    //
}

/*============================== Public methods ============================*/

void TInviteInfo::clear()
{
    B_D(TInviteInfo);
    d->code = BUuid();
    d->creationDT = QDateTime().toUTC();
    d->expirationDT = QDateTime().toUTC();
    d->groups.clear();
    d->id = 0;
    d->ownerId = 0;
    d->ownerLogin.clear();
    d->services.clear();
}

BUuid TInviteInfo::code() const
{
    return d_func()->code;
}

QDateTime TInviteInfo::creationDateTime() const
{
    return d_func()->creationDT;
}

QDateTime TInviteInfo::expirationDateTime() const
{
    return d_func()->expirationDT;
}

TIdList TInviteInfo::groups() const
{
    return d_func()->groups;
}

quint64 TInviteInfo::id() const
{
    return d_func()->id;
}

bool TInviteInfo::isValid() const
{
    const B_D(TInviteInfo);
    return !d->code.isNull() && d->creationDT.isValid() && d->expirationDT.isValid() && d->id && d->ownerId
            && !d->ownerLogin.isEmpty();
}

quint64 TInviteInfo::ownerId() const
{
    return d_func()->ownerId;
}

QString TInviteInfo::ownerLogin() const
{
    return d_func()->ownerLogin;
}

TServiceList TInviteInfo::services() const
{
    return d_func()->services;
}

void TInviteInfo::setCode(const BUuid &code)
{
    d_func()->code = code;
}

void TInviteInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
}

void TInviteInfo::setExpirationDateTime(const QDateTime &dt)
{
    d_func()->expirationDT = dt.toUTC();
}

void TInviteInfo::setGroups(const TIdList &groups)
{
    B_D(TInviteInfo);
    d->groups = groups;
    d->groups.removeAll(0);
    bRemoveDuplicates(d->groups);
}

void TInviteInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TInviteInfo::setOwnerId(quint64 id)
{
    d_func()->ownerId = id;
}

void TInviteInfo::setOwnerLogin(const QString &login)
{
    d_func()->ownerLogin = Texsample::testLogin(login) ? login : QString();
}

void TInviteInfo::setServices(const TServiceList &services)
{
    B_D(TInviteInfo);
    d->services = services;
    bRemoveDuplicates(d->services);
}

/*============================== Public operators ==========================*/

TInviteInfo &TInviteInfo::operator =(const TInviteInfo &other)
{
    B_D(TInviteInfo);
    const TInviteInfoPrivate *dd = other.d_func();
    d->code = dd->code;
    d->creationDT = dd->creationDT;
    d->expirationDT = dd->expirationDT;
    d->groups = dd->groups;
    d->id = dd->id;
    d->ownerId = dd->ownerId;
    d->ownerLogin = dd->ownerLogin;
    d->services = dd->services;
    return *this;
}

bool TInviteInfo::operator ==(const TInviteInfo &other) const
{
    const B_D(TInviteInfo);
    const TInviteInfoPrivate *dd = other.d_func();
    return d->code == dd->code && d->creationDT == dd->creationDT && d->expirationDT == dd->expirationDT
            && d->groups == dd->groups && d->id == dd->id && d->ownerId == dd->ownerId
            && d->ownerLogin == dd->ownerLogin && d->services == dd->services;
}

TInviteInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TInviteInfo &info)
{
    const TInviteInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("code", QVariant::fromValue(d->code));
    m.insert("creation_date_time", d->creationDT);
    m.insert("expiration_date_time", d->expirationDT);
    m.insert("grouops", d->groups);
    m.insert("id", d->id);
    m.insert("owner_id", d->ownerId);
    m.insert("owner_login", d->ownerLogin);
    m.insert("services", d->services);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TInviteInfo &info)
{
    TInviteInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->code = m.value("code").value<BUuid>();
    d->creationDT = m.value("creation_date_time").toDateTime().toUTC();
    d->expirationDT = m.value("expiration_date_time").toDateTime().toUTC();
    d->groups = m.value("groups").value<TIdList>();
    d->id = m.value("id").toULongLong();
    d->ownerId = m.value("owner_id").toULongLong();
    d->ownerLogin = m.value("owner_login").toString();
    d->services = m.value("services").value<TServiceList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TInviteInfo &info)
{
    const TInviteInfoPrivate *d = info.d_func();
    dbg.nospace() << "TInviteInfo(" << d->id << ")";
    return dbg.space();
}
