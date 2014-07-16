#include "tgetsamplesourcerequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleSourceRequestDataPrivate ==========
============================================================================*/

class TGetSampleSourceRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleSourceRequestData)
public:
    quint64 id;
public:
    explicit TGetSampleSourceRequestDataPrivate(TGetSampleSourceRequestData *q);
    ~TGetSampleSourceRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleSourceRequestDataPrivate)
};

/*============================================================================
================================ TGetSampleSourceRequestDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleSourceRequestDataPrivate::TGetSampleSourceRequestDataPrivate(TGetSampleSourceRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleSourceRequestDataPrivate::~TGetSampleSourceRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleSourceRequestDataPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TGetSampleSourceRequestData =================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleSourceRequestData::TGetSampleSourceRequestData() :
    BBase(*new TGetSampleSourceRequestDataPrivate(this))
{
    d_func()->init();
}

TGetSampleSourceRequestData::TGetSampleSourceRequestData(const TGetSampleSourceRequestData &other) :
    BBase(*new TGetSampleSourceRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleSourceRequestData::~TGetSampleSourceRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleSourceRequestData::clear()
{
    d_func()->id = 0;
}

quint64 TGetSampleSourceRequestData::id() const
{
    return d_func()->id;
}

bool TGetSampleSourceRequestData::isValid() const
{
    return d_func()->id;
}

void TGetSampleSourceRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

/*============================== Public operators ==========================*/

TGetSampleSourceRequestData &TGetSampleSourceRequestData::operator =(const TGetSampleSourceRequestData &other)
{
    B_D(TGetSampleSourceRequestData);
    const TGetSampleSourceRequestDataPrivate *dd = other.d_func();
    d->id = dd->id;
    return *this;
}

bool TGetSampleSourceRequestData::operator ==(const TGetSampleSourceRequestData &other) const
{
    const B_D(TGetSampleSourceRequestData);
    const TGetSampleSourceRequestDataPrivate *dd = other.d_func();
    return d->id == dd->id;
}

bool TGetSampleSourceRequestData::operator !=(const TGetSampleSourceRequestData &other) const
{
    return !(*this == other);
}

TGetSampleSourceRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceRequestData &data)
{
    const TGetSampleSourceRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleSourceRequestData &data)
{
    TGetSampleSourceRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleSourceRequestData &/*data*/)
{
    //const TGetSampleSourceRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleSourceRequestData(" << ")";
    return dbg.space();
}
