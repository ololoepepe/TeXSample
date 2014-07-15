#ifndef TLABDATAINFOLIST_H
#define TLABDATAINFOLIST_H

#include "tlabdatainfo.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TLabDataInfoList ============================
============================================================================*/

class T_CORE_EXPORT TLabDataInfoList : public QList<TLabDataInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TLabDataInfoList)


#endif // TLABDATAINFOLIST_H
