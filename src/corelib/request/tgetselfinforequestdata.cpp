#include "tgetselfinforequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSelfInfoRequestDataPrivate ==============
============================================================================*/

class TGetSelfInfoRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSelfInfoRequestData)
public:
    bool includeAvatar;
public:
    explicit TGetSelfInfoRequestDataPrivate(TGetSelfInfoRequestData *q);
    ~TGetSelfInfoRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSelfInfoRequestDataPrivate)
};


/*============================================================================
================================ TGetSelfInfoRequestDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetSelfInfoRequestDataPrivate::TGetSelfInfoRequestDataPrivate(TGetSelfInfoRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetSelfInfoRequestDataPrivate::~TGetSelfInfoRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSelfInfoRequestDataPrivate::init()
{
    includeAvatar = false;
}

/*============================================================================
================================ TGetSelfInfoRequestData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSelfInfoRequestData::TGetSelfInfoRequestData() :
    BBase(*new TGetSelfInfoRequestDataPrivate(this))
{
    d_func()->init();
}

TGetSelfInfoRequestData::TGetSelfInfoRequestData(const TGetSelfInfoRequestData &other) :
    BBase(*new TGetSelfInfoRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSelfInfoRequestData::~TGetSelfInfoRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetSelfInfoRequestData::clear()
{
    d_func()->includeAvatar = false;
}

bool TGetSelfInfoRequestData::includeAvatar() const
{
    return d_func()->includeAvatar;
}

void TGetSelfInfoRequestData::setIncludeAvatar(bool include)
{
    d_func()->includeAvatar = include;
}

/*============================== Public operators ==========================*/

TGetSelfInfoRequestData &TGetSelfInfoRequestData::operator =(const TGetSelfInfoRequestData &other)
{
    B_D(TGetSelfInfoRequestData);
    const TGetSelfInfoRequestDataPrivate *dd = other.d_func();
    d->includeAvatar = dd->includeAvatar;
    return *this;
}

bool TGetSelfInfoRequestData::operator ==(const TGetSelfInfoRequestData &other) const
{
    const B_D(TGetSelfInfoRequestData);
    const TGetSelfInfoRequestDataPrivate *dd = other.d_func();
    return d->includeAvatar == dd->includeAvatar;
}

bool TGetSelfInfoRequestData::operator !=(const TGetSelfInfoRequestData &other) const
{
    return !(*this == other);
}

TGetSelfInfoRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoRequestData &data)
{
    const TGetSelfInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("include_avatar", d->includeAvatar);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSelfInfoRequestData &data)
{
    TGetSelfInfoRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->includeAvatar = m.value("include_avatar").toBool();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSelfInfoRequestData &/*data*/)
{
    //const TGetSelfInfoRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSelfInfoRequestData(" << ")";
    return dbg.space();
}
