#include "tuseridentifier.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TUserIdentifierPrivate ======================
============================================================================*/

class TUserIdentifierPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserIdentifier)
public:
    explicit TUserIdentifierPrivate(TUserIdentifier *q);
    ~TUserIdentifierPrivate();
public:
    void init();
public:
    quint64 id;
    QString login;
private:
    Q_DISABLE_COPY(TUserIdentifierPrivate)
};


/*============================================================================
================================ TUserIdentifierPrivate ======================
============================================================================*/

/*============================== Public constructors =======================*/

TUserIdentifierPrivate::TUserIdentifierPrivate(TUserIdentifier *q) :
    BBasePrivate(q)
{
    //
}

TUserIdentifierPrivate::~TUserIdentifierPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserIdentifierPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TUserIdentifier =============================
============================================================================*/

/*============================== Public constructors =======================*/

TUserIdentifier::TUserIdentifier() :
    BBase(*new TUserIdentifierPrivate(this))
{
    d_func()->init();
}

TUserIdentifier::TUserIdentifier(quint64 id) :
    BBase(*new TUserIdentifierPrivate(this))
{
    d_func()->init();
    d_func()->id = id;
}

TUserIdentifier::TUserIdentifier(const QString &login) :
    BBase(*new TUserIdentifierPrivate(this))
{
    d_func()->init();
    d_func()->login = login;
}

TUserIdentifier::TUserIdentifier(const TUserIdentifier &other) :
    BBase(*new TUserIdentifierPrivate(this))
{
    d_func()->init();
    *this = other;
}

TUserIdentifier::~TUserIdentifier()
{
    //
}

/*============================== Public methods ============================*/

void TUserIdentifier::clear()
{
    d_func()->id = 0;
    d_func()->login.clear();
}

quint64 TUserIdentifier::id() const
{
    return d_func()->id;
}

bool TUserIdentifier::isValid() const
{
    return type();
}

QString TUserIdentifier::login() const
{
    return d_func()->login;
}

void TUserIdentifier::setId(quint64 id)
{
    d_func()->login.clear();
    d_func()->id = id;
}

void TUserIdentifier::setLogin(const QString &login)
{
    d_func()->id = 0;
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

TUserIdentifier::Type TUserIdentifier::type() const
{
    if (d_func()->id)
        return IdType;
    else if (!d_func()->login.isEmpty())
        return LoginType;
    else
        return NoType;
}

/*============================== Public operators ==========================*/

TUserIdentifier &TUserIdentifier::operator =(const TUserIdentifier &other)
{
    B_D(TUserIdentifier);
    const TUserIdentifierPrivate *dd = other.d_func();
    d->id = dd->id;
    d->login = dd->login;
    return *this;
}

bool TUserIdentifier::operator ==(const TUserIdentifier &other) const
{
    const B_D(TUserIdentifier);
    const TUserIdentifierPrivate *dd = other.d_func();
    return d->id == dd->id && d->login == dd->login;
}

bool TUserIdentifier::operator !=(const TUserIdentifier &other) const
{
    return !(*this == other);
}

TUserIdentifier::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TUserIdentifier::operator quint64() const
{
    return d_func()->id;
}

TUserIdentifier::operator QString() const
{
    return d_func()->login;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserIdentifier &identificator)
{
    const TUserIdentifierPrivate *d = identificator.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    m.insert("login", d->login);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserIdentifier &identificator)
{
    TUserIdentifierPrivate *d = identificator.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    d->login = m.value("login").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserIdentifier &identificator)
{
    const TUserIdentifierPrivate *d = identificator.d_func();
    dbg.nospace() << "TUserIdentifier(" << d->id << "," << d->login << ")";
    return dbg.space();
}

