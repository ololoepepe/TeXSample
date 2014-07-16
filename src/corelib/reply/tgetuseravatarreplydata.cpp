#include "tgetuseravatarreplydata.h"


#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserAvatarReplyDataPrivate ==============
============================================================================*/

class TGetUserAvatarReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserAvatarReplyData)
public:
    QImage avatar;
public:
    explicit TGetUserAvatarReplyDataPrivate(TGetUserAvatarReplyData *q);
    ~TGetUserAvatarReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserAvatarReplyDataPrivate)
};

/*============================================================================
================================ TGetUserAvatarReplyDataPrivate ==============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarReplyDataPrivate::TGetUserAvatarReplyDataPrivate(TGetUserAvatarReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserAvatarReplyDataPrivate::~TGetUserAvatarReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserAvatarReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserAvatarReplyData =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserAvatarReplyData::TGetUserAvatarReplyData() :
    BBase(*new TGetUserAvatarReplyDataPrivate(this))
{
    d_func()->init();
}

TGetUserAvatarReplyData::TGetUserAvatarReplyData(const TGetUserAvatarReplyData &other) :
    BBase(*new TGetUserAvatarReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserAvatarReplyData::~TGetUserAvatarReplyData()
{
    //
}

/*============================== Public methods ============================*/

QImage TGetUserAvatarReplyData::avatar() const
{
    return d_func()->avatar;
}

void TGetUserAvatarReplyData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = avatar;
}

/*============================== Public operators ==========================*/

TGetUserAvatarReplyData &TGetUserAvatarReplyData::operator =(const TGetUserAvatarReplyData &other)
{
    B_D(TGetUserAvatarReplyData);
    const TGetUserAvatarReplyDataPrivate *dd = other.d_func();
    d->avatar = dd->avatar;
    return *this;
}

bool TGetUserAvatarReplyData::operator ==(const TGetUserAvatarReplyData &other) const
{
    const B_D(TGetUserAvatarReplyData);
    const TGetUserAvatarReplyDataPrivate *dd = other.d_func();
    return d->avatar == dd->avatar;
}

bool TGetUserAvatarReplyData::operator !=(const TGetUserAvatarReplyData &other) const
{
    return !(*this == other);
}

TGetUserAvatarReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarReplyData &data)
{
    const TGetUserAvatarReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("avatar", d->avatar);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserAvatarReplyData &data)
{
    TGetUserAvatarReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->avatar = m.value("avatar").value<QImage>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserAvatarReplyData &/*data*/)
{
    //const TGetUserAvatarReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserAvatarReplyData(" << ")";
    return dbg.space();
}
