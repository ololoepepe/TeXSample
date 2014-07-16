#include "tchangeemailrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TChangeEmailRequestDataPrivate ==============
============================================================================*/

class TChangeEmailRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TChangeEmailRequestData)
public:
    QString email;
    QByteArray password;
public:
    explicit TChangeEmailRequestDataPrivate(TChangeEmailRequestData *q);
    ~TChangeEmailRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TChangeEmailRequestDataPrivate)
};

/*============================================================================
================================ TChangeEmailRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TChangeEmailRequestDataPrivate::TChangeEmailRequestDataPrivate(TChangeEmailRequestData *q) :
    BBasePrivate(q)
{
    //
}

TChangeEmailRequestDataPrivate::~TChangeEmailRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TChangeEmailRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TChangeEmailRequestData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TChangeEmailRequestData::TChangeEmailRequestData() :
    BBase(*new TChangeEmailRequestDataPrivate(this))
{
    d_func()->init();
}

TChangeEmailRequestData::TChangeEmailRequestData(const TChangeEmailRequestData &other) :
    BBase(*new TChangeEmailRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TChangeEmailRequestData::~TChangeEmailRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TChangeEmailRequestData::clear()
{
    B_D(TChangeEmailRequestData);
    d->email.clear();
    d->password.clear();
}

QString TChangeEmailRequestData::email() const
{
    return d_func()->email;
}

bool TChangeEmailRequestData::isValid() const
{
    return !d_func()->email.isEmpty() && !d_func()->password.isEmpty();
}

QByteArray TChangeEmailRequestData::password() const
{
    return d_func()->password;
}

void TChangeEmailRequestData::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

void TChangeEmailRequestData::setPassword(const QString &password)
{
    d_func()->password = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

/*============================== Public operators ==========================*/

TChangeEmailRequestData &TChangeEmailRequestData::operator =(const TChangeEmailRequestData &other)
{
    B_D(TChangeEmailRequestData);
    const TChangeEmailRequestDataPrivate *dd = other.d_func();
    d->email = dd->email;
    d->password = dd->password;
    return *this;
}

bool TChangeEmailRequestData::operator ==(const TChangeEmailRequestData &other) const
{
    const B_D(TChangeEmailRequestData);
    const TChangeEmailRequestDataPrivate *dd = other.d_func();
    return d->email == dd->email && d->password == dd->password;
}

bool TChangeEmailRequestData::operator !=(const TChangeEmailRequestData &other) const
{
    return !(*this == other);
}

TChangeEmailRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TChangeEmailRequestData &data)
{
    const TChangeEmailRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("email", d->email);
    m.insert("password", d->password);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TChangeEmailRequestData &data)
{
    TChangeEmailRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->email = m.value("email").toString();
    d->password = m.value("password").toByteArray();
    return stream;
}

QDebug operator <<(QDebug dbg, const TChangeEmailRequestData &/*data*/)
{
    //const TChangeEmailRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TChangeEmailRequestData(" << ")";
    return dbg.space();
}
