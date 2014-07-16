#include "tadduserreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddUserReplyDataPrivate ====================
============================================================================*/

class TAddUserReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddUserReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TAddUserReplyDataPrivate(TAddUserReplyData *q);
    ~TAddUserReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddUserReplyDataPrivate)
};

/*============================================================================
================================ TAddUserReplyDataPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TAddUserReplyDataPrivate::TAddUserReplyDataPrivate(TAddUserReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAddUserReplyDataPrivate::~TAddUserReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddUserReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddUserReplyData ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddUserReplyData::TAddUserReplyData() :
    BBase(*new TAddUserReplyDataPrivate(this))
{
    d_func()->init();
}

TAddUserReplyData::TAddUserReplyData(const TAddUserReplyData &other) :
    BBase(*new TAddUserReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddUserReplyData::~TAddUserReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAddUserReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TAddUserReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TAddUserReplyData &TAddUserReplyData::operator =(const TAddUserReplyData &other)
{
    B_D(TAddUserReplyData);
    const TAddUserReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TAddUserReplyData::operator ==(const TAddUserReplyData &other) const
{
    const B_D(TAddUserReplyData);
    const TAddUserReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TAddUserReplyData::operator !=(const TAddUserReplyData &other) const
{
    return !(*this == other);
}

TAddUserReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddUserReplyData &data)
{
    const TAddUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddUserReplyData &data)
{
    TAddUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddUserReplyData &/*data*/)
{
    //const TAddUserReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddUserReplyData(" << ")";
    return dbg.space();
}
