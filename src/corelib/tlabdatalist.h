#ifndef TLABDATALIST_H
#define TLABDATALIST_H

#include "tlabdata.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TLabDataList ================================
============================================================================*/

class T_CORE_EXPORT TLabDataList : public QList<TLabData>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TLabDataList)


#endif // TLABDATALIST_H
