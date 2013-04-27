#include "tinviteinfo.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>

#include <QObject>
#include <QDataStream>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QUuid>

/*============================================================================
================================ TInviteInfoPrivate ==========================
============================================================================*/

class TInviteInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TInviteInfo)
public:
   static QString numberToString(quint64 number, int fixedLength = -1);
public:
   explicit TInviteInfoPrivate(TInviteInfo *q);
    ~TInviteInfoPrivate();
public:
    void init();
public:
    quint64 id;
    QUuid uuid;
    quint64 creatorId;
    QDateTime creationDT;
    QDateTime expirationDT;
private:
    Q_DISABLE_COPY(TInviteInfoPrivate)
};

/*============================================================================
================================ TInviteInfoPrivate ==========================
============================================================================*/

/*============================== Static public methods =====================*/

QString TInviteInfoPrivate::numberToString(quint64 number, int fixedLength)
{
    QString s = QString::number(number);
    int dlen = fixedLength - s.length();
    if (dlen > 0)
        s.prepend( QString().fill('0', dlen) );
    return s;
}

/*============================== Public constructors =======================*/

TInviteInfoPrivate::TInviteInfoPrivate(TInviteInfo *q) :
    BBasePrivate(q)
{
    //
}

TInviteInfoPrivate::~TInviteInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TInviteInfoPrivate::init()
{
    id = 0;
    creationDT.setTimeSpec(Qt::UTC);
    expirationDT.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TInviteInfo =================================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteInfo::TInviteInfo() :
    BBase(*new TInviteInfoPrivate(this))
{
    d_func()->init();
}

TInviteInfo::TInviteInfo(const TInviteInfo &other) :
    BBase(*new TInviteInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TInviteInfo::~TInviteInfo()
{
    //
}

/*============================== Public methods ============================*/

void TInviteInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TInviteInfo::setUuid(const QUuid &uuid)
{
    d_func()->uuid = uuid;
}

void TInviteInfo::setUuid(const QString &s)
{
    d_func()->uuid = BeQt::uuidFromText(s);
}

void TInviteInfo::setCreatorId(quint64 id)
{
    d_func()->creatorId = id;
}

void TInviteInfo::setCreationDateTime(const QDateTime &dt)
{
    d_func()->creationDT = dt.toUTC();
}

void TInviteInfo::setExpirationDateTime(const QDateTime &dt)
{
    d_func()->expirationDT = dt.toUTC();
}

quint64 TInviteInfo::id() const
{
    return d_func()->id;
}

QString TInviteInfo::idString(int fixedLength) const
{
    return TInviteInfoPrivate::numberToString(d_func()->id, fixedLength);
}

QUuid TInviteInfo::uuid() const
{
    return d_func()->uuid;
}

QString TInviteInfo::uuidString(bool unwrapped) const
{
    return unwrapped ? BeQt::pureUuidText(d_func()->uuid) : d_func()->uuid.toString();
}

quint64 TInviteInfo::creatorId() const
{
    return d_func()->creatorId;
}

QString TInviteInfo::creatorIdString(int fixedLength) const
{
    return TInviteInfoPrivate::numberToString(d_func()->creatorId, fixedLength);
}

QDateTime TInviteInfo::creationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->creationDT.toTimeSpec(spec);
}

QDateTime TInviteInfo::expirationDateTime(Qt::TimeSpec spec) const
{
    return d_func()->expirationDT.toTimeSpec(spec);
}

bool TInviteInfo::isValid() const
{
    const B_D(TInviteInfo);
    return d->id && !d->uuid.isNull() && d->creatorId && d->creationDT.isValid() && d->expirationDT.isValid();
    return true;
}

/*============================== Public operators ==========================*/

TInviteInfo &TInviteInfo::operator =(const TInviteInfo &other)
{
    B_D(TInviteInfo);
    const TInviteInfoPrivate *dd = other.d_func();
    d->id = dd->id;
    d->uuid = dd->uuid;
    d->creatorId = dd->creatorId;
    d->creationDT = dd->creationDT;
    d->expirationDT = dd->expirationDT;
    return *this;
}

bool TInviteInfo::operator ==(const TInviteInfo &other) const
{
    const B_D(TInviteInfo);
    const TInviteInfoPrivate *dd = other.d_func();
    return d->id == dd->id;
}

TInviteInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TInviteInfo &info)
{
    const TInviteInfoPrivate *d = info.d_func();
    stream << d->id;
    stream << d->uuid;
    stream << d->creatorId;
    stream << d->creationDT;
    stream << d->expirationDT;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TInviteInfo &info)
{
    TInviteInfoPrivate *d = info.d_func();
    stream >> d->id;
    stream >> d->uuid;
    stream >>d->creatorId;
    stream >> d->creationDT;
    if (d->creationDT.timeSpec() != Qt::UTC)
        d->creationDT = d->creationDT.toUTC();
    stream >> d->expirationDT;
    if (d->expirationDT.timeSpec() != Qt::UTC)
        d->expirationDT = d->expirationDT.toUTC();
    return stream;
}

QDebug operator <<(QDebug dbg, const TInviteInfo &info)
{
    const TInviteInfoPrivate *d = info.d_func();
    dbg.nospace() << "TInviteInfo(" << d->id << "," << info.uuidString() << "," << d->creatorId << ","
                  << d->creationDT << "," << d->expirationDT << ")";
    return dbg.space();
}
