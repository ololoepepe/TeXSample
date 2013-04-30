#ifndef TUSERINFO_H
#define TUSERINFO_H

class TUserInfoPrivate;

class QDataStream;
class QDateTime;
class QVariant;
class QDebug;
class QByteArray;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>

/*============================================================================
================================ TUserInfo ===================================
============================================================================*/

class TSMP_EXPORT TUserInfo : public BBase
{
    B_DECLARE_PRIVATE(TUserInfo)
    Q_DECLARE_TR_FUNCTIONS(TUserInfo)
public:
    enum AccessLevel
    {
        NoLevel = 0,
        UserLevel = 10,
        ModeratorLevel = 100,
        AdminLevel = 1000
    };
    enum Context
    {
        CurrentContext,
        GeneralContext,
        ShortInfoContext,
        AddContext,
        RegisterContext,
        UpdateContext,
        AuthorizeContext
    };
public:
    static QString accessLevelToString(AccessLevel lvl, bool singular = true);
public:
    explicit TUserInfo(Context c = GeneralContext);
    TUserInfo(const TUserInfo &other);
    ~TUserInfo();
public:
    void setContext(int c, bool clear = false);
    void setId(quint64 id);
    void setLogin(const QString &login);
    void setPassword(const QString &s);
    void setPassword(const QByteArray &data);
    void setAccessLevel(int lvl);
    void setRealName(const QString &name);
    void setAvatar(const QByteArray &data);
    void setCreationDateTime(const QDateTime &dt);
    void setModificationDateTime(const QDateTime &dt);
    void setUpdateDateTime(const QDateTime &dt);
    Context context() const;
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    QString login() const;
    QByteArray password() const;
    AccessLevel accessLevel() const;
    QString accessLevelString() const;
    QString realName() const;
    QByteArray avatar() const;
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime modificationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime updateDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    bool isValid(Context c = CurrentContext) const;
public:
    TUserInfo &operator =(const TUserInfo &other);
    bool operator ==(const TUserInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TUserInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TUserInfo &info);
    friend QDebug operator <<(QDebug dbg, const TUserInfo &info);
};

Q_DECLARE_METATYPE(TUserInfo)

#endif // TUSERINFO_H
