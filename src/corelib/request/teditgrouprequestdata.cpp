#include "teditgrouprequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditGroupRequestDataPrivate ================
============================================================================*/

class TEditGroupRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditGroupRequestData)
public:
    quint64 id;
    QString name;
public:
    explicit TEditGroupRequestDataPrivate(TEditGroupRequestData *q);
    ~TEditGroupRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditGroupRequestDataPrivate)
};


/*============================================================================
================================ TEditGroupRequestDataPrivate ================
============================================================================*/

/*============================== Public constructors =======================*/

TEditGroupRequestDataPrivate::TEditGroupRequestDataPrivate(TEditGroupRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditGroupRequestDataPrivate::~TEditGroupRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditGroupRequestDataPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TEditGroupRequestData =======================
============================================================================*/

/*============================== Public constructors =======================*/

TEditGroupRequestData::TEditGroupRequestData() :
    BBase(*new TEditGroupRequestDataPrivate(this))
{
    d_func()->init();
}

TEditGroupRequestData::TEditGroupRequestData(const TEditGroupRequestData &other) :
    BBase(*new TEditGroupRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditGroupRequestData::~TEditGroupRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TEditGroupRequestData::clear()
{
    B_D(TEditGroupRequestData);
    d->id = 0;
    d->name.clear();
}

quint64 TEditGroupRequestData::id() const
{
    return d_func()->id;
}

bool TEditGroupRequestData::isValid() const
{
    const B_D(TEditGroupRequestData);
    return d->id && !d->name.isEmpty();
}

QString TEditGroupRequestData::name() const
{
    return d_func()->name;
}

void TEditGroupRequestData::setId(quint64 id)
{
    d_func()->id = id;
}

void TEditGroupRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testGroupName(name) ? name : QString();
}

/*============================== Public operators ==========================*/

TEditGroupRequestData &TEditGroupRequestData::operator =(const TEditGroupRequestData &other)
{
    B_D(TEditGroupRequestData);
    const TEditGroupRequestDataPrivate *dd = other.d_func();
    d->id = dd->id;
    d->name = dd->name;
    return *this;
}

bool TEditGroupRequestData::operator ==(const TEditGroupRequestData &other) const
{
    const B_D(TEditGroupRequestData);
    const TEditGroupRequestDataPrivate *dd = other.d_func();
    return d->id == dd->id && d->name == dd->name;
}

bool TEditGroupRequestData::operator !=(const TEditGroupRequestData &other) const
{
    return !(*this == other);
}

TEditGroupRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditGroupRequestData &data)
{
    const TEditGroupRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("id", d->id);
    m.insert("name", d->name);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditGroupRequestData &data)
{
    TEditGroupRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->id = m.value("id").toULongLong();
    d->name = m.value("name").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditGroupRequestData &data)
{
    const TEditGroupRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditGroupRequestData(" << d->name << ")";
    return dbg.space();
}
