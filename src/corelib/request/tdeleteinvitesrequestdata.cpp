#include "tdeleteinvitesrequestdata.h"

#include "tidlist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteInvitesRequestDataPrivate ============
============================================================================*/

class TDeleteInvitesRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteInvitesRequestData)
public:
    TIdList ids;
public:
    explicit TDeleteInvitesRequestDataPrivate(TDeleteInvitesRequestData *q);
    ~TDeleteInvitesRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteInvitesRequestDataPrivate)
};


/*============================================================================
================================ TDeleteInvitesRequestDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesRequestDataPrivate::TDeleteInvitesRequestDataPrivate(TDeleteInvitesRequestData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteInvitesRequestDataPrivate::~TDeleteInvitesRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteInvitesRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteInvitesRequestData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesRequestData::TDeleteInvitesRequestData() :
    BBase(*new TDeleteInvitesRequestDataPrivate(this))
{
    d_func()->init();
}

TDeleteInvitesRequestData::TDeleteInvitesRequestData(const TDeleteInvitesRequestData &other) :
    BBase(*new TDeleteInvitesRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteInvitesRequestData::~TDeleteInvitesRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteInvitesRequestData::clear()
{
    d_func()->ids.clear();
}

TIdList TDeleteInvitesRequestData::ids() const
{
    return d_func()->ids;
}

bool TDeleteInvitesRequestData::isValid() const
{
    return !d_func()->ids.isEmpty();
}

void TDeleteInvitesRequestData::setIds(const TIdList &ids)
{
    B_D(TDeleteInvitesRequestData);
    d->ids = ids;
    d->ids.removeAll(0);
    bRemoveDuplicates(d->ids);
}

/*============================== Public operators ==========================*/

TDeleteInvitesRequestData &TDeleteInvitesRequestData::operator =(const TDeleteInvitesRequestData &other)
{
    B_D(TDeleteInvitesRequestData);
    const TDeleteInvitesRequestDataPrivate *dd = other.d_func();
    d->ids = dd->ids;
    return *this;
}

bool TDeleteInvitesRequestData::operator ==(const TDeleteInvitesRequestData &other) const
{
    const B_D(TDeleteInvitesRequestData);
    const TDeleteInvitesRequestDataPrivate *dd = other.d_func();
    return d->ids == dd->ids;
}

bool TDeleteInvitesRequestData::operator !=(const TDeleteInvitesRequestData &other) const
{
    return !(*this == other);
}

TDeleteInvitesRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesRequestData &data)
{
    const TDeleteInvitesRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("ids", d->ids);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteInvitesRequestData &data)
{
    TDeleteInvitesRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->ids = m.value("ids").value<TIdList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteInvitesRequestData &/*data*/)
{
    //const TDeleteInvitesRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteInvitesRequestData(" << ")";
    return dbg.space();
}
