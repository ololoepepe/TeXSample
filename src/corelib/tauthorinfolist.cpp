#include "tauthorinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TAuthorInfoList =============================
============================================================================*/

/*============================== Public operators ==========================*/

TAuthorInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
