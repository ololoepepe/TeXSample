#include "tgetuserinforeplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoReplyDataPrivate ================
============================================================================*/

class TGetUserInfoReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TGetUserInfoReplyDataPrivate(TGetUserInfoReplyData *q);
    ~TGetUserInfoReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoReplyDataPrivate)
};

/*============================================================================
================================ TGetUserInfoReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoReplyDataPrivate::TGetUserInfoReplyDataPrivate(TGetUserInfoReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoReplyDataPrivate::~TGetUserInfoReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoReplyData::TGetUserInfoReplyData() :
    BBase(*new TGetUserInfoReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoReplyData::TGetUserInfoReplyData(const TGetUserInfoReplyData &other) :
    BBase(*new TGetUserInfoReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoReplyData::~TGetUserInfoReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TGetUserInfoReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TGetUserInfoReplyData &TGetUserInfoReplyData::operator =(const TGetUserInfoReplyData &other)
{
    B_D(TGetUserInfoReplyData);
    const TGetUserInfoReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TGetUserInfoReplyData::operator ==(const TGetUserInfoReplyData &other) const
{
    const B_D(TGetUserInfoReplyData);
    const TGetUserInfoReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TGetUserInfoReplyData::operator !=(const TGetUserInfoReplyData &other) const
{
    return !(*this == other);
}

TGetUserInfoReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoReplyData &data)
{
    const TGetUserInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoReplyData &data)
{
    TGetUserInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoReplyData &/*data*/)
{
    //const TGetUserInfoReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoReplyData(" << ")";
    return dbg.space();
}
