#include "tgetsamplepreviewrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSamplePreviewRequestDataPrivate =========
============================================================================*/

class TGetSamplePreviewRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSamplePreviewRequestData)
public:
    quint64 id;
public:
    explicit TGetSamplePreviewRequestDataPrivate(TGetSamplePreviewRequestData *q);
    ~TGetSamplePreviewRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSamplePreviewRequestDataPrivate)
};

/*============================================================================
================================ TGetSamplePreviewRequestDataPrivate =========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSamplePreviewRequestDataPrivate::TGetSamplePreviewRequestDataPrivate(TGetSamplePreviewRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetSamplePreviewRequestDataPrivate::~TGetSamplePreviewRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSamplePreviewRequestDataPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TGetSamplePreviewRequestData ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSamplePreviewRequestData::TGetSamplePreviewRequestData() :
    BBase(*new TGetSamplePreviewRequestDataPrivate(this))
{
    d_func()->init();
}

TGetSamplePreviewRequestData::TGetSamplePreviewRequestData(const TGetSamplePreviewRequestData &other) :
    BBase(*new TGetSamplePreviewRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSamplePreviewRequestData::~TGetSamplePreviewRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetSamplePreviewRequestData::clear()
{
    d_func()->id = 0;
}

quint64 TGetSamplePreviewRequestData::id() const
{
    return d_func()->id;
}

bool TGetSamplePreviewRequestData::isValid() const
{
    return d_func()->id;
}

void TGetSamplePreviewRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

/*============================== Public operators ==========================*/

TGetSamplePreviewRequestData &TGetSamplePreviewRequestData::operator =(const TGetSamplePreviewRequestData &other)
{
    B_D(TGetSamplePreviewRequestData);
    const TGetSamplePreviewRequestDataPrivate *dd = other.d_func();
    d->id = dd->id;
    return *this;
}

bool TGetSamplePreviewRequestData::operator ==(const TGetSamplePreviewRequestData &other) const
{
    const B_D(TGetSamplePreviewRequestData);
    const TGetSamplePreviewRequestDataPrivate *dd = other.d_func();
    return d->id == dd->id;
}

bool TGetSamplePreviewRequestData::operator !=(const TGetSamplePreviewRequestData &other) const
{
    return !(*this == other);
}

TGetSamplePreviewRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSamplePreviewRequestData &data)
{
    const TGetSamplePreviewRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSamplePreviewRequestData &data)
{
    TGetSamplePreviewRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSamplePreviewRequestData &/*data*/)
{
    //const TGetSamplePreviewRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSamplePreviewRequestData(" << ")";
    return dbg.space();
}
