#include "tdeleteuserreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteUserReplyDataPrivate =================
============================================================================*/

class TDeleteUserReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteUserReplyData)
public:
    explicit TDeleteUserReplyDataPrivate(TDeleteUserReplyData *q);
    ~TDeleteUserReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteUserReplyDataPrivate)
};

/*============================================================================
================================ TDeleteUserReplyDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserReplyDataPrivate::TDeleteUserReplyDataPrivate(TDeleteUserReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteUserReplyDataPrivate::~TDeleteUserReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteUserReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteUserReplyData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteUserReplyData::TDeleteUserReplyData() :
    BBase(*new TDeleteUserReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteUserReplyData::TDeleteUserReplyData(const TDeleteUserReplyData &other) :
    BBase(*new TDeleteUserReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteUserReplyData::~TDeleteUserReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TDeleteUserReplyData &TDeleteUserReplyData::operator =(const TDeleteUserReplyData &/*other*/)
{
    //B_D(TDeleteUserReplyData);
    //const TDeleteUserReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TDeleteUserReplyData::operator ==(const TDeleteUserReplyData &/*other*/) const
{
    //const B_D(TDeleteUserReplyData);
    //const TDeleteUserReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TDeleteUserReplyData::operator !=(const TDeleteUserReplyData &other) const
{
    return !(*this == other);
}

TDeleteUserReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteUserReplyData &/*data*/)
{
    //const TDeleteUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteUserReplyData &/*data*/)
{
    //TDeleteUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteUserReplyData &/*data*/)
{
    //const TDeleteUserReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteUserReplyData(" << ")";
    return dbg.space();
}
