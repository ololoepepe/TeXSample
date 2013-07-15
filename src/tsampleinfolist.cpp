#include "tsampleinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TSampleInfoList =============================
============================================================================*/

/*============================== Public operators ==========================*/

TSampleInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
