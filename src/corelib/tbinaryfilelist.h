#ifndef TBINARYFILELIST_H
#define TBINARYFILELIST_H

class QVariant;

#include "tbinaryfile.h"

#include <QList>
#include <QMetaType>

/*============================================================================
================================ TBinaryFileList =============================
============================================================================*/

class T_CORE_EXPORT TBinaryFileList : public QList<TBinaryFile>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TBinaryFileList)

#endif // TBINARYFILELIST_H
