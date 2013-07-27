#include "tlabinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TLabInfoList ================================
============================================================================*/

/*============================== Public operators ==========================*/

TLabInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
