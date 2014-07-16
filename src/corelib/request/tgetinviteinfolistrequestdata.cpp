#include "tgetinviteinfolistrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetInviteInfoListRequestDataPrivate ========
============================================================================*/

class TGetInviteInfoListRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetInviteInfoListRequestData)
public:
    explicit TGetInviteInfoListRequestDataPrivate(TGetInviteInfoListRequestData *q);
    ~TGetInviteInfoListRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetInviteInfoListRequestDataPrivate)
};

/*============================================================================
================================ TGetInviteInfoListRequestDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TGetInviteInfoListRequestDataPrivate::TGetInviteInfoListRequestDataPrivate(TGetInviteInfoListRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetInviteInfoListRequestDataPrivate::~TGetInviteInfoListRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetInviteInfoListRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGetInviteInfoListRequestData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TGetInviteInfoListRequestData::TGetInviteInfoListRequestData() :
    BBase(*new TGetInviteInfoListRequestDataPrivate(this))
{
    d_func()->init();
}

TGetInviteInfoListRequestData::TGetInviteInfoListRequestData(const TGetInviteInfoListRequestData &other) :
    BBase(*new TGetInviteInfoListRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetInviteInfoListRequestData::~TGetInviteInfoListRequestData()
{
    //
}

/*============================== Public operators ==========================*/

TGetInviteInfoListRequestData &TGetInviteInfoListRequestData::operator =(
        const TGetInviteInfoListRequestData &/*other*/)
{
    //B_D(TGetInviteInfoListRequestData);
    //const TGetInviteInfoListRequestDataPrivate *dd = other.d_func();
    return *this;
}

bool TGetInviteInfoListRequestData::operator ==(const TGetInviteInfoListRequestData &/*other*/) const
{
    //const B_D(TGetInviteInfoListRequestData);
    //const TGetInviteInfoListRequestDataPrivate *dd = other.d_func();
    return true;
}

bool TGetInviteInfoListRequestData::operator !=(const TGetInviteInfoListRequestData &other) const
{
    return !(*this == other);
}

TGetInviteInfoListRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetInviteInfoListRequestData &/*data*/)
{
    //const TGetInviteInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetInviteInfoListRequestData &/*data*/)
{
    //TGetInviteInfoListRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetInviteInfoListRequestData &/*data*/)
{
    //const TGetInviteInfoListRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetInviteInfoListRequestData(" << ")";
    return dbg.space();
}
