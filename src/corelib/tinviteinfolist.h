#ifndef TINVITEINFOLIST_H
#define TINVITEINFOLIST_H

#include "tinviteinfo.h"

#include <QList>
#include <QMetaType>
#include <QVariant>

/*============================================================================
================================ TInviteInfoList =============================
============================================================================*/

class T_CORE_EXPORT TInviteInfoList : public QList<TInviteInfo>
{
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TInviteInfoList)

#endif // TINVITEINFOLIST_H
