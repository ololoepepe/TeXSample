#include "tclientinfo.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>
#include <BCoreApplication>

#include <QObject>
#include <QDataStream>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QLocale>
#include <QStringList>

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
    QString clientVersion;
    QString texsampleVersion;
    QString beqtVersion;
    QString qtVersion;
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

TClientInfo TClientInfo::createDefaultInfo()
{
    TClientInfo info;
    info.setOS(BeQt::osVersion());
    info.setLocale(BCoreApplication::locale());
    info.setClient(QCoreApplication::applicationName());
    info.setClientVersion(QCoreApplication::applicationVersion());
    info.setTexsampleVersion(tVersion());
    info.setBeqtVersion(bVersion());
    info.setQtVersion(qVersion());
    return info;
}

int TClientInfo::compareVersions(const QString &v1, const QString &v2, bool ignoreSuffix)
{
    Q_UNUSED(ignoreSuffix)
    if (v1.isEmpty() && v2.isEmpty())
        return 0;
    if (v1.isEmpty() && !v2.isEmpty())
        return -1;
    if (!v1.isEmpty() && v2.isEmpty())
        return 1;
    QStringList sl1 = v1.split('-');
    QStringList sl2 = v2.split('-');
    QList<int> vv1;
    foreach (const QString &s, sl1.first().split('.'))
        vv1 << s.toUInt();
    QList<int> vv2;
    foreach (const QString &s, sl2.first().split('.'))
        vv2 << s.toUInt();
    foreach (int i, bRangeD(0, qMin(vv1.size(), vv2.size()) - 1))
    {
        if (vv1.at(i) < vv2.at(i))
            return -1;
        if (vv1.at(i) > vv2.at(i))
            return 1;
    }
    if (vv1.size() < vv2.size())
        return -1;
    if (vv1.size() > vv2.size())
        return 1;
    return 0;
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

void TClientInfo::setOS(const QString &os)
{
    d_func()->os = os;
}

void TClientInfo::setLocale(const QLocale &l)
{
    d_func()->locale = l;
}

void TClientInfo::setClient(const QString &name)
{
    d_func()->client = name;
}

void TClientInfo::setClientVersion(const QString &v)
{
    d_func()->clientVersion = v;
}

void TClientInfo::setEditorVersion(const QString &v)
{
    setClientVersion(v);
}

void TClientInfo::setTexsampleVersion(const QString &v)
{
    d_func()->texsampleVersion = v;
}

void TClientInfo::setBeqtVersion(const QString &v)
{
    d_func()->beqtVersion = v;
}

void TClientInfo::setQtVersion(const QString &v)
{
    d_func()->qtVersion = v;
}

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

QString TClientInfo::clientVersion() const
{
    return d_func()->clientVersion;
}

QString TClientInfo::editorVersion() const
{
    return clientVersion();
}

QString TClientInfo::texsampleVersion() const
{
    return d_func()->texsampleVersion;
}

QString TClientInfo::beqtVersion() const
{
    return d_func()->beqtVersion;
}

QString TClientInfo::qtVersion() const
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
    {
        if (compareVersions(d->clientVersion, "2.1.0") >= 0 || (d->client == "TeXSample Client"))
            f = "%o [%l]\n%c v%v\nTeXSample v%t; BeQt v%b; Qt v%q";
        else
            f = "%o\nv%v\nTeXSample v%t; BeQt v%b; Qt v%q";
    }
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
    return true;
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
    stream << d->os;
    stream << d->clientVersion;
    stream << d->texsampleVersion;
    stream << d->beqtVersion;
    stream << d->qtVersion;
    stream << d->locale;
    stream << d->client;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TClientInfo &info)
{
    TClientInfoPrivate *d = info.d_func();
    stream >> d->os;
    stream >> d->clientVersion;
    stream >> d->texsampleVersion;
    stream >> d->beqtVersion;
    stream >> d->qtVersion;
    if (TClientInfo::compareVersions(d->clientVersion, "2.1.0") >= 0 || (d->client == "TeXSample Client"))
    {
        stream >> d->locale;
        stream >> d->client;
    }
    return stream;
}

QDebug operator <<(QDebug dbg, const TClientInfo &info)
{
    const TClientInfoPrivate *d = info.d_func();
    dbg.nospace() << "TClientInfo(" << d->os << "," << d->locale.name() << "," << d->client << ","
                  << d->clientVersion << "," << d->texsampleVersion << "," << d->beqtVersion << ","
                  << d->qtVersion << ")";
    return dbg.space();
}
