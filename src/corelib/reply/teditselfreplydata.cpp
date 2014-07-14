#include "teditselfreplydata.h"

#include "tuserinfo.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSelfReplyDataPrivate ===================
============================================================================*/

class TEditSelfReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSelfReplyData)
public:
    TUserInfo userInfo;
public:
    explicit TEditSelfReplyDataPrivate(TEditSelfReplyData *q);
    ~TEditSelfReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSelfReplyDataPrivate)
};


/*============================================================================
================================ TEditSelfReplyDataPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfReplyDataPrivate::TEditSelfReplyDataPrivate(TEditSelfReplyData *q) :
    BBasePrivate(q)
{
    //
}

TEditSelfReplyDataPrivate::~TEditSelfReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSelfReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TEditSelfReplyData ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfReplyData::TEditSelfReplyData() :
    BBase(*new TEditSelfReplyDataPrivate(this))
{
    d_func()->init();
}

TEditSelfReplyData::TEditSelfReplyData(const TEditSelfReplyData &other) :
    BBase(*new TEditSelfReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSelfReplyData::~TEditSelfReplyData()
{
    //
}

/*============================== Public methods ============================*/

void TEditSelfReplyData::setUserInfo(const TUserInfo &info)
{
    d_func()->userInfo = info;
}

TUserInfo TEditSelfReplyData::userInfo() const
{
    return d_func()->userInfo;
}

/*============================== Public operators ==========================*/

TEditSelfReplyData &TEditSelfReplyData::operator =(const TEditSelfReplyData &other)
{
    B_D(TEditSelfReplyData);
    const TEditSelfReplyDataPrivate *dd = other.d_func();
    d->userInfo = dd->userInfo;
    return *this;
}

bool TEditSelfReplyData::operator ==(const TEditSelfReplyData &other) const
{
    const B_D(TEditSelfReplyData);
    const TEditSelfReplyDataPrivate *dd = other.d_func();
    return d->userInfo == dd->userInfo;
}

bool TEditSelfReplyData::operator !=(const TEditSelfReplyData &other) const
{
    return !(*this == other);
}

TEditSelfReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSelfReplyData &data)
{
    const TEditSelfReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("user_info", d->userInfo);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSelfReplyData &data)
{
    TEditSelfReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->userInfo = m.value("user_info").value<TUserInfo>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSelfReplyData &/*data*/)
{
    //const TEditSelfReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSelfReplyData(" << ")";
    return dbg.space();
}
