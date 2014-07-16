#include "tregisterreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TRegisterReplyDataPrivate ===================
============================================================================*/

class TRegisterReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TRegisterReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TRegisterReplyDataPrivate(TRegisterReplyData *q);
    ~TRegisterReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TRegisterReplyDataPrivate)
};

/*============================================================================
================================ TRegisterReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TRegisterReplyDataPrivate::TRegisterReplyDataPrivate(TRegisterReplyData *q) :
    BBasePrivate(q)
{
    //
}

TRegisterReplyDataPrivate::~TRegisterReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRegisterReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TRegisterReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TRegisterReplyData::TRegisterReplyData() :
    BBase(*new TRegisterReplyDataPrivate(this))
{
    d_func()->init();
}

TRegisterReplyData::TRegisterReplyData(const TRegisterReplyData &other) :
    BBase(*new TRegisterReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TRegisterReplyData::~TRegisterReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TRegisterReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TRegisterReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TRegisterReplyData &TRegisterReplyData::operator =(const TRegisterReplyData &other)
{
    B_D(TRegisterReplyData);
    const TRegisterReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TRegisterReplyData::operator ==(const TRegisterReplyData &other) const
{
    const B_D(TRegisterReplyData);
    const TRegisterReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TRegisterReplyData::operator !=(const TRegisterReplyData &other) const
{
    return !(*this == other);
}

TRegisterReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TRegisterReplyData &data)
{
    const TRegisterReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TRegisterReplyData &data)
{
    TRegisterReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TRegisterReplyData &/*data*/)
{
    //const TRegisterReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TRegisterReplyData(" << ")";
    return dbg.space();
}
