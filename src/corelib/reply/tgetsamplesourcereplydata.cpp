#include "tgetsamplesourcereplydata.h"

#include "ttexproject.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSampleSourceReplyDataPrivate ============
============================================================================*/

class TGetSampleSourceReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSampleSourceReplyData)
public:
    TTexProject project;
public:
    explicit TGetSampleSourceReplyDataPrivate(TGetSampleSourceReplyData *q);
    ~TGetSampleSourceReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSampleSourceReplyDataPrivate)
};

/*============================================================================
================================ TGetSampleSourceReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleSourceReplyDataPrivate::TGetSampleSourceReplyDataPrivate(TGetSampleSourceReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetSampleSourceReplyDataPrivate::~TGetSampleSourceReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSampleSourceReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSampleSourceReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSampleSourceReplyData::TGetSampleSourceReplyData() :
    BBase(*new TGetSampleSourceReplyDataPrivate(this))
{
    d_func()->init();
}

TGetSampleSourceReplyData::TGetSampleSourceReplyData(const TGetSampleSourceReplyData &other) :
    BBase(*new TGetSampleSourceReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSampleSourceReplyData::~TGetSampleSourceReplyData()
{
    //
}

/*============================== Public methods ============================*/

TTexProject &TGetSampleSourceReplyData::project()
{
    return d_func()->project;
}

const TTexProject &TGetSampleSourceReplyData::project() const
{
    return d_func()->project;
}

void TGetSampleSourceReplyData::setProject(const TTexProject &project)
{
    d_func()->project = project;
}

/*============================== Public operators ==========================*/

TGetSampleSourceReplyData &TGetSampleSourceReplyData::operator =(const TGetSampleSourceReplyData &other)
{
    B_D(TGetSampleSourceReplyData);
    const TGetSampleSourceReplyDataPrivate *dd = other.d_func();
    d->project = dd->project;
    return *this;
}

bool TGetSampleSourceReplyData::operator ==(const TGetSampleSourceReplyData &other) const
{
    const B_D(TGetSampleSourceReplyData);
    const TGetSampleSourceReplyDataPrivate *dd = other.d_func();
    return d->project == dd->project;
}

bool TGetSampleSourceReplyData::operator !=(const TGetSampleSourceReplyData &other) const
{
    return !(*this == other);
}

TGetSampleSourceReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSampleSourceReplyData &data)
{
    const TGetSampleSourceReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("project", d->project);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSampleSourceReplyData &data)
{
    TGetSampleSourceReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->project = m.value("project").value<TTexProject>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSampleSourceReplyData &/*data*/)
{
    //const TGetSampleSourceReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSampleSourceReplyData(" << ")";
    return dbg.space();
}
