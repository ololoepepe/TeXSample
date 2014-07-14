#include "tdeleteuserrequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteUserRequestDataPrivate ===============
============================================================================*/

class TDeleteUserRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteUserRequestData)
public:
    TUserIdentifier identifier;
public:
    explicit TDeleteUserRequestDataPrivate(TDeleteUserRequestData *q);
    ~TDeleteUserRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteUserRequestDataPrivate)
};


/*============================================================================
================================ TDeleteUserRequestDataPrivate ===============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserRequestDataPrivate::TDeleteUserRequestDataPrivate(TDeleteUserRequestData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteUserRequestDataPrivate::~TDeleteUserRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteUserRequestData ======================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserRequestData::TDeleteUserRequestData() :
    BBase(*new TDeleteUserRequestDataPrivate(this))
{
    d_func()->init();
}

TDeleteUserRequestData::TDeleteUserRequestData(const TDeleteUserRequestData &other) :
    BBase(*new TDeleteUserRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteUserRequestData::~TDeleteUserRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserRequestData::clear()
{
    d_func()->identifier.clear();
}

TUserIdentifier TDeleteUserRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TDeleteUserRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TDeleteUserRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

/*============================== Public operators ==========================*/

TDeleteUserRequestData &TDeleteUserRequestData::operator =(const TDeleteUserRequestData &other)
{
    B_D(TDeleteUserRequestData);
    const TDeleteUserRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    return *this;
}

bool TDeleteUserRequestData::operator ==(const TDeleteUserRequestData &other) const
{
    const B_D(TDeleteUserRequestData);
    const TDeleteUserRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier;
}

bool TDeleteUserRequestData::operator !=(const TDeleteUserRequestData &other) const
{
    return !(*this == other);
}

TDeleteUserRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteUserRequestData &data)
{
    const TDeleteUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteUserRequestData &data)
{
    TDeleteUserRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteUserRequestData &/*data*/)
{
    //const TDeleteUserRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteUserRequestData(" << ")";
    return dbg.space();
}
