#include "tgetselfinforeplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetSelfInfoReplyDataPrivate ================
============================================================================*/

class TGetSelfInfoReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetSelfInfoReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TGetSelfInfoReplyDataPrivate(TGetSelfInfoReplyData *q);
    ~TGetSelfInfoReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetSelfInfoReplyDataPrivate)
};

/*============================================================================
================================ TGetSelfInfoReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSelfInfoReplyDataPrivate::TGetSelfInfoReplyDataPrivate(TGetSelfInfoReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetSelfInfoReplyDataPrivate::~TGetSelfInfoReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetSelfInfoReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetSelfInfoReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TGetSelfInfoReplyData::TGetSelfInfoReplyData() :
    BBase(*new TGetSelfInfoReplyDataPrivate(this))
{
    d_func()->init();
}

TGetSelfInfoReplyData::TGetSelfInfoReplyData(const TGetSelfInfoReplyData &other) :
    BBase(*new TGetSelfInfoReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetSelfInfoReplyData::~TGetSelfInfoReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetSelfInfoReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TGetSelfInfoReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TGetSelfInfoReplyData &TGetSelfInfoReplyData::operator =(const TGetSelfInfoReplyData &other)
{
    B_D(TGetSelfInfoReplyData);
    const TGetSelfInfoReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TGetSelfInfoReplyData::operator ==(const TGetSelfInfoReplyData &other) const
{
    const B_D(TGetSelfInfoReplyData);
    const TGetSelfInfoReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TGetSelfInfoReplyData::operator !=(const TGetSelfInfoReplyData &other) const
{
    return !(*this == other);
}

TGetSelfInfoReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoReplyData &data)
{
    const TGetSelfInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetSelfInfoReplyData &data)
{
    TGetSelfInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetSelfInfoReplyData &/*data*/)
{
    //const TGetSelfInfoReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetSelfInfoReplyData(" << ")";
    return dbg.space();
}
