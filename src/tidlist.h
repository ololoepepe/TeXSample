#ifndef TIDLIST_H
#define TIDLIST_H

#include "tglobal.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TIdList =====================================
============================================================================*/

class TSMP_EXPORT TIdList : public QList<quint64>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TIdList)

#endif // TIDLIST_H
