#include "tchangeemailreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TChangeEmailReplyDataPrivate ================
============================================================================*/

class TChangeEmailReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TChangeEmailReplyData)
public:
    explicit TChangeEmailReplyDataPrivate(TChangeEmailReplyData *q);
    ~TChangeEmailReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TChangeEmailReplyDataPrivate)
};

/*============================================================================
================================ TChangeEmailReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TChangeEmailReplyDataPrivate::TChangeEmailReplyDataPrivate(TChangeEmailReplyData *q) :
    BBasePrivate(q)
{
    //
}

TChangeEmailReplyDataPrivate::~TChangeEmailReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TChangeEmailReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TChangeEmailReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TChangeEmailReplyData::TChangeEmailReplyData() :
    BBase(*new TChangeEmailReplyDataPrivate(this))
{
    d_func()->init();
}

TChangeEmailReplyData::TChangeEmailReplyData(const TChangeEmailReplyData &other) :
    BBase(*new TChangeEmailReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TChangeEmailReplyData::~TChangeEmailReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TChangeEmailReplyData &TChangeEmailReplyData::operator =(const TChangeEmailReplyData &/*other*/)
{
    //B_D(TChangeEmailReplyData);
    //const TChangeEmailReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TChangeEmailReplyData::operator ==(const TChangeEmailReplyData &/*other*/) const
{
    //const B_D(TChangeEmailReplyData);
    //const TChangeEmailReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TChangeEmailReplyData::operator !=(const TChangeEmailReplyData &other) const
{
    return !(*this == other);
}

TChangeEmailReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TChangeEmailReplyData &/*data*/)
{
    //const TChangeEmailReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TChangeEmailReplyData &/*data*/)
{
    //TChangeEmailReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TChangeEmailReplyData &/*data*/)
{
    //const TChangeEmailReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TChangeEmailReplyData(" << ")";
    return dbg.space();
}
