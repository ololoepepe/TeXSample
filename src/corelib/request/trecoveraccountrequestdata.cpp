#include "trecoveraccountrequestdata.h"

#include "tnamespace.h"

#include <BeQt>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRecoverAccountRequestDataPrivate ===========
============================================================================*/

class TRecoverAccountRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRecoverAccountRequestData)
public:
    QByteArray password;
    BUuid recoveryCode;
public:
    explicit TRecoverAccountRequestDataPrivate(TRecoverAccountRequestData *q);
    ~TRecoverAccountRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRecoverAccountRequestDataPrivate)
};


/*============================================================================
================================ TRecoverAccountRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TRecoverAccountRequestDataPrivate::TRecoverAccountRequestDataPrivate(TRecoverAccountRequestData *q) :
    BBasePrivate(q)
{
    //
}

TRecoverAccountRequestDataPrivate::~TRecoverAccountRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRecoverAccountRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRecoverAccountRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoverAccountRequestData::TRecoverAccountRequestData() :
    BBase(*new TRecoverAccountRequestDataPrivate(this))
{
    d_func()->init();
}

TRecoverAccountRequestData::TRecoverAccountRequestData(const TRecoverAccountRequestData &other) :
    BBase(*new TRecoverAccountRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRecoverAccountRequestData::~TRecoverAccountRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TRecoverAccountRequestData::clear()
{
    d_func()->password.clear();
    d_func()->recoveryCode = BUuid();
}

bool TRecoverAccountRequestData::isValid() const
{
    return !d_func()->password.isEmpty() && !d_func()->recoveryCode.isNull();
}

QByteArray TRecoverAccountRequestData::password() const
{
    return d_func()->password;
}

BUuid TRecoverAccountRequestData::recoveryCode() const
{
    return d_func()->recoveryCode;
}

void TRecoverAccountRequestData::setPassword(const QString &password)
{
    d_func()->password = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

void TRecoverAccountRequestData::setRecoveryCode(const QString &code)
{
    d_func()->recoveryCode = BeQt::uuidFromText(code);
}

/*============================== Public operators ==========================*/

TRecoverAccountRequestData &TRecoverAccountRequestData::operator =(const TRecoverAccountRequestData &other)
{
    B_D(TRecoverAccountRequestData);
    const TRecoverAccountRequestDataPrivate *dd = other.d_func();
    d->password = dd->password;
    d->recoveryCode = dd->recoveryCode;
    return *this;
}

bool TRecoverAccountRequestData::operator ==(const TRecoverAccountRequestData &other) const
{
    const B_D(TRecoverAccountRequestData);
    const TRecoverAccountRequestDataPrivate *dd = other.d_func();
    return d->password == dd->password && d->recoveryCode == dd->recoveryCode;
}

bool TRecoverAccountRequestData::operator !=(const TRecoverAccountRequestData &other) const
{
    return !(*this == other);
}

TRecoverAccountRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRecoverAccountRequestData &data)
{
    const TRecoverAccountRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("password", d->password);
    m.insert("recovery_code", QVariant::fromValue(d->recoveryCode));
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRecoverAccountRequestData &data)
{
    TRecoverAccountRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->password = m.value("password").toByteArray();
    d->recoveryCode = m.value("recovery_code").value<BUuid>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRecoverAccountRequestData &/*data*/)
{
    //const TRecoverAccountRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TRecoverAccountRequestData(" << ")";
    return dbg.space();
}
