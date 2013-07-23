#include "tprojectfilelist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TProjectFileList ============================
============================================================================*/

/*============================== Public operators ==========================*/

TProjectFileList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
