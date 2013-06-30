#ifndef TPROJECTFILELIST_H
#define TPROJECTFILELIST_H

#include "tprojectfile.h"

#include <QList>
#include <QMetaType>

typedef QList<TProjectFile> TProjectFileList;

Q_DECLARE_METATYPE(TProjectFileList)

#endif // TPROJECTFILELIST_H
