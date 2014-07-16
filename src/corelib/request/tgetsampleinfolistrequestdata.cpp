#include "tgetsampleinfolistrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleInfoListRequestDataPrivate ========
============================================================================*/

class TGetSampleInfoListRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleInfoListRequestData)
public:
    explicit TGetSampleInfoListRequestDataPrivate(TGetSampleInfoListRequestData *q);
    ~TGetSampleInfoListRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleInfoListRequestDataPrivate)
};

/*============================================================================
================================ TGetSampleInfoListRequestDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListRequestDataPrivate::TGetSampleInfoListRequestDataPrivate(TGetSampleInfoListRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleInfoListRequestDataPrivate::~TGetSampleInfoListRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleInfoListRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSampleInfoListRequestData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListRequestData::TGetSampleInfoListRequestData() :
    BBase(*new TGetSampleInfoListRequestDataPrivate(this))
{
    d_func()->init();
}

TGetSampleInfoListRequestData::TGetSampleInfoListRequestData(const TGetSampleInfoListRequestData &other) :
    BBase(*new TGetSampleInfoListRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleInfoListRequestData::~TGetSampleInfoListRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetSampleInfoListRequestData &TGetSampleInfoListRequestData::operator =(
        const TGetSampleInfoListRequestData &/*other*/)
{
    //B_D(TGetSampleInfoListRequestData);
    //const TGetSampleInfoListRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetSampleInfoListRequestData::operator ==(const TGetSampleInfoListRequestData &/*other*/) const
{
    //const B_D(TGetSampleInfoListRequestData);
    //const TGetSampleInfoListRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetSampleInfoListRequestData::operator !=(const TGetSampleInfoListRequestData &other) const
{
    return !(*this == other);
}

TGetSampleInfoListRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListRequestData &/*data*/)
{
    //const TGetSampleInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListRequestData &/*data*/)
{
    //TGetSampleInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleInfoListRequestData &/*data*/)
{
    //const TGetSampleInfoListRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleInfoListRequestData(" << ")";
    return dbg.space();
}
