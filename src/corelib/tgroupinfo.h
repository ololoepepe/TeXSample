#ifndef TGROUPINFO_H
#define TGROUPINFO_H

class TGroupInfoPrivate;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGroupInfo ==================================
============================================================================*/

class T_CORE_EXPORT TGroupInfo : public BBase
{
    B_DECLARE_PRIVATE(TGroupInfo)
public:
    explicit TGroupInfo();
    TGroupInfo(const TGroupInfo &other);
    ~TGroupInfo();
public:
    void clear();
    QDateTime creationDateTime() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    QString name() const;
    quint64 ownerId() const;
    QString ownerLogin() const;
    void setCreationDateTime(const QDateTime &dt);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setName(const QString &name);
    void setOwnerId(quint64 ownerId);
    void setOwnerLogin(const QString &login);
public:
    TGroupInfo &operator =(const TGroupInfo &other);
    bool operator ==(const TGroupInfo &other) const;
    bool operator !=(const TGroupInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGroupInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TGroupInfo &info);
    friend QDebug operator <<(QDebug dbg, const TGroupInfo &info);
};

Q_DECLARE_METATYPE(TGroupInfo)

#endif // TGROUPINFO_H
