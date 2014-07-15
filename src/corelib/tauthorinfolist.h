#ifndef TAUTHORINFOLIST_H
#define TAUTHORINFOLIST_H

#include "tauthorinfo.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TAuthorInfoList =============================
============================================================================*/

class T_CORE_EXPORT TAuthorInfoList : public QList<TAuthorInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TAuthorInfoList)


#endif // TAUTHORINFOLIST_H
