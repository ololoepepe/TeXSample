#ifndef TSAMPLEINFOLIST_H
#define TSAMPLEINFOLIST_H

#include "tsampleinfo.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TSampleInfoList =============================
============================================================================*/

class TSMP_EXPORT TSampleInfoList : public QList<TSampleInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TSampleInfoList)

#endif // TSAMPLEINFOLIST_H
