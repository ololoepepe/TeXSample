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

QStringList TServiceList::serviceListToStringList(const TServiceList &list)
{
    QStringList sl;
    foreach (const TService &s, list)
        sl << s.toString();
    return sl;
}

QStringList TServiceList::serviceListToStringListNoTr(const TServiceList &list)
{
    QStringList sl;
    foreach (const TService &s, list)
        sl << s.toStringNoTr();
    return sl;
}

QString TServiceList::serviceListToString(const TServiceList &list, const QString &separator)
{
    return serviceListToStringList(list).join(separator);
}

QString TServiceList::serviceListToStringNoTr(const TServiceList &list, const QString &separator)
{
    return serviceListToStringListNoTr(list).join(separator);
}

/*============================== Public operators ==========================*/

TServiceList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
