#include "tgroupinfo.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGroupInfoPrivate ===========================
============================================================================*/

class TGroupInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGroupInfo)
public:
    QDateTime creationDateTime;
    quint64 id;
    QDateTime lastModificationDateTime;
    QString name;
    quint64 ownerId;
    QString ownerLogin;
public:
    explicit TGroupInfoPrivate(TGroupInfo *q);
    ~TGroupInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGroupInfoPrivate)
};

/*============================================================================
================================ TGroupInfoPrivate ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupInfoPrivate::TGroupInfoPrivate(TGroupInfo *q) :
    BBasePrivate(q)
{
    //
}

TGroupInfoPrivate::~TGroupInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGroupInfoPrivate::init()
{
    creationDateTime.setTimeSpec(Qt::UTC);
    id = 0;
    lastModificationDateTime.setTimeSpec(Qt::UTC);
    ownerId = 0;
}

/*============================================================================
================================ TGroupInfo ==================================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupInfo::TGroupInfo() :
    BBase(*new TGroupInfoPrivate(this))
{
    d_func()->init();
}

TGroupInfo::TGroupInfo(const TGroupInfo &other) :
    BBase(*new TGroupInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGroupInfo::~TGroupInfo()
{
    //
}

/*============================== Public methods ============================*/

void TGroupInfo::clear()
{
    B_D(TGroupInfo);
    d->creationDateTime = QDateTime().toUTC();
    d->id = 0;
    d->lastModificationDateTime = QDateTime().toUTC();
    d->name.clear();
    d->ownerId = 0;
    d->ownerLogin.clear();
}

QDateTime TGroupInfo::creationDateTime() const
{
    return d_func()->creationDateTime;
}

quint64 TGroupInfo::id() const
{
    return d_func()->id;
}

bool TGroupInfo::isValid() const
{
    const B_D(TGroupInfo);
    return d->id && d->creationDateTime.isValid() && d->ownerId && !d->ownerLogin.isEmpty();
}

QDateTime TGroupInfo::lastModificationDateTime() const
{
    return d_func()->lastModificationDateTime;
}

QString TGroupInfo::name() const
{
    return d_func()->name;
}

quint64 TGroupInfo::ownerId() const
{
    return d_func()->ownerId;
}

QString TGroupInfo::ownerLogin() const
{
    return d_func()->ownerLogin;
}

void TGroupInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDateTime = dt.toUTC();
}

void TGroupInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TGroupInfo::setLastModificationDateTime(const QDateTime &dt)
{
    d_func()->lastModificationDateTime = dt.toUTC();
}

void TGroupInfo::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TGroupInfo::setOwnerId(quint64 ownerId)
{
    d_func()->ownerId = ownerId;
}

void TGroupInfo::setOwnerLogin(const QString &login)
{
    d_func()->ownerLogin = Texsample::testLogin(login) ? login : QString();
}

/*============================== Public operators ==========================*/

TGroupInfo &TGroupInfo::operator =(const TGroupInfo &other)
{
    B_D(TGroupInfo);
    const TGroupInfoPrivate *dd = other.d_func();
    d->creationDateTime = dd->creationDateTime;
    d->id = dd->id;
    d->lastModificationDateTime = dd->lastModificationDateTime;
    d->name = dd->name;
    d->ownerId = dd->ownerId;
    d->ownerLogin = dd->ownerLogin;
    return *this;
}

bool TGroupInfo::operator ==(const TGroupInfo &other) const
{
    const B_D(TGroupInfo);
    const TGroupInfoPrivate *dd = other.d_func();
    return d->creationDateTime == dd->creationDateTime && d->id == dd->id
            && d->lastModificationDateTime == dd->lastModificationDateTime && d->name == dd->name
            && d->ownerId == dd->ownerId && d->ownerLogin == dd->ownerLogin;
}

bool TGroupInfo::operator !=(const TGroupInfo &other) const
{
    return !(*this == other);
}

TGroupInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGroupInfo &info)
{
    const TGroupInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("creation_date_time", d->creationDateTime);
    m.insert("id", d->id);
    m.insert("last_modification_date_time", d->lastModificationDateTime);
    m.insert("name", d->name);
    m.insert("owner_id", d->ownerId);
    m.insert("owner_login", d->ownerLogin);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGroupInfo &info)
{
    TGroupInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->creationDateTime = m.value("creation_date_time").toDateTime().toUTC();
    d->id = m.value("id").toULongLong();
    d->lastModificationDateTime = m.value("last_modification_date_time").toDateTime().toUTC();
    d->name = m.value("name").toString();
    d->ownerId = m.value("owner_id").toULongLong();
    d->ownerLogin = m.value("owner_login").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGroupInfo &info)
{
    const TGroupInfoPrivate *d = info.d_func();
    dbg.nospace() << "TGroupInfo(" << d->id << ")";
    return dbg.space();
}
