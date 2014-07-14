#include "tregisterrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRegisterRequestDataPrivate =================
============================================================================*/

class TRegisterRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRegisterRequestData)
public:
    QImage avatar;
    QString email;
    BUuid inviteCode;
    QString login;
    QString name;
    QByteArray password;
    QString patronymic;
    QString surename;
public:
    explicit TRegisterRequestDataPrivate(TRegisterRequestData *q);
    ~TRegisterRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRegisterRequestDataPrivate)
};


/*============================================================================
================================ TRegisterRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TRegisterRequestDataPrivate::TRegisterRequestDataPrivate(TRegisterRequestData *q) :
    BBasePrivate(q)
{
    //
}

TRegisterRequestDataPrivate::~TRegisterRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRegisterRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRegisterRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TRegisterRequestData::TRegisterRequestData() :
    BBase(*new TRegisterRequestDataPrivate(this))
{
    d_func()->init();
}

TRegisterRequestData::TRegisterRequestData(const TRegisterRequestData &other) :
    BBase(*new TRegisterRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRegisterRequestData::~TRegisterRequestData()
{
    //
}

/*============================== Public methods ============================*/

QImage TRegisterRequestData::avatar() const
{
    return d_func()->avatar;
}

void TRegisterRequestData::clear()
{
    B_D(TRegisterRequestData);
    d->avatar = QImage();
    d->email.clear();
    d->inviteCode = BUuid();
    d->login.clear();
    d->name.clear();
    d->password.clear();
    d->patronymic.clear();
    d->surename.clear();
}

QString TRegisterRequestData::email() const
{
    return d_func()->email;
}

QByteArray TRegisterRequestData::encryptedPassword() const
{
    return d_func()->password;
}

BUuid TRegisterRequestData::inviteCode() const
{
    return d_func()->inviteCode;
}

bool TRegisterRequestData::isValid() const
{
    const B_D(TRegisterRequestData);
    return !d->email.isEmpty() && !d->login.isEmpty() && !d->password.isEmpty() && !d->inviteCode.isNull();
}

QString TRegisterRequestData::login() const
{
    return d_func()->login;
}

QString TRegisterRequestData::name() const
{
    return d_func()->name;
}

QString TRegisterRequestData::patronymic() const
{
    return d_func()->patronymic;
}

void TRegisterRequestData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = Texsample::testAvatar(avatar) ? avatar : QImage();
}

void TRegisterRequestData::setEmail(const QString &email)
{
    d_func()->email = Texsample::testEmail(email) ? email : QString();
}

void TRegisterRequestData::setInviteCode(const QString &inviteCode)
{
    d_func()->inviteCode = BeQt::uuidFromText(inviteCode);
}

void TRegisterRequestData::setLogin(const QString &login)
{
    d_func()->login = Texsample::testLogin(login) ? login : QString();
}

void TRegisterRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TRegisterRequestData::setPassword(const QString &password)
{
    d_func()->password = Texsample::testPassword(password) ?
                QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1) : QByteArray();
}

void TRegisterRequestData::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testName(patronymic) ? patronymic : QString();
}

void TRegisterRequestData::setSurename(const QString &surename)
{
    d_func()->surename = Texsample::testName(surename) ? surename : QString();
}

QString TRegisterRequestData::surename() const
{
    return d_func()->surename;
}

/*============================== Public operators ==========================*/

TRegisterRequestData &TRegisterRequestData::operator =(const TRegisterRequestData &other)
{
    B_D(TRegisterRequestData);
    const TRegisterRequestDataPrivate *dd = other.d_func();
    d->avatar = dd->avatar;
    d->email = dd->email;
    d->inviteCode = dd->inviteCode;
    d->login = dd->login;
    d->name = dd->name;
    d->password = dd->password;
    d->patronymic = dd->patronymic;
    d->surename = dd->surename;
    return *this;
}

bool TRegisterRequestData::operator ==(const TRegisterRequestData &other) const
{
    const B_D(TRegisterRequestData);
    const TRegisterRequestDataPrivate *dd = other.d_func();
    return d->avatar == dd->avatar && d->email == dd->email && d->inviteCode == dd->inviteCode
            && d->login == dd->login && d->name == dd->name && d->password == dd->password
            && d->patronymic == dd->patronymic && d->surename == dd->surename;
}

bool TRegisterRequestData::operator !=(const TRegisterRequestData &other) const
{
    return !(*this == other);
}

TRegisterRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRegisterRequestData &data)
{
    const TRegisterRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("avatar", d->avatar);
    m.insert("email", d->email);
    m.insert("invite_code", QVariant::fromValue(d->inviteCode));
    m.insert("login", d->login);
    m.insert("name", d->name);
    m.insert("password", d->password);
    m.insert("patronymic", d->patronymic);
    m.insert("surename", d->surename);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRegisterRequestData &data)
{
    TRegisterRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->avatar = m.value("avatar").value<QImage>();
    d->email = m.value("email").toString();
    d->inviteCode = m.value("invite_code").value<BUuid>();
    d->login = m.value("login").toString();
    d->name = m.value("name").toString();
    d->password = m.value("password").toByteArray();
    d->patronymic = m.value("patronymic").toString();
    d->surename = m.value("surename").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRegisterRequestData &data)
{
    const TRegisterRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TRegisterRequestData(" << d->login << "," << ")";
    return dbg.space();
}
