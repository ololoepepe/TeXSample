#ifndef TTEXFILELIST_H
#define TTEXFILELIST_H

class QVariant;

#include "ttexfile.h"

#include <QList>
#include <QMetaType>

/*============================================================================
================================ TFileList ===================================
============================================================================*/

class T_CORE_EXPORT TTexFileList : public QList<TTexFile>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TTexFileList)

#endif // TTEXFILELIST_H
