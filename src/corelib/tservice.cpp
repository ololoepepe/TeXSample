#include "tservice.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TServicePrivate =============================
============================================================================*/

class TServicePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TService)
public:
    TService::Service service;
public:
   explicit TServicePrivate(TService *q);
    ~TServicePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TServicePrivate)
};

/*============================================================================
================================ TServicePrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TServicePrivate::TServicePrivate(TService *q) :
    BBasePrivate(q)
{
    //
}

TServicePrivate::~TServicePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TServicePrivate::init()
{
    service = TService::NoService;
}

/*============================================================================
================================ TService ====================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TService::serviceToString(Service srv)
{
    return tr(serviceToStringNoTr(srv).toUtf8().constData());
}

QString TService::serviceToStringNoTr(Service srv)
{
    switch (srv)
    {
    case TexsampleService:
        return QT_TRANSLATE_NOOP("TService", "TeXSample");
    case ClabService:
        return QT_TRANSLATE_NOOP("TService", "CloudLab");
    case NoService:
    default:
        return QT_TRANSLATE_NOOP("TService", "No");
    }
}

/*============================== Public constructors =======================*/

TService::TService(int srv) :
    BBase(*new TServicePrivate(this))
{
    d_func()->init();
    *this = srv;
}

TService::TService(const TService &other) :
    BBase(*new TServicePrivate(this))
{
    d_func()->init();
    *this = other;
}

TService::~TService()
{
    //
}

/*============================== Public methods ============================*/

QString TService::toString() const
{
    return serviceToString(d_func()->service);
}

QString TService::toStringNoTr() const
{
    return serviceToStringNoTr(d_func()->service);
}

/*============================== Public operators ==========================*/

TService &TService::operator =(const TService &other)
{
    d_func()->service = other.d_func()->service;
    return *this;
}

TService &TService::operator =(int srv)
{
    static const QList<int> Services = bRangeD(TexsampleService, ClabService);
    d_func()->service = Services.contains(srv) ? static_cast<Service>(srv) : NoService;
    return *this;
}

bool TService::operator ==(const TService &other) const
{
    return d_func()->service == other.d_func()->service;
}

bool TService::operator !=(const TService &other) const
{
    return !(*this == other);
}

TService::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TService::operator int() const
{
    return (int) d_func()->service;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TService &srv)
{
    QVariantMap m;
    m.insert("service", (int) srv.d_func()->service);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TService &srv)
{
    QVariantMap m;
    stream >> m;
    srv = m.value("service").toInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TService &srv)
{
    dbg.nospace() << "TService(" << srv.toStringNoTr() << ")";
    return dbg.space();
}
