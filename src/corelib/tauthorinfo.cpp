#include "tauthorinfo.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAuthorInfoPrivate ==========================
============================================================================*/

class TAuthorInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAuthorInfo)
public:
    QString name;
    QString organization;
    QString patronymic;
    QString post;
    QString role;
    QString surename;
public:
    explicit TAuthorInfoPrivate(TAuthorInfo *q);
    ~TAuthorInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAuthorInfoPrivate)
};

/*============================================================================
================================ TAuthorInfoPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfoPrivate::TAuthorInfoPrivate(TAuthorInfo *q) :
    BBasePrivate(q)
{
    //
}

TAuthorInfoPrivate::~TAuthorInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorInfoPrivate::init()
{
    //
}

/*============================================================================
================================ TAuthorInfo =================================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfo::TAuthorInfo() :
    BBase(*new TAuthorInfoPrivate(this))
{
    d_func()->init();
}

TAuthorInfo::TAuthorInfo(const TAuthorInfo &other) :
    BBase(*new TAuthorInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAuthorInfo::~TAuthorInfo()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorInfo::clear()
{
    B_D(TAuthorInfo);
    d->name.clear();
    d->organization.clear();
    d->patronymic.clear();
    d->post.clear();
    d->role.clear();
    d->surename.clear();
}

bool TAuthorInfo::isValid() const
{
    const B_D(TAuthorInfo);
    return !d->name.isEmpty();
}

QString TAuthorInfo::name() const
{
    return d_func()->name;
}

QString TAuthorInfo::organization() const
{
    return d_func()->organization;
}

QString TAuthorInfo::patronymic() const
{
    return d_func()->patronymic;
}

QString TAuthorInfo::post() const
{
    return d_func()->post;
}

QString TAuthorInfo::role() const
{
    return d_func()->role;
}

void TAuthorInfo::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TAuthorInfo::setOrganization(const QString &organization)
{
    d_func()->organization = Texsample::testOrganization(organization) ? organization : QString();
}

void TAuthorInfo::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testName(patronymic) ? patronymic : QString();
}

void TAuthorInfo::setPost(const QString &post)
{
    d_func()->post = Texsample::testPost(post) ? post : QString();
}

void TAuthorInfo::setRole(const QString &role)
{
    d_func()->role = Texsample::testRole(role) ? role : QString();
}

void TAuthorInfo::setSurename(const QString &surename)
{
    d_func()->surename = Texsample::testName(surename) ? surename : QString();
}

QString TAuthorInfo::surename() const
{
    return d_func()->surename;
}

/*============================== Public operators ==========================*/

TAuthorInfo &TAuthorInfo::operator =(const TAuthorInfo &other)
{
    B_D(TAuthorInfo);
    const TAuthorInfoPrivate *dd = other.d_func();
    d->name = dd->name;
    d->organization = dd->organization;
    d->patronymic = dd->patronymic;
    d->post = dd->post;
    d->role = dd->role;
    d->surename = dd->surename;
    return *this;
}

bool TAuthorInfo::operator ==(const TAuthorInfo &other) const
{
    const B_D(TAuthorInfo);
    const TAuthorInfoPrivate *dd = other.d_func();
    return d->name == dd->name && d->organization == dd->organization && d->patronymic == dd->patronymic
            && d->post == dd->post && d->role == dd->role && d->surename == dd->surename;
}

bool TAuthorInfo::operator !=(const TAuthorInfo &other) const
{
    return !(*this == other);
}

TAuthorInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAuthorInfo &data)
{
    const TAuthorInfoPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("name", d->name);
    m.insert("organization", d->organization);
    m.insert("patronymic", d->patronymic);
    m.insert("post", d->post);
    m.insert("role", d->role);
    m.insert("surename", d->surename);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAuthorInfo &data)
{
    TAuthorInfoPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->name = m.value("name").toString();
    d->organization = m.value("organization").toString();
    d->patronymic = m.value("patronymic").toString();
    d->post = m.value("post").toString();
    d->role = m.value("role").toString();
    d->surename = m.value("surename").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAuthorInfo &/*data*/)
{
    //const TAuthorInfoPrivate *d = data.d_func();
    dbg.nospace() << "TAuthorInfo(" << ")";
    return dbg.space();
}
