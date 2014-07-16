#include "texecutecommandreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TExecuteCommandReplyDataPrivate =============
============================================================================*/

class TExecuteCommandReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TExecuteCommandReplyData)
public:
    QVariant data;
public:
    explicit TExecuteCommandReplyDataPrivate(TExecuteCommandReplyData *q);
    ~TExecuteCommandReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TExecuteCommandReplyDataPrivate)
};

/*============================================================================
================================ TExecuteCommandReplyDataPrivate =============
============================================================================*/

/*============================== Public constructors =======================*/

TExecuteCommandReplyDataPrivate::TExecuteCommandReplyDataPrivate(TExecuteCommandReplyData *q) :
    BBasePrivate(q)
{
    //
}

TExecuteCommandReplyDataPrivate::~TExecuteCommandReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TExecuteCommandReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TExecuteCommandReplyData ====================
============================================================================*/

/*============================== Public constructors =======================*/

TExecuteCommandReplyData::TExecuteCommandReplyData() :
    BBase(*new TExecuteCommandReplyDataPrivate(this))
{
    d_func()->init();
}

TExecuteCommandReplyData::TExecuteCommandReplyData(const TExecuteCommandReplyData &other) :
    BBase(*new TExecuteCommandReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TExecuteCommandReplyData::~TExecuteCommandReplyData()
{
    //
}

/*============================== Public methods ============================*/

QVariant TExecuteCommandReplyData::data() const
{
    return d_func()->data;
}

void TExecuteCommandReplyData::setData(const QVariant &data)
{
    d_func()->data = data;
}

/*============================== Public operators ==========================*/

TExecuteCommandReplyData &TExecuteCommandReplyData::operator =(const TExecuteCommandReplyData &other)
{
    B_D(TExecuteCommandReplyData);
    const TExecuteCommandReplyDataPrivate *dd = other.d_func();
    d->data = dd->data;
    return *this;
}

bool TExecuteCommandReplyData::operator ==(const TExecuteCommandReplyData &other) const
{
    const B_D(TExecuteCommandReplyData);
    const TExecuteCommandReplyDataPrivate *dd = other.d_func();
    return d->data == dd->data;
}

bool TExecuteCommandReplyData::operator !=(const TExecuteCommandReplyData &other) const
{
    return !(*this == other);
}

TExecuteCommandReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TExecuteCommandReplyData &data)
{
    const TExecuteCommandReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("data", d->data);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TExecuteCommandReplyData &data)
{
    TExecuteCommandReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->data = m.value("data");
    return stream;
}

QDebug operator <<(QDebug dbg, const TExecuteCommandReplyData &/*data*/)
{
    //const TExecuteCommandReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TExecuteCommandReplyData(" << ")";
    return dbg.space();
}
