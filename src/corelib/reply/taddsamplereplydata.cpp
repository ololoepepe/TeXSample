#include "taddsamplereplydata.h"

#include "tsampleinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddSampleReplyDataPrivate ==================
============================================================================*/

class TAddSampleReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddSampleReplyData)
public:
    TSampleInfo sampleInfo;
public:
    explicit TAddSampleReplyDataPrivate(TAddSampleReplyData *q);
    ~TAddSampleReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddSampleReplyDataPrivate)
};

/*============================================================================
================================ TAddSampleReplyDataPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TAddSampleReplyDataPrivate::TAddSampleReplyDataPrivate(TAddSampleReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAddSampleReplyDataPrivate::~TAddSampleReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddSampleReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddSampleReplyData =========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddSampleReplyData::TAddSampleReplyData() :
    BBase(*new TAddSampleReplyDataPrivate(this))
{
    d_func()->init();
}

TAddSampleReplyData::TAddSampleReplyData(const TAddSampleReplyData &other) :
    BBase(*new TAddSampleReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddSampleReplyData::~TAddSampleReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAddSampleReplyData::setSampleInfo(const TSampleInfo &info)
{
    d_func()->sampleInfo = info;
}

TSampleInfo TAddSampleReplyData::sampleInfo() const
{
    return d_func()->sampleInfo;
}

/*============================== Public operators ==========================*/

TAddSampleReplyData &TAddSampleReplyData::operator =(const TAddSampleReplyData &other)
{
    B_D(TAddSampleReplyData);
    const TAddSampleReplyDataPrivate *dd = other.d_func();
    d->sampleInfo = dd->sampleInfo;
    return *this;
}

bool TAddSampleReplyData::operator ==(const TAddSampleReplyData &other) const
{
    const B_D(TAddSampleReplyData);
    const TAddSampleReplyDataPrivate *dd = other.d_func();
    return d->sampleInfo == dd->sampleInfo;
}

bool TAddSampleReplyData::operator !=(const TAddSampleReplyData &other) const
{
    return !(*this == other);
}

TAddSampleReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddSampleReplyData &data)
{
    const TAddSampleReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("sample_info", d->sampleInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddSampleReplyData &data)
{
    TAddSampleReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->sampleInfo = m.value("sample_info").value<TSampleInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddSampleReplyData &/*data*/)
{
    //const TAddSampleReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddSampleReplyData(" << ")";
    return dbg.space();
}
