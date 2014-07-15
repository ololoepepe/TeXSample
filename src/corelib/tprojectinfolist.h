#ifndef TPROJECTINFOLIST_H
#define TPROJECTINFOLIST_H

#include "tprojectinfo.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TProjectInfoList ============================
============================================================================*/

class T_CORE_EXPORT TProjectInfoList : public QList<TProjectInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TProjectInfoList)


#endif // TPROJECTINFOLIST_H
