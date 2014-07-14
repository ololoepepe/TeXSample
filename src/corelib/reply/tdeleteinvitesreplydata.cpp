#include "tdeleteinvitesreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TDeleteInvitesReplyDataPrivate ==============
============================================================================*/

class TDeleteInvitesReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TDeleteInvitesReplyData)
public:
    quint32 count;
public:
    explicit TDeleteInvitesReplyDataPrivate(TDeleteInvitesReplyData *q);
    ~TDeleteInvitesReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TDeleteInvitesReplyDataPrivate)
};


/*============================================================================
================================ TDeleteInvitesReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesReplyDataPrivate::TDeleteInvitesReplyDataPrivate(TDeleteInvitesReplyData *q) :
    BBasePrivate(q)
{
    //
}

TDeleteInvitesReplyDataPrivate::~TDeleteInvitesReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TDeleteInvitesReplyDataPrivate::init()
{
    count = 0;
}

/*============================================================================
================================ TDeleteInvitesReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TDeleteInvitesReplyData::TDeleteInvitesReplyData() :
    BBase(*new TDeleteInvitesReplyDataPrivate(this))
{
    d_func()->init();
}

TDeleteInvitesReplyData::TDeleteInvitesReplyData(const TDeleteInvitesReplyData &other) :
    BBase(*new TDeleteInvitesReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TDeleteInvitesReplyData::~TDeleteInvitesReplyData()
{
    //
}

/*============================== Public methods ============================*/

quint32 TDeleteInvitesReplyData::count() const
{
    return d_func()->count;
}

void TDeleteInvitesReplyData::setCount(quint32 count)
{
    d_func()->count = count;
}

/*============================== Public operators ==========================*/

TDeleteInvitesReplyData &TDeleteInvitesReplyData::operator =(const TDeleteInvitesReplyData &other)
{
    B_D(TDeleteInvitesReplyData);
    const TDeleteInvitesReplyDataPrivate *dd = other.d_func();
    d->count = dd->count;
    return *this;
}

bool TDeleteInvitesReplyData::operator ==(const TDeleteInvitesReplyData &other) const
{
    const B_D(TDeleteInvitesReplyData);
    const TDeleteInvitesReplyDataPrivate *dd = other.d_func();
    return d->count == dd->count;
}

bool TDeleteInvitesReplyData::operator !=(const TDeleteInvitesReplyData &other) const
{
    return !(*this == other);
}

TDeleteInvitesReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TDeleteInvitesReplyData &data)
{
    const TDeleteInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("count", d->count);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TDeleteInvitesReplyData &data)
{
    TDeleteInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->count = m.value("count").toUInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TDeleteInvitesReplyData &/*data*/)
{
    //const TDeleteInvitesReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TDeleteInvitesReplyData(" << ")";
    return dbg.space();
}
