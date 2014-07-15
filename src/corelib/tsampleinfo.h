#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H

class TSampleInfoPrivate;

class TAuthorInfoList;
class TFileInfo;
class TFileInfoList;
class TSampleType;

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
================================ TSampleInfo =================================
============================================================================*/

class T_CORE_EXPORT TSampleInfo : public BBase
{
    B_DECLARE_PRIVATE(TSampleInfo)
public:
    explicit TSampleInfo();
    TSampleInfo(const TSampleInfo &other);
    ~TSampleInfo();
protected:
    explicit TSampleInfo(TSampleInfoPrivate &d);
public:
    QString adminRemark() const;
    TAuthorInfoList authors() const;
    QDateTime creationDateTime() const;
    QString description() const;
    TFileInfoList extraPreviewFiles() const;
    TFileInfoList extraSourceFiles() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    TFileInfo mainPreviewFile() const;
    TFileInfo mainSourceFile() const;
    int previewSize() const;
    quint8 rating() const;
    quint64 senderId() const;
    QString senderLogin() const;
    void setAdminRemark(const QString &remark);
    void setAuthors(const TAuthorInfoList &authors);
    void setCreationDateTime(const QDateTime &dt);
    void setDescription(const QString &description);
    void setExtraPreviewFiles(const TFileInfoList &files);
    void setExtraSourceFiles(const TFileInfoList &files);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setMainPreviewFile(const TFileInfo &file);
    void setMainSourceFile(const TFileInfo &file);
    void setRating(quint8 r);
    void setSenderId(quint64 id);
    void setSenderLogin(const QString &login);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    void setType(const TSampleType &type);
    int sourceSize() const;
    QStringList tags() const;
    QString title() const;
    TSampleType type() const;
public:
    TSampleInfo &operator =(const TSampleInfo &other);
    bool operator ==(const TSampleInfo &other) const;
    bool operator !=(const TSampleInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSampleInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TSampleInfo &info);
    friend QDebug operator <<(QDebug dbg, const TSampleInfo &info);
};

Q_DECLARE_METATYPE(TSampleInfo)

#endif // TSAMPLEINFO_H
