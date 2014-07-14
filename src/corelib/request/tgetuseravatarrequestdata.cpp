#include "tgetuseravatarrequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserAvatarRequestDataPrivate ============
============================================================================*/

class TGetUserAvatarRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserAvatarRequestData)
public:
    TUserIdentifier identifier;
public:
    explicit TGetUserAvatarRequestDataPrivate(TGetUserAvatarRequestData *q);
    ~TGetUserAvatarRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserAvatarRequestDataPrivate)
};


/*============================================================================
================================ TGetUserAvatarRequestDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarRequestDataPrivate::TGetUserAvatarRequestDataPrivate(TGetUserAvatarRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserAvatarRequestDataPrivate::~TGetUserAvatarRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserAvatarRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserAvatarRequestData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarRequestData::TGetUserAvatarRequestData() :
    BBase(*new TGetUserAvatarRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserAvatarRequestData::TGetUserAvatarRequestData(const TGetUserAvatarRequestData &other) :
    BBase(*new TGetUserAvatarRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserAvatarRequestData::~TGetUserAvatarRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserAvatarRequestData::clear()
{
    d_func()->identifier.clear();
}

TUserIdentifier TGetUserAvatarRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TGetUserAvatarRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TGetUserAvatarRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

/*============================== Public operators ==========================*/

TGetUserAvatarRequestData &TGetUserAvatarRequestData::operator =(const TGetUserAvatarRequestData &other)
{
    B_D(TGetUserAvatarRequestData);
    const TGetUserAvatarRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    return *this;
}

bool TGetUserAvatarRequestData::operator ==(const TGetUserAvatarRequestData &other) const
{
    const B_D(TGetUserAvatarRequestData);
    const TGetUserAvatarRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier;
}

bool TGetUserAvatarRequestData::operator !=(const TGetUserAvatarRequestData &other) const
{
    return !(*this == other);
}

TGetUserAvatarRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarRequestData &data)
{
    const TGetUserAvatarRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserAvatarRequestData &data)
{
    TGetUserAvatarRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserAvatarRequestData &/*data*/)
{
    //const TGetUserAvatarRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserAvatarRequestData(" << ")";
    return dbg.space();
}
