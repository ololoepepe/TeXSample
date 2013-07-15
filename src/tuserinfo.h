#ifndef TUSERINFO_H
#define TUSERINFO_H

class TUserInfoPrivate;
class TAccessLevel;

class BTranslator;

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
    enum Context
    {
        CurrentContext,
        GeneralContext,
        ShortInfoContext,
        AddContext,
        RegisterContext,
        EditContext,
        UpdateContext
    };
public:
    explicit TUserInfo(Context c = GeneralContext);
    explicit TUserInfo(quint64 id, Context c = GeneralContext);
    TUserInfo(const TUserInfo &other);
    ~TUserInfo();
public:
    void setContext(int c, bool clear = false);
    void setId(quint64 id);
    void setEmail(const QString &email);
    void setLogin(const QString &login);
    void setPassword(const QString &s);
    void setPassword(const QByteArray &data);
    void setAccessLevel(const TAccessLevel &lvl);
    void setRealName(const QString &name);
    void setAvatar(const QByteArray &data);
    void setCreationDateTime(const QDateTime &dt);
    void setModificationDateTime(const QDateTime &dt);
    void clear();
    Context context() const;
    quint64 id() const;
    QString idString(int fixedLength = -1) const;
    QString email() const;
    QString login() const;
    QByteArray password() const;
    TAccessLevel accessLevel() const;
    QString accessLevelString() const;
    QString accessLevelStringNoTr() const;
    QString realName() const;
    QByteArray avatar() const;
    QDateTime creationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    QDateTime modificationDateTime(Qt::TimeSpec spec = Qt::UTC) const;
    bool isValid(Context c = CurrentContext) const;
public:
    TUserInfo &operator =(const TUserInfo &other);
    bool operator ==(const TUserInfo &other) const;
    bool operator !=(const TUserInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TUserInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TUserInfo &info);
    friend QDebug operator <<(QDebug dbg, const TUserInfo &info);
};

Q_DECLARE_METATYPE(TUserInfo)

#endif // TUSERINFO_H
