#include "teditlabreplydata.h"

#include "tlabinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditLabReplyDataPrivate ====================
============================================================================*/

class TEditLabReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditLabReplyData)
public:
    TLabInfo labInfo;
public:
    explicit TEditLabReplyDataPrivate(TEditLabReplyData *q);
    ~TEditLabReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditLabReplyDataPrivate)
};

/*============================================================================
================================ TEditLabReplyDataPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TEditLabReplyDataPrivate::TEditLabReplyDataPrivate(TEditLabReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditLabReplyDataPrivate::~TEditLabReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditLabReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditLabReplyData ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditLabReplyData::TEditLabReplyData() :
    BBase(*new TEditLabReplyDataPrivate(this))
{
    d_func()->init();
}

TEditLabReplyData::TEditLabReplyData(const TEditLabReplyData &other) :
    BBase(*new TEditLabReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditLabReplyData::~TEditLabReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditLabReplyData::setLabInfo(const TLabInfo &info)
{
    d_func()->labInfo = info;
}

TLabInfo TEditLabReplyData::labInfo() const
{
    return d_func()->labInfo;
}

/*============================== Public operators ==========================*/

TEditLabReplyData &TEditLabReplyData::operator =(const TEditLabReplyData &other)
{
    B_D(TEditLabReplyData);
    const TEditLabReplyDataPrivate *dd = other.d_func();
    d->labInfo = dd->labInfo;
    return *this;
}

bool TEditLabReplyData::operator ==(const TEditLabReplyData &other) const
{
    const B_D(TEditLabReplyData);
    const TEditLabReplyDataPrivate *dd = other.d_func();
    return d->labInfo == dd->labInfo;
}

bool TEditLabReplyData::operator !=(const TEditLabReplyData &other) const
{
    return !(*this == other);
}

TEditLabReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditLabReplyData &data)
{
    const TEditLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("lab_info", d->labInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditLabReplyData &data)
{
    TEditLabReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->labInfo = m.value("lab_info").value<TLabInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditLabReplyData &/*data*/)
{
    //const TEditLabReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditLabReplyData(" << ")";
    return dbg.space();
}
