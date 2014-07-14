#include "tedituserreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditUserReplyDataPrivate ===================
============================================================================*/

class TEditUserReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditUserReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TEditUserReplyDataPrivate(TEditUserReplyData *q);
    ~TEditUserReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditUserReplyDataPrivate)
};


/*============================================================================
================================ TEditUserReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TEditUserReplyDataPrivate::TEditUserReplyDataPrivate(TEditUserReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditUserReplyDataPrivate::~TEditUserReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditUserReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditUserReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditUserReplyData::TEditUserReplyData() :
    BBase(*new TEditUserReplyDataPrivate(this))
{
    d_func()->init();
}

TEditUserReplyData::TEditUserReplyData(const TEditUserReplyData &other) :
    BBase(*new TEditUserReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditUserReplyData::~TEditUserReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditUserReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TEditUserReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TEditUserReplyData &TEditUserReplyData::operator =(const TEditUserReplyData &other)
{
    B_D(TEditUserReplyData);
    const TEditUserReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TEditUserReplyData::operator ==(const TEditUserReplyData &other) const
{
    const B_D(TEditUserReplyData);
    const TEditUserReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TEditUserReplyData::operator !=(const TEditUserReplyData &other) const
{
    return !(*this == other);
}

TEditUserReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditUserReplyData &data)
{
    const TEditUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditUserReplyData &data)
{
    TEditUserReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditUserReplyData &/*data*/)
{
    //const TEditUserReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditUserReplyData(" << ")";
    return dbg.space();
}
