#ifndef TGETINVITEINFOLISTREQUESTDATA_H
#define TGETINVITEINFOLISTREQUESTDATA_H

class TGetInviteInfoListRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetInviteInfoListRequestData ===============
============================================================================*/

class T_CORE_EXPORT TGetInviteInfoListRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetInviteInfoListRequestData)
public:
    explicit TGetInviteInfoListRequestData();
    TGetInviteInfoListRequestData(const TGetInviteInfoListRequestData &other);
    ~TGetInviteInfoListRequestData();
public:
    TGetInviteInfoListRequestData &operator =(const TGetInviteInfoListRequestData &other);
    bool operator ==(const TGetInviteInfoListRequestData &other) const;
    bool operator !=(const TGetInviteInfoListRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetInviteInfoListRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetInviteInfoListRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetInviteInfoListRequestData &data);
};

Q_DECLARE_METATYPE(TGetInviteInfoListRequestData)

#endif // TGETINVITEINFOLISTREQUESTDATA_H
