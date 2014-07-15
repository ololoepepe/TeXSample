#ifndef TLABINFO_H
#define TLABINFO_H

class TLabInfoPrivate;

class TAuthorInfoList;
class TFileInfoList;
class TIdList;
class TLabDataInfoList;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TLabInfo ====================================
============================================================================*/

class T_CORE_EXPORT TLabInfo : public BBase
{
    B_DECLARE_PRIVATE(TLabInfo)
public:
    explicit TLabInfo();
    TLabInfo(const TLabInfo &other);
    ~TLabInfo();
protected:
    explicit TLabInfo(TLabInfoPrivate &d);
public:
    TAuthorInfoList authors() const;
    QDateTime creationDateTime() const;
    TLabDataInfoList dataInfos() const;
    QString description() const;
    TFileInfoList extraFiles() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    quint64 senderId() const;
    QString senderLogin() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setCreationDateTime(const QDateTime &dt);
    void setDataInfos(const TLabDataInfoList &dataInfos);
    void setDescription(const QString &description);
    void setExtraFiles(const TFileInfoList &extraFiles);
    void setGroups(const TIdList &groups);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setSenderId(quint64 id);
    void setSenderLogin(const QString &login);
    void setTags(const QStringList &list);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TLabInfo &operator =(const TLabInfo &other);
    bool operator ==(const TLabInfo &other) const;
    bool operator !=(const TLabInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TLabInfo &info);
    friend QDebug operator <<(QDebug dbg, const TLabInfo &info);
};

Q_DECLARE_METATYPE(TLabInfo)

#endif // TLABINFO_H
