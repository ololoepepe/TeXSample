#include "tgetlatestappversionreplydata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BVersion>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLatestAppVersionReplyDataPrivate ========
============================================================================*/

class TGetLatestAppVersionReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLatestAppVersionReplyData)
public:
    BVersion version;
public:
    explicit TGetLatestAppVersionReplyDataPrivate(TGetLatestAppVersionReplyData *q);
    ~TGetLatestAppVersionReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLatestAppVersionReplyDataPrivate)
};

/*============================================================================
================================ TGetLatestAppVersionReplyDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TGetLatestAppVersionReplyDataPrivate::TGetLatestAppVersionReplyDataPrivate(TGetLatestAppVersionReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetLatestAppVersionReplyDataPrivate::~TGetLatestAppVersionReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLatestAppVersionReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetLatestAppVersionReplyData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TGetLatestAppVersionReplyData::TGetLatestAppVersionReplyData() :
    BBase(*new TGetLatestAppVersionReplyDataPrivate(this))
{
    d_func()->init();
}

TGetLatestAppVersionReplyData::TGetLatestAppVersionReplyData(const TGetLatestAppVersionReplyData &other) :
    BBase(*new TGetLatestAppVersionReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLatestAppVersionReplyData::~TGetLatestAppVersionReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetLatestAppVersionReplyData::setVersion(const BVersion &version)
{
    d_func()->version = version;
}

BVersion TGetLatestAppVersionReplyData::version() const
{
    return d_func()->version;
}

/*============================== Public operators ==========================*/

TGetLatestAppVersionReplyData &TGetLatestAppVersionReplyData::operator =(const TGetLatestAppVersionReplyData &other)
{
    B_D(TGetLatestAppVersionReplyData);
    const TGetLatestAppVersionReplyDataPrivate *dd = other.d_func();
    d->version = dd->version;
    return *this;
}

bool TGetLatestAppVersionReplyData::operator ==(const TGetLatestAppVersionReplyData &other) const
{
    const B_D(TGetLatestAppVersionReplyData);
    const TGetLatestAppVersionReplyDataPrivate *dd = other.d_func();
    return d->version == dd->version;
}

bool TGetLatestAppVersionReplyData::operator !=(const TGetLatestAppVersionReplyData &other) const
{
    return !(*this == other);
}

TGetLatestAppVersionReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionReplyData &data)
{
    const TGetLatestAppVersionReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("version", d->version);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionReplyData &data)
{
    TGetLatestAppVersionReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->version = m.value("version").value<BVersion>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLatestAppVersionReplyData &/*data*/)
{
    //const TGetLatestAppVersionReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLatestAppVersionReplyData(" << ")";
    return dbg.space();
}
