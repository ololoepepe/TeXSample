#ifndef TPROJECTFILELIST_H
#define TPROJECTFILELIST_H

#include "tprojectfile.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TProjectFileList ============================
============================================================================*/

class T_CORE_EXPORT TProjectFileList : public QList<TProjectFile>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TProjectFileList)

#endif // TPROJECTFILELIST_H
