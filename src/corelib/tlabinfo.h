#ifndef TLABINFO_H
#define TLABINFO_H

class TLabInfoPrivate;

class QDataStream;
class QStringList;
class QDateTime;
class QVariant;
class QDebug;

#include "tglobal.h"
#include "tuserinfo.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQt>

#include <QMetaType>
#include <QString>
#include <QCoreApplication>

/*============================================================================
================================ TLabInfo ====================================
============================================================================*/

class T_CORE_EXPORT TLabInfo : public BBase
{
    B_DECLARE_PRIVATE(TLabInfo)
    Q_DECLARE_TR_FUNCTIONS(TLabInfo)
public:
    enum Type
    {
        NoType = 0,
        DesktopType,
        WebType,
        UrlType
    };
    enum Context
    {
        CurrentContext,
        GeneralContext,
        AddContext,
        EditContext
    };
public:
    static QString typeToString(Type t, bool singular = true);
    static QString typeToStringNoTr(Type t, bool singular = true);
    static QString listToString(const QStringList &list);
    static QStringList listFromString(const QString &s);
    static Type typeFromInt(int t);
    static QList<Type> allTypes(bool includeNoType = false);
public:
    explicit TLabInfo(Context c = GeneralContext);
    TLabInfo(const TLabInfo &other);
    ~TLabInfo();
protected:
    explicit TLabInfo(TLabInfoPrivate &d);
public:
    void setContext(int c, bool clear = false);
    void setId(quint64 id);
    //void setSender(const TUserInfo &sender);
    void setTitle(const QString &title);
    void setAuthors(const QStringList &list);
    void setType(int t);
    void setGroups(const QStringList &list);
    void setProjectSize(int sz);
    void setTags(const QStringList &list);
    void setTags(const QString &s);
    void setComment(const QString &s);
    void setCreationDateTime(const QDateTime &dt);
    void setUpdateDateTime(const QDateTime &dt);
    void setExtraAttachedFileNames(const QStringList &list);
    Context context() const;
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    //TUserInfo sender() const;
    QString title() const;
    QStringList authors() const;
    Type type() const;
    QString typeString() const;
    QString typeStringNoTr() const;
    QStringList groups() const;
    int projectSize() const;
    QString projectSizeString(BeQt::FileSizeFormat format = BeQt::KilobytesFormat, quint8 precision = 1) const;
    QString projectSizeStringNoTr(BeQt::FileSizeFormat format = BeQt::KilobytesFormat, quint8 precision = 1) const;
    QStringList tags() const;
    QString tagsString() const;
    QString comment() const;
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime updateDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QStringList extraAttachedFileNames() const;
    bool isValid(Context c = CurrentContext) const;
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
