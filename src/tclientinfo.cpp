#include "tclientinfo.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>

#include <QObject>
#include <QDataStream>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QCoreApplication>

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
    QString client;
    QString texsample;
    QString beqt;
    QString qt;
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
    //
}

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

/*============================== Static public methods =====================*/

TClientInfo TClientInfo::createDefaultInfo()
{
    TClientInfo info;
    info.setOS(BeQt::osVersion());
    info.setEditorVersion(QCoreApplication::applicationVersion());
    info.setTexsampleVersion(tVersion());
    info.setBeqtVersion(bVersion());
    info.setQtVersion(qVersion());
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

void TClientInfo::setOS(const QString &os)
{
    d_func()->os = os;
}

void TClientInfo::setEditorVersion(const QString &v)
{
    d_func()->client = v;
}

void TClientInfo::setTexsampleVersion(const QString &v)
{
    d_func()->texsample = v;
}

void TClientInfo::setBeqtVersion(const QString &v)
{
    d_func()->beqt = v;
}

void TClientInfo::setQtVersion(const QString &v)
{
    d_func()->qt = v;
}

QString TClientInfo::os() const
{
    return d_func()->os;
}

QString TClientInfo::editorVersion() const
{
    return d_func()->client;
}

QString TClientInfo::texsampleVersion() const
{
    return d_func()->texsample;
}

QString TClientInfo::beqtVersion() const
{
    return d_func()->beqt;
}

QString TClientInfo::qtVersion() const
{
    return d_func()->qt;
}

QString TClientInfo::toString(const QString &format) const
{
    const B_D(TClientInfo);
    QString f = !format.isEmpty() ? format : QString("%o\n%c\n%t\n%b\n%q");
    //"%o\n%c %v\n%t\n%b\n%q"
    f.replace("%o", tr("OS:") + " " + d->os);
    //f.replace("%v", "v" + d->client);
    f.replace("%c", tr("Client:") + " " + d->client);
    f.replace("%t", "TeXSample: " + d->texsample);
    f.replace("%b", "BeQt: " + d->beqt);
    f.replace("%q", "Qt: " + d->qt);
    return f;
}

bool TClientInfo::isValid() const
{
    const B_D(TClientInfo);
    return !d->os.isEmpty() && !d->client.isEmpty() && !d->texsample.isEmpty()
            && !d->beqt.isEmpty() && !d->qt.isEmpty();
}

/*============================== Public operators ==========================*/

TClientInfo &TClientInfo::operator =(const TClientInfo &other)
{
    B_D(TClientInfo);
    const TClientInfoPrivate *dd = other.d_func();
    d->os = dd->os;
    d->client = dd->client;
    d->texsample = dd->texsample;
    d->beqt = dd->beqt;
    d->qt = dd->qt;
    return *this;
}

bool TClientInfo::operator ==(const TClientInfo &other) const
{
    const B_D(TClientInfo);
    const TClientInfoPrivate *dd = other.d_func();
    return d->os == dd->os && d->client == dd->client && d->texsample == dd->texsample
            && d->beqt == dd->beqt && d->qt == dd->qt;
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
    stream << d->client;
    stream << d->texsample;
    stream << d->beqt;
    stream << d->qt;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TClientInfo &info)
{
    TClientInfoPrivate *d = info.d_func();
    stream >> d->os;
    stream >> d->client;
    stream >> d->texsample;
    stream >> d->beqt;
    stream >> d->qt;
    return stream;
}

QDebug operator <<(QDebug dbg, const TClientInfo &info)
{
    const TClientInfoPrivate *d = info.d_func();
    dbg.nospace() << "TClientInfo(" << d->os << "," << d->client << "," << d->texsample << ","
                  << d->beqt << "," << d->qt << ")";
    return dbg.space();
}
