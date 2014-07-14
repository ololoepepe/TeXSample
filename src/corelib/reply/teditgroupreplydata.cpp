#include "teditgroupreplydata.h"

#include "tgroupinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditGroupReplyDataPrivate ==================
============================================================================*/

class TEditGroupReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditGroupReplyData)
public:
    TGroupInfo groupInfo;
public:
    explicit TEditGroupReplyDataPrivate(TEditGroupReplyData *q);
    ~TEditGroupReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditGroupReplyDataPrivate)
};


/*============================================================================
================================ TEditGroupReplyDataPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TEditGroupReplyDataPrivate::TEditGroupReplyDataPrivate(TEditGroupReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditGroupReplyDataPrivate::~TEditGroupReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditGroupReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditGroupReplyData =========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditGroupReplyData::TEditGroupReplyData() :
    BBase(*new TEditGroupReplyDataPrivate(this))
{
    d_func()->init();
}

TEditGroupReplyData::TEditGroupReplyData(const TEditGroupReplyData &other) :
    BBase(*new TEditGroupReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditGroupReplyData::~TEditGroupReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditGroupReplyData::setGroupInfo(const TGroupInfo &info)
{
    d_func()->groupInfo = info;
}

TGroupInfo TEditGroupReplyData::groupInfo() const
{
    return d_func()->groupInfo;
}

/*============================== Public operators ==========================*/

TEditGroupReplyData &TEditGroupReplyData::operator =(const TEditGroupReplyData &other)
{
    B_D(TEditGroupReplyData);
    const TEditGroupReplyDataPrivate *dd = other.d_func();
    d->groupInfo = dd->groupInfo;
    return *this;
}

bool TEditGroupReplyData::operator ==(const TEditGroupReplyData &other) const
{
    const B_D(TEditGroupReplyData);
    const TEditGroupReplyDataPrivate *dd = other.d_func();
    return d->groupInfo == dd->groupInfo;
}

bool TEditGroupReplyData::operator !=(const TEditGroupReplyData &other) const
{
    return !(*this == other);
}

TEditGroupReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditGroupReplyData &data)
{
    const TEditGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("group_info", d->groupInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditGroupReplyData &data)
{
    TEditGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->groupInfo = m.value("group_info").value<TGroupInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditGroupReplyData &/*data*/)
{
    //const TEditGroupReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditGroupReplyData(" << ")";
    return dbg.space();
}
