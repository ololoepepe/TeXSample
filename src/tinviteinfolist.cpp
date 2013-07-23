#include "tinviteinfolist.h"

#include <QList>
#include <QVariant>

/*============================================================================
================================ TInviteInfoList =============================
============================================================================*/

/*============================== Public operators ==========================*/

TInviteInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
