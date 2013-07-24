#include "tservicelist.h"

#include <BeQtGlobal>

#include <QList>
#include <QVariant>
#include <QString>
#include <QStringList>

/*============================================================================
================================ TServiceList ================================
============================================================================*/

/*============================== Static public methods =====================*/

TServiceList TServiceList::serviceListFromIntList(const QList<int> &list)
{
    TServiceList nlist;
    foreach (int srv, list)
        nlist << TService(srv);
    bRemoveDuplicates(nlist);
    return nlist;
}

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

QString TServiceList::toString(const QString &separator) const
{
    return toStringList().join(separator);
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
