#ifndef TGETUSERAVATARREPLYDATA_H
#define TGETUSERAVATARREPLYDATA_H

class TGetUserAvatarReplyDataPrivate;

class QDataStream;
class QDebug;
class QImage;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserAvatarReplyData =====================
============================================================================*/

class T_CORE_EXPORT TGetUserAvatarReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserAvatarReplyData)
public:
    explicit TGetUserAvatarReplyData();
    TGetUserAvatarReplyData(const TGetUserAvatarReplyData &other);
    ~TGetUserAvatarReplyData();
public:
    QImage avatar() const;
    void setAvatar(const QImage &avatar);
public:
    TGetUserAvatarReplyData &operator =(const TGetUserAvatarReplyData &other);
    bool operator ==(const TGetUserAvatarReplyData &other) const;
    bool operator !=(const TGetUserAvatarReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserAvatarReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserAvatarReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserAvatarReplyData &data);
};

Q_DECLARE_METATYPE(TGetUserAvatarReplyData)

#endif // TGETUSERAVATARREPLYDATA_H
