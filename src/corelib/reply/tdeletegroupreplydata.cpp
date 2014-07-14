#include "tdeletegroupreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteGroupReplyDataPrivate ================
============================================================================*/

class TDeleteGroupReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteGroupReplyData)
public:
    explicit TDeleteGroupReplyDataPrivate(TDeleteGroupReplyData *q);
    ~TDeleteGroupReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteGroupReplyDataPrivate)
};


/*============================================================================
================================ TDeleteGroupReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteGroupReplyDataPrivate::TDeleteGroupReplyDataPrivate(TDeleteGroupReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteGroupReplyDataPrivate::~TDeleteGroupReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteGroupReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteGroupReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteGroupReplyData::TDeleteGroupReplyData() :
    BBase(*new TDeleteGroupReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteGroupReplyData::TDeleteGroupReplyData(const TDeleteGroupReplyData &other) :
    BBase(*new TDeleteGroupReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteGroupReplyData::~TDeleteGroupReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TDeleteGroupReplyData &TDeleteGroupReplyData::operator =(const TDeleteGroupReplyData &/*other*/)
{
    //B_D(TDeleteGroupReplyData);
    //const TDeleteGroupReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TDeleteGroupReplyData::operator ==(const TDeleteGroupReplyData &/*other*/) const
{
    //const B_D(TDeleteGroupReplyData);
    //const TDeleteGroupReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TDeleteGroupReplyData::operator !=(const TDeleteGroupReplyData &other) const
{
    return !(*this == other);
}

TDeleteGroupReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteGroupReplyData &/*data*/)
{
    //const TDeleteGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteGroupReplyData &/*data*/)
{
    //TDeleteGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteGroupReplyData &/*data*/)
{
    //const TDeleteGroupReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteGroupReplyData(" << ")";
    return dbg.space();
}
