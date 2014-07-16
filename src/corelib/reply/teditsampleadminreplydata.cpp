#include "teditsampleadminreplydata.h"

#include "tsampleinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSampleAdminReplyDataPrivate ============
============================================================================*/

class TEditSampleAdminReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSampleAdminReplyData)
public:
    TSampleInfo sampleInfo;
public:
    explicit TEditSampleAdminReplyDataPrivate(TEditSampleAdminReplyData *q);
    ~TEditSampleAdminReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSampleAdminReplyDataPrivate)
};

/*============================================================================
================================ TEditSampleAdminReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleAdminReplyDataPrivate::TEditSampleAdminReplyDataPrivate(TEditSampleAdminReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditSampleAdminReplyDataPrivate::~TEditSampleAdminReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleAdminReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditSampleAdminReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSampleAdminReplyData::TEditSampleAdminReplyData() :
    BBase(*new TEditSampleAdminReplyDataPrivate(this))
{
    d_func()->init();
}

TEditSampleAdminReplyData::TEditSampleAdminReplyData(const TEditSampleAdminReplyData &other) :
    BBase(*new TEditSampleAdminReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSampleAdminReplyData::~TEditSampleAdminReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditSampleAdminReplyData::setSampleInfo(const TSampleInfo &info)
{
    d_func()->sampleInfo = info;
}

TSampleInfo TEditSampleAdminReplyData::sampleInfo() const
{
    return d_func()->sampleInfo;
}

/*============================== Public operators ==========================*/

TEditSampleAdminReplyData &TEditSampleAdminReplyData::operator =(const TEditSampleAdminReplyData &other)
{
    B_D(TEditSampleAdminReplyData);
    const TEditSampleAdminReplyDataPrivate *dd = other.d_func();
    d->sampleInfo = dd->sampleInfo;
    return *this;
}

bool TEditSampleAdminReplyData::operator ==(const TEditSampleAdminReplyData &other) const
{
    const B_D(TEditSampleAdminReplyData);
    const TEditSampleAdminReplyDataPrivate *dd = other.d_func();
    return d->sampleInfo == dd->sampleInfo;
}

bool TEditSampleAdminReplyData::operator !=(const TEditSampleAdminReplyData &other) const
{
    return !(*this == other);
}

TEditSampleAdminReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminReplyData &data)
{
    const TEditSampleAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("sample_info", d->sampleInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSampleAdminReplyData &data)
{
    TEditSampleAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->sampleInfo = m.value("sample_info").value<TSampleInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSampleAdminReplyData &/*data*/)
{
    //const TEditSampleAdminReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSampleAdminReplyData(" << ")";
    return dbg.space();
}
