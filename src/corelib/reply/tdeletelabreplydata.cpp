#include "tdeletelabreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteLabReplyDataPrivate ==============
============================================================================*/

class TDeleteLabReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteLabReplyData)
public:
    explicit TDeleteLabReplyDataPrivate(TDeleteLabReplyData *q);
    ~TDeleteLabReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteLabReplyDataPrivate)
};

/*============================================================================
================================ TDeleteLabReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteLabReplyDataPrivate::TDeleteLabReplyDataPrivate(TDeleteLabReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteLabReplyDataPrivate::~TDeleteLabReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteLabReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TDeleteLabReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteLabReplyData::TDeleteLabReplyData() :
    BBase(*new TDeleteLabReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteLabReplyData::TDeleteLabReplyData(const TDeleteLabReplyData &other) :
    BBase(*new TDeleteLabReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteLabReplyData::~TDeleteLabReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TDeleteLabReplyData &TDeleteLabReplyData::operator =(const TDeleteLabReplyData &/*other*/)
{
    //B_D(TDeleteLabReplyData);
    //const TDeleteLabReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TDeleteLabReplyData::operator ==(const TDeleteLabReplyData &/*other*/) const
{
    //const B_D(TDeleteLabReplyData);
    //const TDeleteLabReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TDeleteLabReplyData::operator !=(const TDeleteLabReplyData &other) const
{
    return !(*this == other);
}

TDeleteLabReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteLabReplyData &/*data*/)
{
    //const TDeleteLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteLabReplyData &/*data*/)
{
    //TDeleteLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteLabReplyData &/*data*/)
{
    //const TDeleteLabReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteLabReplyData(" << ")";
    return dbg.space();
}
