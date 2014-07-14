#include "tgetselfinforeplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetDelfInfoReplyDataPrivate ================
============================================================================*/

class TGetDelfInfoReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetDelfInfoReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TGetDelfInfoReplyDataPrivate(TGetDelfInfoReplyData *q);
    ~TGetDelfInfoReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetDelfInfoReplyDataPrivate)
};


/*============================================================================
================================ TGetDelfInfoReplyDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TGetDelfInfoReplyDataPrivate::TGetDelfInfoReplyDataPrivate(TGetDelfInfoReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetDelfInfoReplyDataPrivate::~TGetDelfInfoReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetDelfInfoReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetDelfInfoReplyData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TGetDelfInfoReplyData::TGetDelfInfoReplyData() :
    BBase(*new TGetDelfInfoReplyDataPrivate(this))
{
    d_func()->init();
}

TGetDelfInfoReplyData::TGetDelfInfoReplyData(const TGetDelfInfoReplyData &other) :
    BBase(*new TGetDelfInfoReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetDelfInfoReplyData::~TGetDelfInfoReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TGetDelfInfoReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TGetDelfInfoReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TGetDelfInfoReplyData &TGetDelfInfoReplyData::operator =(const TGetDelfInfoReplyData &other)
{
    B_D(TGetDelfInfoReplyData);
    const TGetDelfInfoReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TGetDelfInfoReplyData::operator ==(const TGetDelfInfoReplyData &other) const
{
    const B_D(TGetDelfInfoReplyData);
    const TGetDelfInfoReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TGetDelfInfoReplyData::operator !=(const TGetDelfInfoReplyData &other) const
{
    return !(*this == other);
}

TGetDelfInfoReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetDelfInfoReplyData &data)
{
    const TGetDelfInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetDelfInfoReplyData &data)
{
    TGetDelfInfoReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetDelfInfoReplyData &/*data*/)
{
    //const TGetDelfInfoReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetDelfInfoReplyData(" << ")";
    return dbg.space();
}
