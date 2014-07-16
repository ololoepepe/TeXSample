#include "tgetlabdatarequestdata.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TGetLabDataRequestDataPrivate ===============
============================================================================*/

class TGetLabDataRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGetLabDataRequestData)
public:
    quint64 labId;
    BeQt::OSType os;
public:
    explicit TGetLabDataRequestDataPrivate(TGetLabDataRequestData *q);
    ~TGetLabDataRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGetLabDataRequestDataPrivate)
};

/*============================================================================
================================ TGetLabDataRequestDataPrivate ===============
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabDataRequestDataPrivate::TGetLabDataRequestDataPrivate(TGetLabDataRequestData *q) :
    BBasePrivate(q)
{
    //
}

TGetLabDataRequestDataPrivate::~TGetLabDataRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabDataRequestDataPrivate::init()
{
    labId = 0;
    os = BeQt::UnknownOS;
}

/*============================================================================
================================ TGetLabDataRequestData ======================
============================================================================*/

/*============================== Public constructors =======================*/

TGetLabDataRequestData::TGetLabDataRequestData() :
    BBase(*new TGetLabDataRequestDataPrivate(this))
{
    d_func()->init();
}

TGetLabDataRequestData::TGetLabDataRequestData(const TGetLabDataRequestData &other) :
    BBase(*new TGetLabDataRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TGetLabDataRequestData::~TGetLabDataRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TGetLabDataRequestData::clear()
{
    d_func()->labId = 0;
    d_func()->os = BeQt::UnknownOS;
}

quint64 TGetLabDataRequestData::labId() const
{
    return d_func()->labId;
}

BeQt::OSType TGetLabDataRequestData::os() const
{
    return d_func()->os;
}

bool TGetLabDataRequestData::isValid() const
{
    return d_func()->labId;
}

void TGetLabDataRequestData::setLabId(quint64 id)
{
    d_func()->labId = id;
}

void TGetLabDataRequestData::setOs(const BeQt::OSType os)
{
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d_func()->os = enum_cast<BeQt::OSType>(os, Types, BeQt::UnknownOS);
}

/*============================== Public operators ==========================*/

TGetLabDataRequestData &TGetLabDataRequestData::operator =(const TGetLabDataRequestData &other)
{
    B_D(TGetLabDataRequestData);
    const TGetLabDataRequestDataPrivate *dd = other.d_func();
    d->labId = dd->labId;
    d->os = dd->os;
    return *this;
}

bool TGetLabDataRequestData::operator ==(const TGetLabDataRequestData &other) const
{
    const B_D(TGetLabDataRequestData);
    const TGetLabDataRequestDataPrivate *dd = other.d_func();
    return d->labId == dd->labId && d->os == dd->os;
}

bool TGetLabDataRequestData::operator !=(const TGetLabDataRequestData &other) const
{
    return !(*this == other);
}

TGetLabDataRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TGetLabDataRequestData &data)
{
    const TGetLabDataRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("lab_id", d->labId);
    m.insert("os", int(d->os));
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TGetLabDataRequestData &data)
{
    TGetLabDataRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d->labId = m.value("lab_id").toULongLong();
    d->os = enum_cast<BeQt::OSType>(m.value("os"), Types, BeQt::UnknownOS);
    return stream;
}

QDebug operator <<(QDebug dbg, const TGetLabDataRequestData &/*data*/)
{
    //const TGetLabDataRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TGetLabDataRequestData(" << ")";
    return dbg.space();
}
