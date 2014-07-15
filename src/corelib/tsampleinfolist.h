#ifndef TSAMPLEINFOLIST_H
#define TSAMPLEINFOLIST_H

class QVariant;

#include "tsampleinfo.h"

#include <QList>
#include <QMetaType>

/*============================================================================
================================ TSampleInfoList =============================
============================================================================*/

class T_CORE_EXPORT TSampleInfoList : public QList<TSampleInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TSampleInfoList)

#endif // TSAMPLEINFOLIST_H
