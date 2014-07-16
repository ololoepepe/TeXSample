#include "tdeletegrouprequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteGroupRequestDataPrivate ==============
============================================================================*/

class TDeleteGroupRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteGroupRequestData)
public:
    quint64 id;
public:
    explicit TDeleteGroupRequestDataPrivate(TDeleteGroupRequestData *q);
    ~TDeleteGroupRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteGroupRequestDataPrivate)
};

/*============================================================================
================================ TDeleteGroupRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteGroupRequestDataPrivate::TDeleteGroupRequestDataPrivate(TDeleteGroupRequestData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteGroupRequestDataPrivate::~TDeleteGroupRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteGroupRequestDataPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TDeleteGroupRequestData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteGroupRequestData::TDeleteGroupRequestData() :
    BBase(*new TDeleteGroupRequestDataPrivate(this))
{
    d_func()->init();
}

TDeleteGroupRequestData::TDeleteGroupRequestData(const TDeleteGroupRequestData &other) :
    BBase(*new TDeleteGroupRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteGroupRequestData::~TDeleteGroupRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteGroupRequestData::clear()
{
    d_func()->id = 0;
}

quint64 TDeleteGroupRequestData::id() const
{
    return d_func()->id;
}

bool TDeleteGroupRequestData::isValid() const
{
    return d_func()->id;
}

void TDeleteGroupRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

/*============================== Public operators ==========================*/

TDeleteGroupRequestData &TDeleteGroupRequestData::operator =(const TDeleteGroupRequestData &other)
{
    B_D(TDeleteGroupRequestData);
    const TDeleteGroupRequestDataPrivate *dd = other.d_func();
    d->id = dd->id;
    return *this;
}

bool TDeleteGroupRequestData::operator ==(const TDeleteGroupRequestData &other) const
{
    const B_D(TDeleteGroupRequestData);
    const TDeleteGroupRequestDataPrivate *dd = other.d_func();
    return d->id == dd->id;
}

bool TDeleteGroupRequestData::operator !=(const TDeleteGroupRequestData &other) const
{
    return !(*this == other);
}

TDeleteGroupRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteGroupRequestData &data)
{
    const TDeleteGroupRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteGroupRequestData &data)
{
    TDeleteGroupRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteGroupRequestData &/*data*/)
{
    //const TDeleteGroupRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteGroupRequestData(" << ")";
    return dbg.space();
}
