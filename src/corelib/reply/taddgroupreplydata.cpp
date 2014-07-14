#include "taddgroupreplydata.h"

#include "tgroupinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddGroupReplyDataPrivate ===================
============================================================================*/

class TAddGroupReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddGroupReplyData)
public:
    TGroupInfo groupInfo;
public:
    explicit TAddGroupReplyDataPrivate(TAddGroupReplyData *q);
    ~TAddGroupReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddGroupReplyDataPrivate)
};


/*============================================================================
================================ TAddGroupReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TAddGroupReplyDataPrivate::TAddGroupReplyDataPrivate(TAddGroupReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAddGroupReplyDataPrivate::~TAddGroupReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddGroupReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddGroupReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddGroupReplyData::TAddGroupReplyData() :
    BBase(*new TAddGroupReplyDataPrivate(this))
{
    d_func()->init();
}

TAddGroupReplyData::TAddGroupReplyData(const TAddGroupReplyData &other) :
    BBase(*new TAddGroupReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddGroupReplyData::~TAddGroupReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAddGroupReplyData::setGroupInfo(const TGroupInfo &info)
{
    d_func()->groupInfo = info;
}

TGroupInfo TAddGroupReplyData::groupInfo() const
{
    return d_func()->groupInfo;
}

/*============================== Public operators ==========================*/

TAddGroupReplyData &TAddGroupReplyData::operator =(const TAddGroupReplyData &other)
{
    B_D(TAddGroupReplyData);
    const TAddGroupReplyDataPrivate *dd = other.d_func();
    d->groupInfo = dd->groupInfo;
    return *this;
}

bool TAddGroupReplyData::operator ==(const TAddGroupReplyData &other) const
{
    const B_D(TAddGroupReplyData);
    const TAddGroupReplyDataPrivate *dd = other.d_func();
    return d->groupInfo == dd->groupInfo;
}

bool TAddGroupReplyData::operator !=(const TAddGroupReplyData &other) const
{
    return !(*this == other);
}

TAddGroupReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddGroupReplyData &data)
{
    const TAddGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("group_info", d->groupInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddGroupReplyData &data)
{
    TAddGroupReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->groupInfo = m.value("group_info").value<TGroupInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddGroupReplyData &/*data*/)
{
    //const TAddGroupReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddGroupReplyData(" << ")";
    return dbg.space();
}
