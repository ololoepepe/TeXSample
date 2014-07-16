#include "tcheckemailavailabilityreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCheckEmailAvailabilityReplyDataPrivate =====
============================================================================*/

class TCheckEmailAvailabilityReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCheckEmailAvailabilityReplyData)
public:
    bool available;
public:
    explicit TCheckEmailAvailabilityReplyDataPrivate(TCheckEmailAvailabilityReplyData *q);
    ~TCheckEmailAvailabilityReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCheckEmailAvailabilityReplyDataPrivate)
};

/*============================================================================
================================ TCheckEmailAvailabilityReplyDataPrivate =====
============================================================================*/

/*============================== Public constructors =======================*/

TCheckEmailAvailabilityReplyDataPrivate::TCheckEmailAvailabilityReplyDataPrivate(TCheckEmailAvailabilityReplyData *q) :
    BBasePrivate(q)
{
    //
}

TCheckEmailAvailabilityReplyDataPrivate::~TCheckEmailAvailabilityReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCheckEmailAvailabilityReplyDataPrivate::init()
{
    available = false;
}

/*============================================================================
================================ TCheckEmailAvailabilityReplyData ============
============================================================================*/

/*============================== Public constructors =======================*/

TCheckEmailAvailabilityReplyData::TCheckEmailAvailabilityReplyData() :
    BBase(*new TCheckEmailAvailabilityReplyDataPrivate(this))
{
    d_func()->init();
}

TCheckEmailAvailabilityReplyData::TCheckEmailAvailabilityReplyData(const TCheckEmailAvailabilityReplyData &other) :
    BBase(*new TCheckEmailAvailabilityReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCheckEmailAvailabilityReplyData::~TCheckEmailAvailabilityReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TCheckEmailAvailabilityReplyData::setAvailable(bool available)
{
    d_func()->available = available;
}

bool TCheckEmailAvailabilityReplyData::available() const
{
    return d_func()->available;
}

/*============================== Public operators ==========================*/

TCheckEmailAvailabilityReplyData &TCheckEmailAvailabilityReplyData::operator =(
        const TCheckEmailAvailabilityReplyData &other)
{
    B_D(TCheckEmailAvailabilityReplyData);
    const TCheckEmailAvailabilityReplyDataPrivate *dd = other.d_func();
    d->available = dd->available;
    return *this;
}

bool TCheckEmailAvailabilityReplyData::operator ==(const TCheckEmailAvailabilityReplyData &other) const
{
    const B_D(TCheckEmailAvailabilityReplyData);
    const TCheckEmailAvailabilityReplyDataPrivate *dd = other.d_func();
    return d->available == dd->available;
}

bool TCheckEmailAvailabilityReplyData::operator !=(const TCheckEmailAvailabilityReplyData &other) const
{
    return !(*this == other);
}

TCheckEmailAvailabilityReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCheckEmailAvailabilityReplyData &data)
{
    const TCheckEmailAvailabilityReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("available", d->available);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCheckEmailAvailabilityReplyData &data)
{
    TCheckEmailAvailabilityReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->available = m.value("available").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCheckEmailAvailabilityReplyData &/*data*/)
{
    //const TCheckEmailAvailabilityReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TCheckEmailAvailabilityReplyData(" << ")";
    return dbg.space();
}
