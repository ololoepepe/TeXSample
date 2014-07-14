#include "trequestrecoverycodereplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRequestRecoveryCodeReplyDataPrivate ========
============================================================================*/

class TRequestRecoveryCodeReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRequestRecoveryCodeReplyData)
public:
    explicit TRequestRecoveryCodeReplyDataPrivate(TRequestRecoveryCodeReplyData *q);
    ~TRequestRecoveryCodeReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRequestRecoveryCodeReplyDataPrivate)
};


/*============================================================================
================================ TRequestRecoveryCodeReplyDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TRequestRecoveryCodeReplyDataPrivate::TRequestRecoveryCodeReplyDataPrivate(TRequestRecoveryCodeReplyData *q) :
    BBasePrivate(q)
{
    //
}

TRequestRecoveryCodeReplyDataPrivate::~TRequestRecoveryCodeReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRequestRecoveryCodeReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRequestRecoveryCodeReplyData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TRequestRecoveryCodeReplyData::TRequestRecoveryCodeReplyData() :
    BBase(*new TRequestRecoveryCodeReplyDataPrivate(this))
{
    d_func()->init();
}

TRequestRecoveryCodeReplyData::TRequestRecoveryCodeReplyData(const TRequestRecoveryCodeReplyData &other) :
    BBase(*new TRequestRecoveryCodeReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRequestRecoveryCodeReplyData::~TRequestRecoveryCodeReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TRequestRecoveryCodeReplyData &TRequestRecoveryCodeReplyData::operator =(
        const TRequestRecoveryCodeReplyData &/*other*/)
{
    //B_D(TRequestRecoveryCodeReplyData);
    //const TRequestRecoveryCodeReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TRequestRecoveryCodeReplyData::operator ==(const TRequestRecoveryCodeReplyData &/*other*/) const
{
    //const B_D(TRequestRecoveryCodeReplyData);
    //const TRequestRecoveryCodeReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TRequestRecoveryCodeReplyData::operator !=(const TRequestRecoveryCodeReplyData &other) const
{
    return !(*this == other);
}

TRequestRecoveryCodeReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeReplyData &/*data*/)
{
    //const TRequestRecoveryCodeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeReplyData &/*data*/)
{
    //TRequestRecoveryCodeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeReplyData &/*data*/)
{
    //const TRequestRecoveryCodeReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TRequestRecoveryCodeReplyData(" << ")";
    return dbg.space();
}
