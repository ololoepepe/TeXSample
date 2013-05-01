#ifndef TINVITEINFO_H
#define TINVITEINFO_H

class TInviteInfoPrivate;

class QDataStream;
class QDateTime;
class QVariant;
class QDebug;
class QUuid;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QList>

/*============================================================================
================================ TInviteInfo =================================
============================================================================*/

class TSMP_EXPORT TInviteInfo : public BBase
{
    B_DECLARE_PRIVATE(TInviteInfo)
public:
    typedef QList<TInviteInfo> InvitesList;
public:
    explicit TInviteInfo();
    TInviteInfo(const TInviteInfo &other);
    ~TInviteInfo();
public:
    void setId(quint64 id);
    void setUuid(const QUuid &uuid);
    void setUuid(const QString &s);
    void setCreatorId(quint64 id);
    void setCreationDateTime(const QDateTime &dt);
    void setExpirationDateTime(const QDateTime &dt);
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    QUuid uuid() const;
    QString uuidString(bool pure = true) const;
    quint64 creatorId() const;
    QString creatorIdString(int fixedLength = -1) const;
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime expirationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    bool isValid() const;
public:
    TInviteInfo &operator =(const TInviteInfo &other);
    bool operator ==(const TInviteInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TInviteInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TInviteInfo &info);
    friend QDebug operator <<(QDebug dbg, const TInviteInfo &info);
};

Q_DECLARE_METATYPE(TInviteInfo)
Q_DECLARE_METATYPE(TInviteInfo::InvitesList)

#endif // TINVITEINFO_H
