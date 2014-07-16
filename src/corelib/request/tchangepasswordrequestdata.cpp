#include "tchangepasswordrequestdata.h"

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
================================ TChangePasswordRequestDataPrivate ===========
============================================================================*/

class TChangePasswordRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TChangePasswordRequestData)
public:
    QByteArray newPassword;
    QByteArray oldPassword;
public:
    explicit TChangePasswordRequestDataPrivate(TChangePasswordRequestData *q);
    ~TChangePasswordRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TChangePasswordRequestDataPrivate)
};

/*============================================================================
================================ TChangePasswordRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TChangePasswordRequestDataPrivate::TChangePasswordRequestDataPrivate(TChangePasswordRequestData *q) :
    BBasePrivate(q)
{
    //
}

TChangePasswordRequestDataPrivate::~TChangePasswordRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TChangePasswordRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TChangePasswordRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TChangePasswordRequestData::TChangePasswordRequestData() :
    BBase(*new TChangePasswordRequestDataPrivate(this))
{
    d_func()->init();
}

TChangePasswordRequestData::TChangePasswordRequestData(const TChangePasswordRequestData &other) :
    BBase(*new TChangePasswordRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TChangePasswordRequestData::~TChangePasswordRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TChangePasswordRequestData::clear()
{
    d_func()->newPassword.clear();
    d_func()->oldPassword.clear();
}

bool TChangePasswordRequestData::isValid() const
{
    return !d_func()->newPassword.isEmpty() && !d_func()->oldPassword.isEmpty();
}

QByteArray TChangePasswordRequestData::newPassword() const
{
    return d_func()->newPassword;
}

QByteArray TChangePasswordRequestData::oldPassword() const
{
    return d_func()->oldPassword;
}

void TChangePasswordRequestData::setNewPassword(const QString &password)
{
    d_func()->newPassword = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

void TChangePasswordRequestData::setOldPassword(const QString &password)
{
    d_func()->oldPassword = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

/*============================== Public operators ==========================*/

TChangePasswordRequestData &TChangePasswordRequestData::operator =(const TChangePasswordRequestData &other)
{
    B_D(TChangePasswordRequestData);
    const TChangePasswordRequestDataPrivate *dd = other.d_func();
    d->newPassword = dd->newPassword;
    d->oldPassword = dd->oldPassword;
    return *this;
}

bool TChangePasswordRequestData::operator ==(const TChangePasswordRequestData &other) const
{
    const B_D(TChangePasswordRequestData);
    const TChangePasswordRequestDataPrivate *dd = other.d_func();
    return d->newPassword == dd->newPassword && d->oldPassword == dd->oldPassword;
}

bool TChangePasswordRequestData::operator !=(const TChangePasswordRequestData &other) const
{
    return !(*this == other);
}

TChangePasswordRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TChangePasswordRequestData &data)
{
    const TChangePasswordRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("new_password", d->newPassword);
    m.insert("old_password", d->oldPassword);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TChangePasswordRequestData &data)
{
    TChangePasswordRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->newPassword = m.value("new_password").toByteArray();
    d->oldPassword = m.value("old_password").toByteArray();
    return stream;
}

QDebug operator <<(QDebug dbg, const TChangePasswordRequestData &/*data*/)
{
    //const TChangePasswordRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TChangePasswordRequestData(" << ")";
    return dbg.space();
}
