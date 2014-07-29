#include "tgetuserinfolistadminrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetUserInfoListAdminRequestDataPrivate =====
============================================================================*/

class TGetUserInfoListAdminRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetUserInfoListAdminRequestData)
public:
    explicit TGetUserInfoListAdminRequestDataPrivate(TGetUserInfoListAdminRequestData *q);
    ~TGetUserInfoListAdminRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetUserInfoListAdminRequestDataPrivate)
};

/*============================================================================
================================ TGetUserInfoListAdminRequestDataPrivate =====
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoListAdminRequestDataPrivate::TGetUserInfoListAdminRequestDataPrivate(TGetUserInfoListAdminRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetUserInfoListAdminRequestDataPrivate::~TGetUserInfoListAdminRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetUserInfoListAdminRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetUserInfoListAdminRequestData ============
============================================================================*/

/*============================== Public constructors =======================*/

TGetUserInfoListAdminRequestData::TGetUserInfoListAdminRequestData() :
    BBase(*new TGetUserInfoListAdminRequestDataPrivate(this))
{
    d_func()->init();
}

TGetUserInfoListAdminRequestData::TGetUserInfoListAdminRequestData(const TGetUserInfoListAdminRequestData &other) :
    BBase(*new TGetUserInfoListAdminRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetUserInfoListAdminRequestData::~TGetUserInfoListAdminRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetUserInfoListAdminRequestData &TGetUserInfoListAdminRequestData::operator =(
        const TGetUserInfoListAdminRequestData &/*other*/)
{
    //B_D(TGetUserInfoListAdminRequestData);
    //const TGetUserInfoListAdminRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetUserInfoListAdminRequestData::operator ==(const TGetUserInfoListAdminRequestData &/*other*/) const
{
    //const B_D(TGetUserInfoListAdminRequestData);
    //const TGetUserInfoListAdminRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetUserInfoListAdminRequestData::operator !=(const TGetUserInfoListAdminRequestData &other) const
{
    return !(*this == other);
}

TGetUserInfoListAdminRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetUserInfoListAdminRequestData &/*data*/)
{
    //const TGetUserInfoListAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetUserInfoListAdminRequestData &/*data*/)
{
    //TGetUserInfoListAdminRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetUserInfoListAdminRequestData &/*data*/)
{
    //const TGetUserInfoListAdminRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetUserInfoListAdminRequestData(" << ")";
    return dbg.space();
}
