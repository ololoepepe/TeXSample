#include "tuserinfo.h"
#include "tglobal.h"
#include "taccesslevel.h"
#include "tservice.h"
#include "tservicelist.h"
#include "tnamespace.h"
#include "cimg/CImg.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTranslator>
#include <BeQt>
#include <BTextTools>
#include <BDirTools>

#include <QObject>
#include <QDataStream>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QCryptographicHash>
#include <QVariantMap>
#include <QList>
#include <QUuid>
#include <QRegExp>
#include <QFileInfo>
#include <QTemporaryFile>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_DECLARE_METATYPE(QUuid)
#endif

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

class TUserInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserInfo)
public:
    static TUserInfo::Context contextFromInt(int c);
public:
    static const QList<TUserInfo::Context> IdContexts;
    static const QList<TUserInfo::Context> InviteCodeContexts;
    static const QList<TUserInfo::Context> EmailContexts;
    static const QList<TUserInfo::Context> LoginContexts;
    static const QList<TUserInfo::Context> PasswordContexts;
    static const QList<TUserInfo::Context> AccessLevelContexts;
    static const QList<TUserInfo::Context> ServicesContexts;
    static const QList<TUserInfo::Context> RealNameContexts;
    static const QList<TUserInfo::Context> AvatarContexts;
    static const QList<TUserInfo::Context> CreationDTContexts;
    static const QList<TUserInfo::Context> UpdateDTContexts;
public:
    explicit TUserInfoPrivate(TUserInfo *q);
    ~TUserInfoPrivate();
public:
    void init();
public:
    TUserInfo::Context context;
    quint64 id;
    QUuid inviteCode;
    QString email;
    QString login;
    QByteArray password;
    TAccessLevel accessLevel;
    TServiceList services;
    QString realName;
    QByteArray avatar;
    QDateTime creationDT;
    QDateTime updateDT;
private:
    Q_DISABLE_COPY(TUserInfoPrivate)
};

/*============================================================================
================================ TUserInfoPrivate ============================
============================================================================*/

/*============================== Static public methods =====================*/

TUserInfo::Context TUserInfoPrivate::contextFromInt(int c)
{
    static const QList<int> contexts = bRangeD(TUserInfo::GeneralContext, TUserInfo::UpdateContext);
    return contexts.contains(c) ? static_cast<TUserInfo::Context>(c) : TUserInfo::GeneralContext;
}

/*============================== Static public constants ===================*/

const QList<TUserInfo::Context> TUserInfoPrivate::IdContexts =
    QList<TUserInfo::Context>() << TUserInfo::BriefInfoContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::EmailContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext;
const QList<TUserInfo::Context> TUserInfoPrivate::InviteCodeContexts =
    QList<TUserInfo::Context>() << TUserInfo::RegisterContext;
const QList<TUserInfo::Context> TUserInfoPrivate::LoginContexts =
    QList<TUserInfo::Context>() << TUserInfo::BriefInfoContext << TUserInfo::AddContext
    << TUserInfo::RegisterContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::PasswordContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::AccessLevelContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::EditContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::ServicesContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::EditContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::RealNameContexts =
    QList<TUserInfo::Context>() << TUserInfo::BriefInfoContext << TUserInfo::AddContext << TUserInfo::RegisterContext
    << TUserInfo::EditContext << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::AvatarContexts =
    QList<TUserInfo::Context>() << TUserInfo::AddContext << TUserInfo::RegisterContext << TUserInfo::EditContext
    << TUserInfo::UpdateContext << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::CreationDTContexts =
    QList<TUserInfo::Context>() << TUserInfo::GeneralContext;
const QList<TUserInfo::Context> TUserInfoPrivate::UpdateDTContexts =
    QList<TUserInfo::Context>() << TUserInfo::GeneralContext;

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
    context = TUserInfo::GeneralContext;
    id = 0;
    creationDT.setTimeSpec(Qt::UTC);
    updateDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

/*============================== Static public methods =====================*/

bool TUserInfo::testAvatar(const QByteArray &data)
{
    if (data.isEmpty() || (int) data.size() > Texsample::MaximumAvatarSize)
        return false;
    QString path = QDir::tempPath() + "/texsample/userinfo/" + BeQt::pureUuidText(QUuid::createUuid());
    if (!BDirTools::mkpath(path))
        return false;
    QTemporaryFile f(path + "/XXXXXX");
    bool b = f.open() && f.write(data) == data.size() && testAvatar(f.fileName());
    BDirTools::rmdir(path);
    f.remove();
    return b;
}

bool TUserInfo::testAvatar(const QString &fileName)
{
    if (fileName.isEmpty())
        return false;
    QFileInfo fi(fileName);
    if (!fi.isFile() || (int) fi.size() > Texsample::MaximumAvatarSize)
        return false;
    cimg_library::CImg<unsigned char> cimg(fileName.toLocal8Bit().constData());
    return (cimg.height() <= Texsample::MaximumAvatarExtent && cimg.width() <= Texsample::MaximumAvatarExtent);
}

/*============================== Public constructors =======================*/

TUserInfo::TUserInfo(Context c) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
}

