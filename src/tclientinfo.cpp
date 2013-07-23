#include "tclientinfo.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>
#include <BCoreApplication>
#include <BVersion>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QLocale>
#include <QVariantMap>

/*============================================================================
================================ TClientInfoPrivate ==========================
============================================================================*/

class TClientInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TClientInfo)
public:
   explicit TClientInfoPrivate(TClientInfo *q);
    ~TClientInfoPrivate();
public:
    void init();
public:
    QString os;
    QLocale locale;
    QString client;
    BVersion clientVersion;
    BVersion texsampleVersion;
    BVersion beqtVersion;
    BVersion qtVersion;
private:
    Q_DISABLE_COPY(TClientInfoPrivate)
};

/*============================================================================
================================ TClientInfoPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TClientInfoPrivate::TClientInfoPrivate(TClientInfo *q) :
    BBasePrivate(q)
{
    //
}

TClientInfoPrivate::~TClientInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TClientInfoPrivate::init()
{
    locale = QLocale("en");
}

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

/*============================== Static public methods =====================*/

TClientInfo TClientInfo::createInfo()
{
    TClientInfo info;
    TClientInfoPrivate *d = info.d_func();
    d->os = BeQt::osVersion();
    d->locale = BCoreApplication::locale();
    d->client = QCoreApplication::applicationName();
    d->clientVersion = BVersion(QCoreApplication::applicationVersion());
    d->texsampleVersion = BVersion(tVersion());
    d->beqtVersion = BVersion(bVersion());
    d->qtVersion = BVersion(qVersion());
    return info;
}

/*============================== Public constructors =======================*/

TClientInfo::TClientInfo() :
    BBase(*new TClientInfoPrivate(this))
{
    d_func()->init();
}

TClientInfo::TClientInfo(const TClientInfo &other) :
    BBase(*new TClientInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TClientInfo::~TClientInfo()
{
    //
}

/*============================== Public methods ============================*/

QString TClientInfo::os() const
{
    return d_func()->os;
}

QLocale TClientInfo::locale() const
{
    return d_func()->locale;
}

QString TClientInfo::client() const
{
    return d_func()->client;
}

BVersion TClientInfo::clientVersion() const
{
    return d_func()->clientVersion;
}

BVersion TClientInfo::texsampleVersion() const
{
    return d_func()->texsampleVersion;
}

BVersion TClientInfo::beqtVersion() const
{
    return d_func()->beqtVersion;
}

BVersion TClientInfo::qtVersion() const
{
    return d_func()->qtVersion;
}

QString TClientInfo::toString(const QString &format) const
{
    //%o - OS, %l - locale, %c - client, %v - client version
    //%t - texsample version, %b - BeQt version, %q - Qt version
    const B_D(TClientInfo);
    QString f = format;
    if (f.isEmpty())
        f = "%o [%l]\n%c v%v; TeXSample v%t; BeQt v%b; Qt v%q";
    f.replace("%o", d->os);
    f.replace("%l", d->locale.name());
    f.replace("%c", d->client);
    f.replace("%v", d->clientVersion);
    f.replace("%t", d->texsampleVersion);
    f.replace("%b", d->beqtVersion);
    f.replace("%q", d->qtVersion);
    return f;
}

bool TClientInfo::isValid() const
{
    const B_D(TClientInfo);
    return !d->os.isEmpty() && !d->client.isEmpty() && d->clientVersion.isValid() && d->texsampleVersion.isValid()
            && d->beqtVersion.isValid() && d->qtVersion.isValid();
}

/*============================== Public operators ==========================*/

TClientInfo &TClientInfo::operator =(const TClientInfo &other)
{
    B_D(TClientInfo);
    const TClientInfoPrivate *dd = other.d_func();
    d->os = dd->os;
    d->locale = dd->locale;
    d->client = dd->client;
    d->clientVersion = dd->clientVersion;
    d->texsampleVersion = dd->texsampleVersion;
    d->beqtVersion = dd->beqtVersion;
    d->qtVersion = dd->qtVersion;
    return *this;
}

bool TClientInfo::operator ==(const TClientInfo &other) const
{
    const B_D(TClientInfo);
    const TClientInfoPrivate *dd = other.d_func();
    return d->os == dd->os && d->locale == dd->locale && d->client == dd->client
            && d->clientVersion == dd->clientVersion && d->texsampleVersion == dd->texsampleVersion
            && d->beqtVersion == dd->beqtVersion && d->qtVersion == dd->qtVersion;
}

TClientInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TClientInfo &info)
{
    const TClientInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("os", d->os);
    m.insert("locale", d->locale);
    m.insert("client", d->client);
    m.insert("client_v", d->clientVersion);
    m.insert("texsample_v", d->texsampleVersion);
    m.insert("beqt_v", d->beqtVersion);
    m.insert("qt_v", d->qtVersion);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TClientInfo &info)
{
    TClientInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->os = m.value("os").toString();
    d->locale = m.value("locale").toLocale();
    d->client = m.value("client").toString();
    d->clientVersion = m.value("client_v").value<BVersion>();
    d->texsampleVersion = m.value("texsample_v").value<BVersion>();
    d->beqtVersion = m.value("beqt_v").value<BVersion>();
    d->qtVersion = m.value("qt_v").value<BVersion>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TClientInfo &info)
{
    dbg.nospace() << "TClientInfo(" << info.toString("%o,%l,%c,%v,%t,%b,%q") << ")";
    return dbg.space();
}
