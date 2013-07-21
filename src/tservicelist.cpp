#include "tservicelist.h"

#include <BeQtGlobal>

#include <QList>
#include <QVariant>

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

TServiceList TServiceList::allServices()
{
    TServiceList list;
    list << TService::TexsampleService;
    return list;
}

/*============================== Public operators ==========================*/

TServiceList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
