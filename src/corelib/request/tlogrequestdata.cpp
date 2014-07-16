#include "tlogrequestdata.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BLogger>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLogRequestDataPrivate ======================
============================================================================*/

class TLogRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLogRequestData)
public:
    BLogger::Level level;
    QString text;
public:
    explicit TLogRequestDataPrivate(TLogRequestData *q);
    ~TLogRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLogRequestDataPrivate)
};

/*============================================================================
================================ TLogRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TLogRequestDataPrivate::TLogRequestDataPrivate(TLogRequestData *q) :
    BBasePrivate(q)
{
    //
}

TLogRequestDataPrivate::~TLogRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLogRequestDataPrivate::init()
{
    //
}

/*============================================================================
================================ TLogRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TLogRequestData::TLogRequestData() :
    BBase(*new TLogRequestDataPrivate(this))
{
    d_func()->init();
}

TLogRequestData::TLogRequestData(const TLogRequestData &other) :
    BBase(*new TLogRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLogRequestData::~TLogRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TLogRequestData::clear()
{
    d_func()->text.clear();
}

bool TLogRequestData::isValid() const
{
    const B_D(TLogRequestData);
    return !d->text.isEmpty();
}

BLogger::Level TLogRequestData::level() const
{
    return d_func()->level;
}

void TLogRequestData::setLevel(BLogger::Level level)
{
    d_func()->level = enum_cast<BLogger::Level>(level, BLogger::NoLevel, BLogger::FatalLevel);
}

void TLogRequestData::setText(const QString &text)
{
    d_func()->text = text;
}

QString TLogRequestData::text() const
{
    return d_func()->text;
}

/*============================== Public operators ==========================*/

TLogRequestData &TLogRequestData::operator =(const TLogRequestData &other)
{
    B_D(TLogRequestData);
    const TLogRequestDataPrivate *dd = other.d_func();
    d->level = dd->level;
    d->text = dd->text;
    return *this;
}

bool TLogRequestData::operator ==(const TLogRequestData &other) const
{
    const B_D(TLogRequestData);
    const TLogRequestDataPrivate *dd = other.d_func();
    return d->level == dd->level && d->text == dd->text;
}

bool TLogRequestData::operator !=(const TLogRequestData &other) const
{
    return !(*this == other);
}

TLogRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLogRequestData &data)
{
    const TLogRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("level", int(d->level));
    m.insert("text", d->text);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLogRequestData &data)
{
    TLogRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->level = enum_cast<BLogger::Level>(m.value("level"), BLogger::NoLevel, BLogger::FatalLevel);
    d->text = m.value("text").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLogRequestData &/*data*/)
{
    //const TLogRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TLogRequestData(" << ")";
    return dbg.space();
}
