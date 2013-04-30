#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H

class TSampleInfoPrivate;

class QDataStream;
class QStringList;
class QDateTime;
class QVariant;
class QDebug;

#include "tglobal.h"
#include "tuserinfo.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>
#include <QCoreApplication>
#include <QList>

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

class TSMP_EXPORT TSampleInfo : public BBase
{
    B_DECLARE_PRIVATE(TSampleInfo)
    Q_DECLARE_TR_FUNCTIONS(TSampleInfo)
public:
    typedef QList<TSampleInfo> SamplesList;
public:
    enum Type
    {
        Unverified = 0,
        Approved = 10,
        Rejected = 100
    };
    enum Context
    {
        CurrentContext,
        GeneralContext,
        AddContext,
        UpdateContext
    };
public:
    static QString typeToString(Type t, bool singular = true);
    static QString tagsToString(const QStringList &tags);
    static QStringList tagsFromString(const QString &s);
public:
    explicit TSampleInfo(Context c = GeneralContext);
    TSampleInfo(const TSampleInfo &other);
    ~TSampleInfo();
protected:
    explicit TSampleInfo(TSampleInfoPrivate &d);
public:
    void setContext(int c, bool clear = false);
    void setId(quint64 id);
    void setAuthor(const TUserInfo &author);
    void setExtraAuthors(const QList<TUserInfo> &list);
    void setTitle(const QString &title);
    void setType(Type t);
    void setFileName(const QString &fileName);
    void setTags(const QStringList &list);
    void setTags(const QString &s);
    void setComment(const QString &s);
    void setAdminRemark(const QString &s);
    void setRating(quint8 r);
    void setCreationDateTime(const QDateTime &dt);
    void setModificationDateTime(const QDateTime &dt);
    void setUpdateDateTime(const QDateTime &dt);
    Context context() const;
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    TUserInfo author() const;
    QList<TUserInfo> extraAuthors() const;
    QString title() const;
    Type type() const;
    QString typeString() const;
    QString fileName() const;
    QStringList tags() const;
    QString tagsString() const;
    QString comment() const;
    QString adminRemark() const;
    quint8 rating() const;
    QString ratingString(const QString &format = "") const; //%r - rating
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime modificationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime updateDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    bool isValid(Context c = CurrentContext) const;
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
