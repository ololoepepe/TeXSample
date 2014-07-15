#ifndef TLABINFOLIST_H
#define TLABINFOLIST_H

class QVariant;

#include "tlabinfo.h"

#include <QList>
#include <QMetaType>

/*============================================================================
================================ TLabInfoList ================================
============================================================================*/

class T_CORE_EXPORT TLabInfoList : public QList<TLabInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TLabInfoList)


#endif // TLABINFOLIST_H
