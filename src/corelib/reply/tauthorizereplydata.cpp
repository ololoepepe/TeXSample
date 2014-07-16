#include "tauthorizereplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAuthorizeReplyDataPrivate ==================
============================================================================*/

class TAuthorizeReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAuthorizeReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TAuthorizeReplyDataPrivate(TAuthorizeReplyData *q);
    ~TAuthorizeReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAuthorizeReplyDataPrivate)
};

/*============================================================================
================================ TAuthorizeReplyDataPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorizeReplyDataPrivate::TAuthorizeReplyDataPrivate(TAuthorizeReplyData *q) :
    BBasePrivate(q)
{
    //
}

TAuthorizeReplyDataPrivate::~TAuthorizeReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorizeReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAuthorizeReplyData =========================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorizeReplyData::TAuthorizeReplyData() :
    BBase(*new TAuthorizeReplyDataPrivate(this))
{
    d_func()->init();
}

TAuthorizeReplyData::TAuthorizeReplyData(const TAuthorizeReplyData &other) :
    BBase(*new TAuthorizeReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAuthorizeReplyData::~TAuthorizeReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorizeReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TAuthorizeReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TAuthorizeReplyData &TAuthorizeReplyData::operator =(const TAuthorizeReplyData &other)
{
    B_D(TAuthorizeReplyData);
    const TAuthorizeReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TAuthorizeReplyData::operator ==(const TAuthorizeReplyData &other) const
{
    const B_D(TAuthorizeReplyData);
    const TAuthorizeReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TAuthorizeReplyData::operator !=(const TAuthorizeReplyData &other) const
{
    return !(*this == other);
}

TAuthorizeReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAuthorizeReplyData &data)
{
    const TAuthorizeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAuthorizeReplyData &data)
{
    TAuthorizeReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAuthorizeReplyData &/*data*/)
{
    //const TAuthorizeReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TAuthorizeReplyData(" << ")";
    return dbg.space();
}
