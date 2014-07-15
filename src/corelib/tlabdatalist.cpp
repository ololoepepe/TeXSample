#include "tlabdatalist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TLabDataList =============================
============================================================================*/

/*============================== Public operators ==========================*/

TLabDataList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
