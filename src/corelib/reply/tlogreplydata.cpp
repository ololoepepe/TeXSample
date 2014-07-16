#include "tlogreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLogReplyDataPrivate ========================
============================================================================*/

class TLogReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLogReplyData)
public:
    explicit TLogReplyDataPrivate(TLogReplyData *q);
    ~TLogReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLogReplyDataPrivate)
};

/*============================================================================
================================ TLogReplyDataPrivate ========================
============================================================================*/

/*============================== Public constructors =======================*/

TLogReplyDataPrivate::TLogReplyDataPrivate(TLogReplyData *q) :
    BBasePrivate(q)
{
    //
}

TLogReplyDataPrivate::~TLogReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLogReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TLogReplyData ===============================
============================================================================*/

/*============================== Public constructors =======================*/

TLogReplyData::TLogReplyData() :
    BBase(*new TLogReplyDataPrivate(this))
{
    d_func()->init();
}

TLogReplyData::TLogReplyData(const TLogReplyData &other) :
    BBase(*new TLogReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLogReplyData::~TLogReplyData()
{
    //
}

/*============================== Public operators ==========================*/

TLogReplyData &TLogReplyData::operator =(const TLogReplyData &/*other*/)
{
    //B_D(TLogReplyData);
    //const TLogReplyDataPrivate *dd = other.d_func();
    return *this;
}

bool TLogReplyData::operator ==(const TLogReplyData &/*other*/) const
{
    //const B_D(TLogReplyData);
    //const TLogReplyDataPrivate *dd = other.d_func();
    return true;
}

bool TLogReplyData::operator !=(const TLogReplyData &other) const
{
    return !(*this == other);
}

TLogReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLogReplyData &/*data*/)
{
    //const TLogReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLogReplyData &/*data*/)
{
    //TLogReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TLogReplyData &/*data*/)
{
    //const TLogReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TLogReplyData(" << ")";
    return dbg.space();
}
