#include "tgenerateinvitesreplydata.h"

#include "tinviteinfolist.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGenerateInvitesReplyDataPrivate ============
============================================================================*/

class TGenerateInvitesReplyDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGenerateInvitesReplyData)
public:
    TInviteInfoList generatedInvites;
public:
    explicit TGenerateInvitesReplyDataPrivate(TGenerateInvitesReplyData *q);
    ~TGenerateInvitesReplyDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGenerateInvitesReplyDataPrivate)
};


/*============================================================================
================================ TGenerateInvitesReplyDataPrivate ============
============================================================================*/

/*============================== Public constructors =======================*/

TGenerateInvitesReplyDataPrivate::TGenerateInvitesReplyDataPrivate(TGenerateInvitesReplyData *q) :
    BBasePrivate(q)
{
    //
}

TGenerateInvitesReplyDataPrivate::~TGenerateInvitesReplyDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGenerateInvitesReplyDataPrivate::init()
{
    //
}

/*============================================================================
================================ TGenerateInvitesReplyData ===================
============================================================================*/

/*============================== Public constructors =======================*/

TGenerateInvitesReplyData::TGenerateInvitesReplyData() :
    BBase(*new TGenerateInvitesReplyDataPrivate(this))
{
    d_func()->init();
}

TGenerateInvitesReplyData::TGenerateInvitesReplyData(const TGenerateInvitesReplyData &other) :
    BBase(*new TGenerateInvitesReplyDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGenerateInvitesReplyData::~TGenerateInvitesReplyData()
{
    //
}

/*============================== Public methods ============================*/

TInviteInfoList TGenerateInvitesReplyData::generatedInvites() const
{
    return d_func()->generatedInvites;
}

void TGenerateInvitesReplyData::setGeneratedInvites(const TInviteInfoList &generatedInvites)
{
    d_func()->generatedInvites = generatedInvites;
}

/*============================== Public operators ==========================*/

TGenerateInvitesReplyData &TGenerateInvitesReplyData::operator =(const TGenerateInvitesReplyData &other)
{
    B_D(TGenerateInvitesReplyData);
    const TGenerateInvitesReplyDataPrivate *dd = other.d_func();
    d->generatedInvites = dd->generatedInvites;
    return *this;
}

bool TGenerateInvitesReplyData::operator ==(const TGenerateInvitesReplyData &other) const
{
    const B_D(TGenerateInvitesReplyData);
    const TGenerateInvitesReplyDataPrivate *dd = other.d_func();
    return d->generatedInvites == dd->generatedInvites;
}

bool TGenerateInvitesReplyData::operator !=(const TGenerateInvitesReplyData &other) const
{
    return !(*this == other);
}

TGenerateInvitesReplyData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGenerateInvitesReplyData &data)
{
    const TGenerateInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("generated_invites", d->generatedInvites);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGenerateInvitesReplyData &data)
{
    TGenerateInvitesReplyDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->generatedInvites = m.value("generated_invites").value<TInviteInfoList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TGenerateInvitesReplyData &/*data*/)
{
    //const TGenerateInvitesReplyDataPrivate *d = data.d_func();
    dbg.nospace() << "TGenerateInvitesReplyData(" << ")";
    return dbg.space();
}
