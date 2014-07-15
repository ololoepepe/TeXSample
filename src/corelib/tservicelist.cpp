#include "tservicelist.h"

#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

/*============================================================================
================================ TServiceList ================================
============================================================================*/

/*============================== Static public methods =====================*/

TServiceList TServiceList::allServices(bool includeNoService)
{
    TServiceList list;
    if (includeNoService)
        list << TService::NoService;
    list << TService::TexsampleService;
    list << TService::ClabService;
    return list;
}

/*============================== Public methods ============================*/

QString TServiceList::toString(const QString &separator) const
{
    return toStringList().join(separator);
}

QStringList TServiceList::toStringList() const
{
    QStringList sl;
    foreach (const TService &s, *this)
        sl << s.toString();
    return sl;
}

QStringList TServiceList::toStringListNoTr() const
{
    QStringList sl;
    foreach (const TService &s, *this)
        sl << s.toStringNoTr();
    return sl;
}

QString TServiceList::toStringNoTr(const QString &separator) const
{
    return toStringListNoTr().join(separator);
}

/*============================== Public operators ==========================*/

TServiceList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
