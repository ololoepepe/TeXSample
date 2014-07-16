#include "tsubscribereplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TSubscribeReplyDataPrivate ==================
============================================================================*/

class TSubscribeReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSubscribeReplyData)
public:
    explicit TSubscribeReplyDataPrivate(TSubscribeReplyData *q);
    ~TSubscribeReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TSubscribeReplyDataPrivate)
};

/*============================================================================
================================ TSubscribeReplyDataPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TSubscribeReplyDataPrivate::TSubscribeReplyDataPrivate(TSubscribeReplyData *q) :
    BBasePrivate(q)
{
    //
}

TSubscribeReplyDataPrivate::~TSubscribeReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSubscribeReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TSubscribeReplyData =========================
============================================================================*/

/*============================== Public constructors =======================*/

TSubscribeReplyData::TSubscribeReplyData() :
    BBase(*new TSubscribeReplyDataPrivate(this))
{
    d_func()->init();
}

TSubscribeReplyData::TSubscribeReplyData(const TSubscribeReplyData &other) :
    BBase(*new TSubscribeReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSubscribeReplyData::~TSubscribeReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TSubscribeReplyData &TSubscribeReplyData::operator =(const TSubscribeReplyData &/*other*/)
{
    //B_D(TSubscribeReplyData);
    //const TSubscribeReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TSubscribeReplyData::operator ==(const TSubscribeReplyData &/*other*/) const
{
    //const B_D(TSubscribeReplyData);
    //const TSubscribeReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TSubscribeReplyData::operator !=(const TSubscribeReplyData &other) const
{
    return !(*this == other);
}

TSubscribeReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TSubscribeReplyData &/*data*/)
{
    //const TSubscribeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TSubscribeReplyData &/*data*/)
{
    //TSubscribeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TSubscribeReplyData &/*data*/)
{
    //const TSubscribeReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TSubscribeReplyData(" << ")";
    return dbg.space();
}
