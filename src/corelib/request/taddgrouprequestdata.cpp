#include "taddgrouprequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TAddGroupRequestDataPrivate =================
============================================================================*/

class TAddGroupRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAddGroupRequestData)
public:
    QString name;
public:
    explicit TAddGroupRequestDataPrivate(TAddGroupRequestData *q);
    ~TAddGroupRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TAddGroupRequestDataPrivate)
};

/*============================================================================
================================ TAddGroupRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TAddGroupRequestDataPrivate::TAddGroupRequestDataPrivate(TAddGroupRequestData *q) :
    BBasePrivate(q)
{
    //
}

TAddGroupRequestDataPrivate::~TAddGroupRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAddGroupRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TAddGroupRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TAddGroupRequestData::TAddGroupRequestData() :
    BBase(*new TAddGroupRequestDataPrivate(this))
{
    d_func()->init();
}

TAddGroupRequestData::TAddGroupRequestData(const TAddGroupRequestData &other) :
    BBase(*new TAddGroupRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAddGroupRequestData::~TAddGroupRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TAddGroupRequestData::clear()
{
    d_func()->name.clear();
}

bool TAddGroupRequestData::isValid() const
{
    const B_D(TAddGroupRequestData);
    return !d->name.isEmpty();
}

QString TAddGroupRequestData::name() const
{
    return d_func()->name;
}

void TAddGroupRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testGroupName(name) ? name : QString();
}

/*============================== Public operators ==========================*/

TAddGroupRequestData &TAddGroupRequestData::operator =(const TAddGroupRequestData &other)
{
    B_D(TAddGroupRequestData);
    const TAddGroupRequestDataPrivate *dd = other.d_func();
    d->name = dd->name;
    return *this;
}

bool TAddGroupRequestData::operator ==(const TAddGroupRequestData &other) const
{
    const B_D(TAddGroupRequestData);
    const TAddGroupRequestDataPrivate *dd = other.d_func();
    return d->name == dd->name;
}

bool TAddGroupRequestData::operator !=(const TAddGroupRequestData &other) const
{
    return !(*this == other);
}

TAddGroupRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAddGroupRequestData &data)
{
    const TAddGroupRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("name", d->name);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAddGroupRequestData &data)
{
    TAddGroupRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->name = m.value("name").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAddGroupRequestData &data)
{
    const TAddGroupRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TAddGroupRequestData(" << d->name << ")";
    return dbg.space();
}
