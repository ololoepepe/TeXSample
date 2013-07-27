#ifndef TLABINFOLIST_H
#define TLABINFOLIST_H

#include "tlabinfo.h"
#include "tglobal.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

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
