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
#include "tservicelist.h"

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
    explicit TInviteInfo();
    TInviteInfo(const TInviteInfo &other);
    ~TInviteInfo();
public:
    void setId(quint64 id);
    void setCode(const QUuid &code);
    void setCode(const QString &code);
    void setCreatorId(quint64 id);
    void setServices(const TServiceList &list);
    void setCreationDateTime(const QDateTime &dt);
    void setExpirationDateTime(const QDateTime &dt);
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    QUuid code() const;
    QString codeString() const;
    quint64 creatorId() const;
    QString creatorIdString(int fixedLength = -1) const;
    TServiceList services() const;
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime expirationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    bool isExpired() const;
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

#endif // TINVITEINFO_H
