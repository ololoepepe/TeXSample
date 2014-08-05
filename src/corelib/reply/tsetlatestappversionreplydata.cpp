#include "tsetlatestappversionreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSetLatestAppVersionReplyDataPrivate ========
============================================================================*/

class TSetLatestAppVersionReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSetLatestAppVersionReplyData)
public:
    explicit TSetLatestAppVersionReplyDataPrivate(TSetLatestAppVersionReplyData *q);
    ~TSetLatestAppVersionReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSetLatestAppVersionReplyDataPrivate)
};


/*============================================================================
================================ TSetLatestAppVersionReplyDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TSetLatestAppVersionReplyDataPrivate::TSetLatestAppVersionReplyDataPrivate(TSetLatestAppVersionReplyData *q) :
    BBasePrivate(q)
{
    //
}

TSetLatestAppVersionReplyDataPrivate::~TSetLatestAppVersionReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSetLatestAppVersionReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TSetLatestAppVersionReplyData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TSetLatestAppVersionReplyData::TSetLatestAppVersionReplyData() :
    BBase(*new TSetLatestAppVersionReplyDataPrivate(this))
{
    d_func()->init();
}

TSetLatestAppVersionReplyData::TSetLatestAppVersionReplyData(const TSetLatestAppVersionReplyData &other) :
    BBase(*new TSetLatestAppVersionReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSetLatestAppVersionReplyData::~TSetLatestAppVersionReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TSetLatestAppVersionReplyData &TSetLatestAppVersionReplyData::operator =(
        const TSetLatestAppVersionReplyData &/*other*/)
{
    //B_D(TSetLatestAppVersionReplyData);
    //const TSetLatestAppVersionReplyDataPrivate *dd = other.d_func();
    //
    return *this;
}

bool TSetLatestAppVersionReplyData::operator ==(const TSetLatestAppVersionReplyData &/*other*/) const
{
    //const B_D(TSetLatestAppVersionReplyData);
    //const TSetLatestAppVersionReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TSetLatestAppVersionReplyData::operator !=(const TSetLatestAppVersionReplyData &other) const
{
    return !(*this == other);
}

TSetLatestAppVersionReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSetLatestAppVersionReplyData &/*data*/)
{
    //const TSetLatestAppVersionReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    //
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSetLatestAppVersionReplyData &/*data*/)
{
    //TSetLatestAppVersionReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    //
    return stream;
}

QDebug operator <<(QDebug dbg, const TSetLatestAppVersionReplyData &/*data*/)
{
    //const TSetLatestAppVersionReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TSetLatestAppVersionReplyData(" << ")";
    return dbg.space();
}
