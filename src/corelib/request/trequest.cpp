#include "trequest.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRequestPrivate =============================
============================================================================*/

class TRequestPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRequest)
public:
    bool cachingEnabled;
    QVariant data;
    QDateTime lastRequestDateTime;
public:
    explicit TRequestPrivate(TRequest *q);
    ~TRequestPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRequestPrivate)
};


/*============================================================================
================================ TRequestPrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TRequestPrivate::TRequestPrivate(TRequest *q) :
    BBasePrivate(q)
{
    //
}

TRequestPrivate::~TRequestPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRequestPrivate::init()
{
    cachingEnabled = false;
    lastRequestDateTime.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TRequest ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TRequest::TRequest() :
    BBase(*new TRequestPrivate(this))
{
    d_func()->init();
}

TRequest::TRequest(const TRequest &other) :
    BBase(*new TRequestPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRequest::~TRequest()
{
    //
}

/*============================== Public methods ============================*/

bool TRequest::cachingEnabled() const
{
    return d_func()->cachingEnabled;
}

void TRequest::clear()
{
    B_D(TRequest);
    d->cachingEnabled = false;
    d->data.clear();
    d->lastRequestDateTime = QDateTime().toUTC();
}

QVariant TRequest::data() const
{
    return d_func()->data;
}

QDateTime TRequest::lastRequestDateTime() const
{
    return d_func()->lastRequestDateTime;
}

void TRequest::setCachingEnabled(bool enabled)
{
    d_func()->cachingEnabled = enabled;
}

void TRequest::setData(const QVariant &data)
{
    d_func()->data = data;
}

void TRequest::setLastRequestDateTime(const QDateTime &dt)
{
    d_func()->lastRequestDateTime = dt.toUTC();
}

/*============================== Public operators ==========================*/

TRequest &TRequest::operator =(const TRequest &other)
{
    B_D(TRequest);
    const TRequestPrivate *dd = other.d_func();
    d->cachingEnabled = dd->cachingEnabled;
    d->data = dd->data;
    d->lastRequestDateTime = dd->lastRequestDateTime;
    return *this;
}

bool TRequest::operator ==(const TRequest &other) const
{
    const B_D(TRequest);
    const TRequestPrivate *dd = other.d_func();
    return d->cachingEnabled == dd->cachingEnabled && d->data == dd->data
            && d->lastRequestDateTime == dd->lastRequestDateTime;
}

bool TRequest::operator !=(const TRequest &other) const
{
    return !(*this == other);
}

TRequest::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRequest &data)
{
    const TRequestPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("caching_enabled", d->cachingEnabled);
    m.insert("data", d->data);
    m.insert("last_request_date_time", d->lastRequestDateTime);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRequest &data)
{
    TRequestPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->cachingEnabled = m.value("caching_enabled").toBool();
    d->data = m.value("data");
    d->lastRequestDateTime = m.value("last_request_date_time").toDateTime().toUTC();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRequest &/*data*/)
{
    //const TRequestPrivate *d = data.d_func();
    dbg.nospace() << "TRequest(" << ")";
    return dbg.space();
}
