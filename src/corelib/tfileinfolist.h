#ifndef TFILEINFOLIST_H
#define TFILEINFOLIST_H

#include "tfileinfo.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TFileInfoList ===============================
============================================================================*/

class T_CORE_EXPORT TFileInfoList : public QList<TFileInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TFileInfoList)

#endif // TFILEINFOLIST_H
