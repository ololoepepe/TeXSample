#include "tgroupinfolist.h"

#include "tgroupinfo.h"

#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

/*============================================================================
================================ TGroupInfoList ==============================
============================================================================*/

/*============================== Public methods ============================*/

QStringList TGroupInfoList::names() const
{
    QStringList sl;
    foreach (const TGroupInfo &info, *this)
        sl << info.name();
    return sl;
}

/*============================== Public operators ==========================*/

TGroupInfoList::operator QVariant() const
{
    return QVariant::fromValue(*this);
}
