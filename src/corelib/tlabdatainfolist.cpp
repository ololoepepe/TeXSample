#include "tlabdatainfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TLabDataInfoList ============================
============================================================================*/

/*============================== Public operators ==========================*/

TLabDataInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
