#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H

class TSampleInfoPrivate;

class QDataStream;
class QStringList;
class QDateTime;
class QVariant;
class QDebug;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>
#include <QCoreApplication>

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

class TSMP_EXPORT TSampleInfo : public BBase
{
    B_DECLARE_PRIVATE(TSampleInfo)
    Q_DECLARE_TR_FUNCTIONS(TSampleInfo)
public:
    enum Type
    {
        Unverified = 0,
        Approved = 10,
        Rejected = 100
    };
public:
    static QString typeToString(Type t, bool singular = true);
    static QString tagsToString(const QStringList &tags);
    static QStringList tagsFromString(const QString &s);
public:
    explicit TSampleInfo();
    TSampleInfo(const TSampleInfo &other);
    ~TSampleInfo();
protected:
    explicit TSampleInfo(TSampleInfoPrivate &d);
public:
    void setId(quint64 id);
    void setAuthorId(quint64 id);
    void setAuthorName(const QString &name);
    void setTitle(const QString &title);
    void setType(Type t);
    void setTags(const QStringList &list);
    void setComment(const QString &s);
    void setAdminRemark(const QString &s);
    void setRating(quint8 r);
    void setCreationDateTime(const QDateTime &dt);
    void setModificationDateTime(const QDateTime &dt);
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    quint64 authorId() const;
    QString authorIdString(int fixedLength = -1) const;
    QString authorName() const;
    QString title() const;
    Type type() const;
    QString typeString() const;
    QStringList tags() const;
    QString tagsString() const;
    QString comment() const;
    QString adminRemark() const;
    quint8 rating() const;
    QString ratingString(const QString &format = "%r") const;
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime modificationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    bool isValid() const;
public:
    TSampleInfo &operator =(const TSampleInfo &other);
    bool operator ==(const TSampleInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSampleInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TSampleInfo &info);
    friend QDebug operator <<(QDebug dbg, const TSampleInfo &info);
};

Q_DECLARE_METATYPE(TSampleInfo)

#endif // TSAMPLEINFO_H
