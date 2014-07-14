#include "tfileinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TFileInfoList =============================
============================================================================*/

/*============================== Public operators ==========================*/

TFileInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
