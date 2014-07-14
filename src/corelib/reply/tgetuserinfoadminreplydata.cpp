#include "tgetuserinfoadminreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoAdminReplyDataPrivate ===========
============================================================================*/

class TGetUserInfoAdminReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoAdminReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TGetUserInfoAdminReplyDataPrivate(TGetUserInfoAdminReplyData *q);
    ~TGetUserInfoAdminReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoAdminReplyDataPrivate)
};


/*============================================================================
================================ TGetUserInfoAdminReplyDataPrivate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoAdminReplyDataPrivate::TGetUserInfoAdminReplyDataPrivate(TGetUserInfoAdminReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoAdminReplyDataPrivate::~TGetUserInfoAdminReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoAdminReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoAdminReplyData ==================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoAdminReplyData::TGetUserInfoAdminReplyData() :
    BBase(*new TGetUserInfoAdminReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoAdminReplyData::TGetUserInfoAdminReplyData(const TGetUserInfoAdminReplyData &other) :
    BBase(*new TGetUserInfoAdminReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoAdminReplyData::~TGetUserInfoAdminReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoAdminReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TGetUserInfoAdminReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TGetUserInfoAdminReplyData &TGetUserInfoAdminReplyData::operator =(const TGetUserInfoAdminReplyData &other)
{
    B_D(TGetUserInfoAdminReplyData);
    const TGetUserInfoAdminReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TGetUserInfoAdminReplyData::operator ==(const TGetUserInfoAdminReplyData &other) const
{
    const B_D(TGetUserInfoAdminReplyData);
    const TGetUserInfoAdminReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TGetUserInfoAdminReplyData::operator !=(const TGetUserInfoAdminReplyData &other) const
{
    return !(*this == other);
}

TGetUserInfoAdminReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoAdminReplyData &data)
{
    const TGetUserInfoAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoAdminReplyData &data)
{
    TGetUserInfoAdminReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoAdminReplyData &/*data*/)
{
    //const TGetUserInfoAdminReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoAdminReplyData(" << ")";
    return dbg.space();
}
