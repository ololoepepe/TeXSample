#include "tuserinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TUserInfoList ===============================
============================================================================*/

/*============================== Public operators ==========================*/

TUserInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
