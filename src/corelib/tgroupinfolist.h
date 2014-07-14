#ifndef TGROUPINFOLIST_H
#define TGROUPINFOLIST_H

#include "tglobal.h"
#include "tgroupinfo.h"

#include <QList>
#include <QMetaType>
#include <QStringList>
#include <QVariant>

/*============================================================================
================================ TGroupInfoList ==============================
============================================================================*/

class T_CORE_EXPORT TGroupInfoList : public QList<TGroupInfo>
{
public:
    QStringList names() const;
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TGroupInfoList)

#endif // TGROUPINFOLIST_H
