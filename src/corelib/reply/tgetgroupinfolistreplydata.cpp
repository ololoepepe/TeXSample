#include "tgetgroupinfolistreplydata.h"

#include "tgroupinfolist.h"
#include "tidlist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetGroupInfoListReplyDataPrivate ===========
============================================================================*/

class TGetGroupInfoListReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetGroupInfoListReplyData)
public:
    TIdList deletedGroups;
    TGroupInfoList newGroups;
public:
    explicit TGetGroupInfoListReplyDataPrivate(TGetGroupInfoListReplyData *q);
    ~TGetGroupInfoListReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetGroupInfoListReplyDataPrivate)
};


/*============================================================================
================================ TGetGroupInfoListReplyDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TGetGroupInfoListReplyDataPrivate::TGetGroupInfoListReplyDataPrivate(TGetGroupInfoListReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetGroupInfoListReplyDataPrivate::~TGetGroupInfoListReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetGroupInfoListReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetGroupInfoListReplyData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TGetGroupInfoListReplyData::TGetGroupInfoListReplyData() :
    BBase(*new TGetGroupInfoListReplyDataPrivate(this))
{
    d_func()->init();
}

TGetGroupInfoListReplyData::TGetGroupInfoListReplyData(const TGetGroupInfoListReplyData &other) :
    BBase(*new TGetGroupInfoListReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetGroupInfoListReplyData::~TGetGroupInfoListReplyData()
{
    //
}

/*============================== Public methods ============================*/

TIdList TGetGroupInfoListReplyData::deletedGroups() const
{
    return d_func()->deletedGroups;
}

TGroupInfoList TGetGroupInfoListReplyData::newGroups() const
{
    return d_func()->newGroups;
}

void TGetGroupInfoListReplyData::setDeletedGroups(const TIdList &deletedGroups)
{
    B_D(TGetGroupInfoListReplyData);
    d->deletedGroups = deletedGroups;
    d->deletedGroups.removeAll(0);
    bRemoveDuplicates(d->deletedGroups);
}

void TGetGroupInfoListReplyData::setNewGroups(const TGroupInfoList &newGroups)
{
    d_func()->newGroups = newGroups;
}

/*============================== Public operators ==========================*/

TGetGroupInfoListReplyData &TGetGroupInfoListReplyData::operator =(const TGetGroupInfoListReplyData &other)
{
    B_D(TGetGroupInfoListReplyData);
    const TGetGroupInfoListReplyDataPrivate *dd = other.d_func();
    d->deletedGroups = dd->deletedGroups;
    d->newGroups = dd->newGroups;
    return *this;
}

bool TGetGroupInfoListReplyData::operator ==(const TGetGroupInfoListReplyData &other) const
{
    const B_D(TGetGroupInfoListReplyData);
    const TGetGroupInfoListReplyDataPrivate *dd = other.d_func();
    return d->deletedGroups == dd->deletedGroups && d->newGroups == dd->newGroups;
}

bool TGetGroupInfoListReplyData::operator !=(const TGetGroupInfoListReplyData &other) const
{
    return !(*this == other);
}

TGetGroupInfoListReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetGroupInfoListReplyData &data)
{
    const TGetGroupInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("deleted_groups", d->deletedGroups);
    m.insert("new_groups", d->newGroups);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetGroupInfoListReplyData &data)
{
    TGetGroupInfoListReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->deletedGroups = m.value("deleted_groups").value<TIdList>();
    d->newGroups = m.value("new_groups").value<TGroupInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetGroupInfoListReplyData &/*data*/)
{
    //const TGetGroupInfoListReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetGroupInfoListReplyData(" << ")";
    return dbg.space();
}
