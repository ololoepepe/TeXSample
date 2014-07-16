#include "tdeletesamplerequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteSampleRequestDataPrivate =============
============================================================================*/

class TDeleteSampleRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteSampleRequestData)
public:
    quint64 id;
public:
    explicit TDeleteSampleRequestDataPrivate(TDeleteSampleRequestData *q);
    ~TDeleteSampleRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteSampleRequestDataPrivate)
};

/*============================================================================
================================ TDeleteSampleRequestDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteSampleRequestDataPrivate::TDeleteSampleRequestDataPrivate(TDeleteSampleRequestData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteSampleRequestDataPrivate::~TDeleteSampleRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteSampleRequestDataPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TDeleteSampleRequestData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteSampleRequestData::TDeleteSampleRequestData() :
    BBase(*new TDeleteSampleRequestDataPrivate(this))
{
    d_func()->init();
}

TDeleteSampleRequestData::TDeleteSampleRequestData(const TDeleteSampleRequestData &other) :
    BBase(*new TDeleteSampleRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteSampleRequestData::~TDeleteSampleRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteSampleRequestData::clear()
{
    d_func()->id = 0;
}

quint64 TDeleteSampleRequestData::id() const
{
    return d_func()->id;
}

bool TDeleteSampleRequestData::isValid() const
{
    return d_func()->id;
}

void TDeleteSampleRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

/*============================== Public operators ==========================*/

TDeleteSampleRequestData &TDeleteSampleRequestData::operator =(const TDeleteSampleRequestData &other)
{
    B_D(TDeleteSampleRequestData);
    const TDeleteSampleRequestDataPrivate *dd = other.d_func();
    d->id = dd->id;
    return *this;
}

bool TDeleteSampleRequestData::operator ==(const TDeleteSampleRequestData &other) const
{
    const B_D(TDeleteSampleRequestData);
    const TDeleteSampleRequestDataPrivate *dd = other.d_func();
    return d->id == dd->id;
}

bool TDeleteSampleRequestData::operator !=(const TDeleteSampleRequestData &other) const
{
    return !(*this == other);
}

TDeleteSampleRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteSampleRequestData &data)
{
    const TDeleteSampleRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteSampleRequestData &data)
{
    TDeleteSampleRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteSampleRequestData &/*data*/)
{
    //const TDeleteSampleRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteSampleRequestData(" << ")";
    return dbg.space();
}
