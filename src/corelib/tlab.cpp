#include "tlab.h"

#include "tnamespace.h"
#include "tproject.h"
#include "tprojecttype.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLabPrivate =================================
============================================================================*/

class TLabPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLab)
public:
    TProject desktopApplication;
    QString url;
    TProject webApplication;
public:
    explicit TLabPrivate(TLab *q);
    ~TLabPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLabPrivate)
};

/*============================================================================
================================ TLabPrivate =================================
============================================================================*/

/*============================== Public constructors =======================*/

TLabPrivate::TLabPrivate(TLab *q) :
    BBasePrivate(q)
{
    //
}

TLabPrivate::~TLabPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabPrivate::init()
{
    //
}

/*============================================================================
================================ TLab ========================================
============================================================================*/

/*============================== Public constructors =======================*/

TLab::TLab() :
    BBase(*new TLabPrivate(this))
{
    d_func()->init();
}

TLab::TLab(const TLab &other) :
    BBase(*new TLabPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLab::~TLab()
{
    //
}

/*============================== Public methods ============================*/

void TLab::clear()
{
    B_D(TLab);
    d->desktopApplication.clear();
    d->url.clear();
    d->webApplication.clear();
}

TProject &TLab::desktopApplication()
{
    return d_func()->desktopApplication;
}

const TProject &TLab::desktopApplication() const
{
    return d_func()->desktopApplication;
}

bool TLab::isValid() const
{
    const B_D(TLab);
    return d->desktopApplication.isValid() || !d->url.isEmpty() || d->webApplication.isValid();
}

void TLab::setDesktopApplication(const TProject &project)
{
    clear();
    d_func()->desktopApplication = project;
}

void TLab::setUrl(const QString &url)
{
    clear();
    d_func()->url = Texsample::testUrl(url) ? url : QString();
}

void TLab::setWebApplication(const TProject &project)
{
    clear();
    d_func()->webApplication = project;
}

int TLab::size() const
{
    const B_D(TLab);
    if (d->desktopApplication.isValid())
        return d->desktopApplication.size();
    else if (!d->url.isEmpty())
        return d->url.length() * 2;
    else if (d->webApplication.isValid())
        return d->webApplication.size();
    else
        return 0;
}

TProjectType TLab::type() const
{
    const B_D(TLab);
    if (d->desktopApplication.isValid())
        return TProjectType::DesktopType;
    else if (!d->url.isEmpty())
        return TProjectType::UrlType;
    else if (d->webApplication.isValid())
        return TProjectType::WebType;
    else
        return TProjectType::NoType;
}

QString TLab::url() const
{
    return d_func()->url;
}

TProject &TLab::webApplication()
{
    return d_func()->webApplication;
}

const TProject &TLab::webApplication() const
{
    return d_func()->webApplication;
}

/*============================== Public operators ==========================*/

TLab &TLab::operator =(const TLab &other)
{
    B_D(TLab);
    const TLabPrivate *dd = other.d_func();
    d->desktopApplication = dd->desktopApplication;
    d->url = dd->url;
    d->webApplication = dd->webApplication;
    return *this;
}

bool TLab::operator ==(const TLab &other) const
{
    const B_D(TLab);
    const TLabPrivate *dd = other.d_func();
    return d->desktopApplication == dd->desktopApplication && d->url == dd->url
            && d->webApplication == dd->webApplication;
}

TLab::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLab &lab)
{
    const TLabPrivate *d = lab.d_func();
    QVariantMap m;
    m.insert("desktop_application", d->desktopApplication);
    m.insert("url", d->url);
    m.insert("web_application", d->webApplication);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLab &lab)
{
    TLabPrivate *d = lab.d_func();
    QVariantMap m;
    stream >> m;
    d->desktopApplication = m.value("desktop_application").value<TProject>();
    d->url = m.value("url").toString();
    d->webApplication = m.value("web_application").value<TProject>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLab &lab)
{
    dbg.nospace() << "TLab(" << lab.size() << ")";
    return dbg.space();
}
