#ifndef TSERVICELIST_H
#define TSERVICELIST_H

#include "tservice.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TServiceList ================================
============================================================================*/

class TSMP_EXPORT TServiceList : public QList<TService>
{
public:
    static TServiceList serviceListFromIntList(const QList<int> &list);
    static TServiceList allServices();
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TServiceList)

#endif // TSERVICELIST_H
