#include "tcheckloginavailabilityrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCheckLoginAvailabilityRequestDataPrivate ===
============================================================================*/

class TCheckLoginAvailabilityRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCheckLoginAvailabilityRequestData)
public:
    QString login;
public:
    explicit TCheckLoginAvailabilityRequestDataPrivate(TCheckLoginAvailabilityRequestData *q);
    ~TCheckLoginAvailabilityRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCheckLoginAvailabilityRequestDataPrivate)
};


/*============================================================================
================================ TCheckLoginAvailabilityRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TCheckLoginAvailabilityRequestDataPrivate::TCheckLoginAvailabilityRequestDataPrivate(
        TCheckLoginAvailabilityRequestData *q) :
    BBasePrivate(q)
{
    //
}

TCheckLoginAvailabilityRequestDataPrivate::~TCheckLoginAvailabilityRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCheckLoginAvailabilityRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TCheckLoginAvailabilityRequestData ==========
============================================================================*/

/*============================== Public constructors =======================*/

TCheckLoginAvailabilityRequestData::TCheckLoginAvailabilityRequestData() :
    BBase(*new TCheckLoginAvailabilityRequestDataPrivate(this))
{
    d_func()->init();
}

TCheckLoginAvailabilityRequestData::TCheckLoginAvailabilityRequestData(
        const TCheckLoginAvailabilityRequestData &other) :
    BBase(*new TCheckLoginAvailabilityRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCheckLoginAvailabilityRequestData::~TCheckLoginAvailabilityRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TCheckLoginAvailabilityRequestData::clear()
{
    d_func()->login.clear();
}

bool TCheckLoginAvailabilityRequestData::isValid() const
{
    return !d_func()->login.isEmpty();
}

QString TCheckLoginAvailabilityRequestData::login() const
{
    return d_func()->login;
}

void TCheckLoginAvailabilityRequestData::setLogin(const QString &login)
{
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

/*============================== Public operators ==========================*/

TCheckLoginAvailabilityRequestData &TCheckLoginAvailabilityRequestData::operator =(
        const TCheckLoginAvailabilityRequestData &other)
{
    B_D(TCheckLoginAvailabilityRequestData);
    const TCheckLoginAvailabilityRequestDataPrivate *dd = other.d_func();
    d->login = dd->login;
    return *this;
}

bool TCheckLoginAvailabilityRequestData::operator ==(const TCheckLoginAvailabilityRequestData &other) const
{
    const B_D(TCheckLoginAvailabilityRequestData);
    const TCheckLoginAvailabilityRequestDataPrivate *dd = other.d_func();
    return d->login == dd->login;
}

bool TCheckLoginAvailabilityRequestData::operator !=(const TCheckLoginAvailabilityRequestData &other) const
{
    return !(*this == other);
}

TCheckLoginAvailabilityRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCheckLoginAvailabilityRequestData &data)
{
    const TCheckLoginAvailabilityRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("login", d->login);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCheckLoginAvailabilityRequestData &data)
{
    TCheckLoginAvailabilityRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->login = m.value("login").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCheckLoginAvailabilityRequestData &/*data*/)
{
    //const TCheckLoginAvailabilityRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TCheckLoginAvailabilityRequestData(" << ")";
    return dbg.space();
}