TUserInfo::TUserInfo(quint64 id, Context c) :
    BBase(*new TUserInfoPrivate(this))
{
    d_func()->init();
    setContext(c);
    setId(id);
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

void TUserInfo::setContext(int c, bool clear)
{
    B_D(TUserInfo);
    Context cc = TUserInfoPrivate::contextFromInt(c);
    if (cc == d->context)
        return;
    d->context = cc;
    if (!clear)
        return;
    if (!TUserInfoPrivate::IdContexts.contains(d->context))
        d->id = 0;
    if (!TUserInfoPrivate::InviteCodeContexts.contains(d->context))
        d->inviteCode = QUuid();
    if (!TUserInfoPrivate::EmailContexts.contains(d->context))
        d->email.clear();
    if (!TUserInfoPrivate::LoginContexts.contains(d->context))
        d->login.clear();
    if (!TUserInfoPrivate::PasswordContexts.contains(d->context))
        d->password.clear();
    if (!TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        d->accessLevel = TAccessLevel();
    if (!TUserInfoPrivate::ServicesContexts.contains(d->context))
        d->services.clear();
    if (!TUserInfoPrivate::RealNameContexts.contains(d->context))
        d->realName.clear();
    if (!TUserInfoPrivate::AvatarContexts.contains(d->context))
        d->avatar.clear();
    if (!TUserInfoPrivate::CreationDTContexts.contains(d->context))
        d->creationDT = QDateTime().toUTC();
    if (!TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        d->updateDT = QDateTime().toUTC();
}

void TUserInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TUserInfo::setInviteCode(const QString &code)
{
    d_func()->inviteCode = BeQt::uuidFromText(code);
}

void TUserInfo::setEmail(const QString &email)
{
    d_func()->email = BTextTools::standardRegExp(BTextTools::EmailPattern).exactMatch(email) ? email : QString();
}

void TUserInfo::setLogin(const QString &login)
{
    d_func()->login = (login.length() <= 20) ? login : QString();
}

void TUserInfo::setPassword(const QString &s)
{
    setPassword(!s.isEmpty() ? QCryptographicHash::hash(s.toUtf8(), QCryptographicHash::Sha1) : QByteArray());
}

void TUserInfo::setPassword(const QByteArray &data)
{
    d_func()->password = data;
}

void TUserInfo::setAccessLevel(const TAccessLevel &lvl)
{
    d_func()->accessLevel = lvl;
}

void TUserInfo::setServices(const TServiceList &list)
{
    d_func()->services = list;
    bRemoveDuplicates(d_func()->services);
}

void TUserInfo::setServices(const QList<int> &list)
{
    d_func()->services = TServiceList::serviceListFromIntList(list);
}

void TUserInfo::setRealName(const QString &name)
{
    d_func()->realName = (name.length() <= 50) ? name : QString();
}

void TUserInfo::setAvatar(const QByteArray &data)
{
    if (!testAvatar(data))
        return d_func()->avatar.clear();
    d_func()->avatar = data;
}

void TUserInfo::setAvatar(const QString &fileName)
{
    if (!testAvatar(fileName))
        return d_func()->avatar.clear();
    d_func()->avatar = BDirTools::readFile(fileName);
}

void TUserInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
}

void TUserInfo::setUpdateDateTime(const QDateTime &dt)
{
    d_func()->updateDT = dt.toUTC();
}

void TUserInfo::clear()
{
    B_D(TUserInfo);
    d->id = 0;
    d->inviteCode = QUuid();
    d->email.clear();
    d->login.clear();
    d->password.clear();
    d->accessLevel = TAccessLevel();
    d->services.clear();
    d->realName.clear();
    d->avatar.clear();
    d->creationDT = QDateTime().toUTC();
    d->updateDT = QDateTime().toUTC();
}

TUserInfo::Context TUserInfo::context() const
{
    return d_func()->context;
}

quint64 TUserInfo::id() const
{
    return d_func()->id;
}

QString TUserInfo::idString(int fixedLength) const
{
    QString s = QString::number(id());
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend(QString().fill('0', dlen));
    return s;
}

QString TUserInfo::inviteCode() const
{
    return BeQt::pureUuidText(d_func()->inviteCode);
}

QString TUserInfo::email() const
{
    return d_func()->email;
}

QString TUserInfo::login() const
{
    return d_func()->login;
}

QByteArray TUserInfo::password() const
{
    return d_func()->password;
}

TAccessLevel TUserInfo::accessLevel() const
{
    return d_func()->accessLevel;
}

QString TUserInfo::accessLevelString() const
{
    return d_func()->accessLevel.toString();
}

QString TUserInfo::accessLevelStringNoTr() const
{
    return d_func()->accessLevel.toStringNoTr();
}

TServiceList TUserInfo::services() const
{
    return d_func()->services;
}

bool TUserInfo::hasAccessToService(TService s) const
{
    return d_func()->services.contains(s);
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

QDateTime TUserInfo::updateDateTime(Qt::TimeSpec spec) const
{
    return d_func()->updateDT.toTimeSpec(spec);
}

bool TUserInfo::isValid(Context c) const
{
    const B_D(TUserInfo);
    switch ((CurrentContext == c) ? d->context : c)
    {
    case BriefInfoContext:
        return d->id && !d->login.isEmpty();
    case AddContext:
        return !d->email.isEmpty() && !d->login.isEmpty() && !d->password.isEmpty();
    case RegisterContext:
        return !d->inviteCode.isNull() && !d->email.isEmpty() && !d->login.isEmpty() && !d->password.isEmpty();
    case EditContext:
        return d->id || !d->login.isEmpty();
    case UpdateContext:
        return d->id && !d->password.isEmpty();
    case GeneralContext:
    default:
        return d->id && !d->login.isEmpty() && d->creationDT.isValid() && d->updateDT.isValid();
    }
}

TUserInfo TUserInfo::toContext(int c) const
{
    Context cc = TUserInfoPrivate::contextFromInt(c);
    if (cc == d_func()->context)
        return *this;
    TUserInfo i = *this;
    i.setContext(c);
    return i;
}

/*============================== Public operators ==========================*/

TUserInfo &TUserInfo::operator =(const TUserInfo &other)
{
    B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    d->context = dd->context;
    d->id = dd->id;
    d->inviteCode = dd->inviteCode;
    d->email = dd->email;
    d->login = dd->login;
    d->password = dd->password;
    d->accessLevel = dd->accessLevel;
    d->services = dd->services;
    d->realName = dd->realName;
    d->avatar = dd->avatar;
    d->creationDT = dd->creationDT;
    d->updateDT = dd->updateDT;
    return *this;
}

bool TUserInfo::operator ==(const TUserInfo &other) const
{
    const B_D(TUserInfo);
    const TUserInfoPrivate *dd = other.d_func();
    if (context() != other.context())
        return false;
    bool b = true;
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        b = b && d->id == dd->id;
    if (TUserInfoPrivate::InviteCodeContexts.contains(d->context))
        b = b && d->inviteCode == dd->inviteCode;
    if (TUserInfoPrivate::EmailContexts.contains(d->context))
        b = b && d->email == dd->email;
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        b = b && d->login == dd->login;
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        b = b && d->password == dd->password;
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        b = b && d->accessLevel == dd->accessLevel;
    if (TUserInfoPrivate::ServicesContexts.contains(d->context))
        b = b && d->services == dd->services;
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        b = b && d->realName == dd->realName;
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        b = b && d->avatar == dd->avatar;
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        b = b && d->creationDT == dd->creationDT;
    if (TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        b = b && d->updateDT == dd->updateDT;
    return b;
}

bool TUserInfo::operator !=(const TUserInfo &other) const
{
    return !(*this == other);
}

TUserInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("context", (int) d->context);
    if (TUserInfoPrivate::IdContexts.contains(d->context))
        m.insert("id", d->id);
    if (TUserInfoPrivate::InviteCodeContexts.contains(d->context))
        m.insert("invite_code", QVariant::fromValue(d->inviteCode));
    if (TUserInfoPrivate::EmailContexts.contains(d->context))
        m.insert("email", d->email);
    if (TUserInfoPrivate::LoginContexts.contains(d->context))
        m.insert("login", d->login);
    if (TUserInfoPrivate::PasswordContexts.contains(d->context))
        m.insert("password", d->password);
    if (TUserInfoPrivate::AccessLevelContexts.contains(d->context))
        m.insert("access_level", d->accessLevel);
    if (TUserInfoPrivate::ServicesContexts.contains(d->context))
        m.insert("services", d->services);
    if (TUserInfoPrivate::RealNameContexts.contains(d->context))
        m.insert("real_name", d->realName);
    if (TUserInfoPrivate::AvatarContexts.contains(d->context))
        m.insert("avatar", d->avatar);
    if (TUserInfoPrivate::CreationDTContexts.contains(d->context))
        m.insert("creation_dt", d->creationDT);
    if (TUserInfoPrivate::UpdateDTContexts.contains(d->context))
        m.insert("update_dt", d->updateDT);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TUserInfo &info)
{
    TUserInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->context = TUserInfoPrivate::contextFromInt(m.value("context").toInt());
    d->id = m.value("id").toULongLong();
    d->inviteCode = m.value("invite_code").value<QUuid>();
    info.setEmail(m.value("email").toString());
    info.setLogin(m.value("login").toString());
    d->password = m.value("password").toByteArray();
    d->accessLevel = m.value("access_level").value<TAccessLevel>();
    info.setServices(m.value("services").value<TServiceList>());
    info.setRealName(m.value("real_name").toString());
    info.setAvatar(m.value("avatar").toByteArray());
    d->creationDT = m.value("creation_dt").toDateTime().toTimeSpec(Qt::UTC);
    d->updateDT = m.value("update_dt").toDateTime().toTimeSpec(Qt::UTC);
    return stream;
}

QDebug operator <<(QDebug dbg, const TUserInfo &info)
{
    const TUserInfoPrivate *d = info.d_func();
    dbg.nospace() << "TUserInfo(" << d->context << "," << d->id << "," << d->login << ")";
    return dbg.space();
}
