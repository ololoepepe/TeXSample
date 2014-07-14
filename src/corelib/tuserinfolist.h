#ifndef TUSERINFOLIST_H
#define TUSERINFOLIST_H

class QVariant;

#include "tuserinfo.h"

#include <QList>
#include <QMetaType>

/*============================================================================
================================ TUserInfoList ===============================
============================================================================*/

class T_CORE_EXPORT TUserInfoList : public QList<TUserInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TUserInfoList)

#endif // TUSERINFOLIST_H
