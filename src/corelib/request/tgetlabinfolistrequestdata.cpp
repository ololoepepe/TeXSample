#include "tgetlabinfolistrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLabInfoListRequestDataPrivate ===========
============================================================================*/

class TGetLabInfoListRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLabInfoListRequestData)
public:
    explicit TGetLabInfoListRequestDataPrivate(TGetLabInfoListRequestData *q);
    ~TGetLabInfoListRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLabInfoListRequestDataPrivate)
};

/*============================================================================
================================ TGetLabInfoListRequestDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabInfoListRequestDataPrivate::TGetLabInfoListRequestDataPrivate(TGetLabInfoListRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetLabInfoListRequestDataPrivate::~TGetLabInfoListRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabInfoListRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLabInfoListRequestData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabInfoListRequestData::TGetLabInfoListRequestData() :
    BBase(*new TGetLabInfoListRequestDataPrivate(this))
{
    d_func()->init();
}

TGetLabInfoListRequestData::TGetLabInfoListRequestData(const TGetLabInfoListRequestData &other) :
    BBase(*new TGetLabInfoListRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLabInfoListRequestData::~TGetLabInfoListRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetLabInfoListRequestData &TGetLabInfoListRequestData::operator =(
        const TGetLabInfoListRequestData &/*other*/)
{
    //B_D(TGetLabInfoListRequestData);
    //const TGetLabInfoListRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetLabInfoListRequestData::operator ==(const TGetLabInfoListRequestData &/*other*/) const
{
    //const B_D(TGetLabInfoListRequestData);
    //const TGetLabInfoListRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetLabInfoListRequestData::operator !=(const TGetLabInfoListRequestData &other) const
{
    return !(*this == other);
}

TGetLabInfoListRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLabInfoListRequestData &/*data*/)
{
    //const TGetLabInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLabInfoListRequestData &/*data*/)
{
    //TGetLabInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLabInfoListRequestData &/*data*/)
{
    //const TGetLabInfoListRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLabInfoListRequestData(" << ")";
    return dbg.space();
}
