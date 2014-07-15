#include "tprojectinfo.h"

#include "tprojecttype.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TProjectInfoPrivate =========================
============================================================================*/

class TProjectInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TProjectInfo)
public:
    BeQt::OSType os;
    int size;
    TProjectType type;
public:
    explicit TProjectInfoPrivate(TProjectInfo *q);
    ~TProjectInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TProjectInfoPrivate)
};

/*============================================================================
================================ TProjectInfoPrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TProjectInfoPrivate::TProjectInfoPrivate(TProjectInfo *q) :
    BBasePrivate(q)
{
    //
}

TProjectInfoPrivate::~TProjectInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TProjectInfoPrivate::init()
{
    os = BeQt::UnknownOS;
    size = 0;
}

/*============================================================================
================================ TProjectInfo ================================
============================================================================*/

/*============================== Public constructors =======================*/

TProjectInfo::TProjectInfo() :
    BBase(*new TProjectInfoPrivate(this))
{
    d_func()->init();
}

TProjectInfo::TProjectInfo(const TProjectInfo &other) :
    BBase(*new TProjectInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TProjectInfo::~TProjectInfo()
{
    //
}

/*============================== Public methods ============================*/

void TProjectInfo::clear()
{
    B_D(TProjectInfo);
    d->os = BeQt::UnknownOS;
    d->size = 0;
    d->type = TProjectType();
}

bool TProjectInfo::isValid() const
{
    const B_D(TProjectInfo);
    return d->type.isValid() && (d->type == TProjectType(TProjectType::UrlType) || BeQt::UnknownOS != d->os);
}

BeQt::OSType TProjectInfo::os() const
{
    return d_func()->os;
}

void TProjectInfo::setOs(BeQt::OSType os)
{
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d_func()->os = enum_cast<BeQt::OSType>(os, Types, BeQt::UnknownOS);
}

void TProjectInfo::setSize(int size)
{
    d_func()->size = (size > 0) ? size : 0;
}

void TProjectInfo::setType(const TProjectType &type)
{
    d_func()->type = type;
}

int TProjectInfo::size() const
{
    return d_func()->size;
}

TProjectType TProjectInfo::type() const
{
    return d_func()->type;
}

/*============================== Public operators ==========================*/

TProjectInfo &TProjectInfo::operator =(const TProjectInfo &other)
{
    B_D(TProjectInfo);
    const TProjectInfoPrivate *dd = other.d_func();
    d->os = dd->os;
    d->size = dd->size;
    d->type = dd->type;
    return *this;
}

bool TProjectInfo::operator ==(const TProjectInfo &other) const
{
    const B_D(TProjectInfo);
    const TProjectInfoPrivate *dd = other.d_func();
    return d->os == dd->os && d->size == dd->size && d->type == dd->type;
}

bool TProjectInfo::operator !=(const TProjectInfo &other) const
{
    return !(*this == other);
}

TProjectInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TProjectInfo &data)
{
    const TProjectInfoPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("os", int(d->os));
    m.insert("size", d->size);
    m.insert("type", d->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProjectInfo &data)
{
    TProjectInfoPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d->os = enum_cast<BeQt::OSType>(m.value("os"), Types, BeQt::UnknownOS);
    d->size = m.value("size").toInt();
    d->type = m.value("type").value<TProjectType>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TProjectInfo &/*data*/)
{
    //const TProjectInfoPrivate *d = data.d_func();
    dbg.nospace() << "TProjectInfo(" << ")";
    return dbg.space();
}
