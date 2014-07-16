#include "trecoveraccountreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRecoverAccountReplyDataPrivate =============
============================================================================*/

class TRecoverAccountReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRecoverAccountReplyData)
public:
    explicit TRecoverAccountReplyDataPrivate(TRecoverAccountReplyData *q);
    ~TRecoverAccountReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRecoverAccountReplyDataPrivate)
};

/*============================================================================
================================ TRecoverAccountReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TRecoverAccountReplyDataPrivate::TRecoverAccountReplyDataPrivate(TRecoverAccountReplyData *q) :
    BBasePrivate(q)
{
    //
}

TRecoverAccountReplyDataPrivate::~TRecoverAccountReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRecoverAccountReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRecoverAccountReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoverAccountReplyData::TRecoverAccountReplyData() :
    BBase(*new TRecoverAccountReplyDataPrivate(this))
{
    d_func()->init();
}

TRecoverAccountReplyData::TRecoverAccountReplyData(const TRecoverAccountReplyData &other) :
    BBase(*new TRecoverAccountReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRecoverAccountReplyData::~TRecoverAccountReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TRecoverAccountReplyData &TRecoverAccountReplyData::operator =(const TRecoverAccountReplyData &/*other*/)
{
    //B_D(TRecoverAccountReplyData);
    //const TRecoverAccountReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TRecoverAccountReplyData::operator ==(const TRecoverAccountReplyData &/*other*/) const
{
    //const B_D(TRecoverAccountReplyData);
    //const TRecoverAccountReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TRecoverAccountReplyData::operator !=(const TRecoverAccountReplyData &other) const
{
    return !(*this == other);
}

TRecoverAccountReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRecoverAccountReplyData &/*data*/)
{
    //const TRecoverAccountReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRecoverAccountReplyData &/*data*/)
{
    //TRecoverAccountReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TRecoverAccountReplyData &/*data*/)
{
    //const TRecoverAccountReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TRecoverAccountReplyData(" << ")";
    return dbg.space();
}
