#include "tgetuserinforequestdata.h"

#include "tuseridentifier.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoRequestDataPrivate ==============
============================================================================*/

class TGetUserInfoRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoRequestData)
public:
    TUserIdentifier identifier;
    bool includeAvatar;
public:
    explicit TGetUserInfoRequestDataPrivate(TGetUserInfoRequestData *q);
    ~TGetUserInfoRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoRequestDataPrivate)
};

/*============================================================================
================================ TGetUserInfoRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoRequestDataPrivate::TGetUserInfoRequestDataPrivate(TGetUserInfoRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoRequestDataPrivate::~TGetUserInfoRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoRequestDataPrivate::init()
{
    includeAvatar = false;
}

/*============================================================================
================================ TGetUserInfoRequestData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoRequestData::TGetUserInfoRequestData() :
    BBase(*new TGetUserInfoRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoRequestData::TGetUserInfoRequestData(const TGetUserInfoRequestData &other) :
    BBase(*new TGetUserInfoRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoRequestData::~TGetUserInfoRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoRequestData::clear()
{
    d_func()->identifier.clear();
    d_func()->includeAvatar = false;
}

TUserIdentifier TGetUserInfoRequestData::identifier() const
{
    return d_func()->identifier;
}

bool TGetUserInfoRequestData::includeAvatar() const
{
    return d_func()->includeAvatar;
}

bool TGetUserInfoRequestData::isValid() const
{
    return d_func()->identifier.isValid();
}

void TGetUserInfoRequestData::setIdentifier(const TUserIdentifier &identifier)
{
    d_func()->identifier = identifier;
}

void TGetUserInfoRequestData::setIncludeAvatar(bool include)
{
    d_func()->includeAvatar = include;
}

/*============================== Public operators ==========================*/

TGetUserInfoRequestData &TGetUserInfoRequestData::operator =(const TGetUserInfoRequestData &other)
{
    B_D(TGetUserInfoRequestData);
    const TGetUserInfoRequestDataPrivate *dd = other.d_func();
    d->identifier = dd->identifier;
    d->includeAvatar = dd->includeAvatar;
    return *this;
}

bool TGetUserInfoRequestData::operator ==(const TGetUserInfoRequestData &other) const
{
    const B_D(TGetUserInfoRequestData);
    const TGetUserInfoRequestDataPrivate *dd = other.d_func();
    return d->identifier == dd->identifier && d->includeAvatar == dd->includeAvatar;
}

bool TGetUserInfoRequestData::operator !=(const TGetUserInfoRequestData &other) const
{
    return !(*this == other);
}

TGetUserInfoRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoRequestData &data)
{
    const TGetUserInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("identifier", d->identifier);
    m.insert("include_avatar", d->includeAvatar);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoRequestData &data)
{
    TGetUserInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->identifier = m.value("identifier").value<TUserIdentifier>();
    d->includeAvatar = m.value("include_avatar").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoRequestData &/*data*/)
{
    //const TGetUserInfoRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoRequestData(" << ")";
    return dbg.space();
}
