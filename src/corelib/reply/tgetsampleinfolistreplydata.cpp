#include "tgetsampleinfolistreplydata.h"

#include "tidlist.h"
#include "tsampleinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleInfoListReplyDataPrivate ==========
============================================================================*/

class TGetSampleInfoListReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleInfoListReplyData)
public:
    TIdList deletedSamples;
    TSampleInfoList newSamples;
public:
    explicit TGetSampleInfoListReplyDataPrivate(TGetSampleInfoListReplyData *q);
    ~TGetSampleInfoListReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleInfoListReplyDataPrivate)
};

/*============================================================================
================================ TGetSampleInfoListReplyDataPrivate ==========
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListReplyDataPrivate::TGetSampleInfoListReplyDataPrivate(TGetSampleInfoListReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleInfoListReplyDataPrivate::~TGetSampleInfoListReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleInfoListReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSampleInfoListReplyData =================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleInfoListReplyData::TGetSampleInfoListReplyData() :
    BBase(*new TGetSampleInfoListReplyDataPrivate(this))
{
    d_func()->init();
}

TGetSampleInfoListReplyData::TGetSampleInfoListReplyData(const TGetSampleInfoListReplyData &other) :
    BBase(*new TGetSampleInfoListReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleInfoListReplyData::~TGetSampleInfoListReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TGetSampleInfoListReplyData::deletedSamples() const
{
    return d_func()->deletedSamples;
}

TSampleInfoList TGetSampleInfoListReplyData::newSamples() const
{
    return d_func()->newSamples;
}

void TGetSampleInfoListReplyData::setDeletedSamples(const TIdList &deletedSamples)
{
    B_D(TGetSampleInfoListReplyData);
    d->deletedSamples = deletedSamples;
    d->deletedSamples.removeAll(0);
    bRemoveDuplicates(d->deletedSamples);
}

void TGetSampleInfoListReplyData::setNewSamples(const TSampleInfoList &newSamples)
{
    d_func()->newSamples = newSamples;
}

/*============================== Public operators ==========================*/

TGetSampleInfoListReplyData &TGetSampleInfoListReplyData::operator =(const TGetSampleInfoListReplyData &other)
{
    B_D(TGetSampleInfoListReplyData);
    const TGetSampleInfoListReplyDataPrivate *dd = other.d_func();
    d->deletedSamples = dd->deletedSamples;
    d->newSamples = dd->newSamples;
    return *this;
}

bool TGetSampleInfoListReplyData::operator ==(const TGetSampleInfoListReplyData &other) const
{
    const B_D(TGetSampleInfoListReplyData);
    const TGetSampleInfoListReplyDataPrivate *dd = other.d_func();
    return d->deletedSamples == dd->deletedSamples && d->newSamples == dd->newSamples;
}

bool TGetSampleInfoListReplyData::operator !=(const TGetSampleInfoListReplyData &other) const
{
    return !(*this == other);
}

TGetSampleInfoListReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleInfoListReplyData &data)
{
    const TGetSampleInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("deleted_samples", d->deletedSamples);
    m.insert("new_samples", d->newSamples);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleInfoListReplyData &data)
{
    TGetSampleInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->deletedSamples = m.value("deleted_samples").value<TIdList>();
    d->newSamples = m.value("new_samples").value<TSampleInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleInfoListReplyData &/*data*/)
{
    //const TGetSampleInfoListReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleInfoListReplyData(" << ")";
    return dbg.space();
}
