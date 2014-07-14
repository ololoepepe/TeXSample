#include "tbinaryfilelist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TBinaryFileList =============================
============================================================================*/

/*============================== Public operators ==========================*/

TBinaryFileList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
