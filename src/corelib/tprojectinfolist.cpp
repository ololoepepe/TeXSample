#include "tprojectinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TProjectInfoList ============================
============================================================================*/

/*============================== Public operators ==========================*/

TProjectInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
