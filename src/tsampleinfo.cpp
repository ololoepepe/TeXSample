#include "tsampleinfo.h"

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QString>

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

class TSampleInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TSampleInfo)
public:
   explicit TSampleInfoPrivate(TSampleInfo *q);
    ~TSampleInfoPrivate();
public:
    void init();
public:
    quint64 id;
    QString title;
private:
    Q_DISABLE_COPY(TSampleInfoPrivate)
};

/*============================================================================
================================ TSampleInfoPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TSampleInfoPrivate::TSampleInfoPrivate(TSampleInfo *q) :
    BBasePrivate(q)
{
    //
}

TSampleInfoPrivate::~TSampleInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TSampleInfoPrivate::init()
{
    id = 0;
}

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

/*============================== Public constructors =======================*/

TSampleInfo::TSampleInfo() :
    BBase(*new TSampleInfoPrivate(this))
{
    d_func()->init();
}

TSampleInfo::TSampleInfo(const TSampleInfo &other) :
    BBase(*new TSampleInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TSampleInfo::~TSampleInfo()
{
    //
}

/*============================== Protected constructors ====================*/

TSampleInfo::TSampleInfo(TSampleInfoPrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

void TSampleInfo::setId(quint64 id)
{
    d_func()->id = id;
}

void TSampleInfo::setTitle(const QString &title)
{
    d_func()->title = title;
}

quint64 TSampleInfo::id() const
{
    return d_func()->id;
}

QString TSampleInfo::title() const
{
    return d_func()->title;
}

/*============================== Public operators ==========================*/

TSampleInfo &TSampleInfo::operator=(const TSampleInfo &other)
{
    B_D(TSampleInfo);
    const TSampleInfoPrivate *dd = other.d_func();
    d->id = dd->id;
    d->title = dd->title;
    return *this;
}

/*============================== Public friend operators ===================*/

QDataStream &operator<<(QDataStream &stream, const TSampleInfo &info)
{
    const TSampleInfoPrivate *d = info.d_func();
    stream << d->id;
    stream << d->title;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, TSampleInfo &info)
{
    TSampleInfoPrivate *d = info.d_func();
    stream >> d->id;
    stream >> d->title;
    return stream;
}
