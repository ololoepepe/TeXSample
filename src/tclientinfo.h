#ifndef TCLIENTINFO_H
#define TCLIENTINFO_H

class TClientInfoPrivate;

class QDataStream;
class QDateTime;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>
#include <QLocale>

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

class TSMP_EXPORT TClientInfo : public BBase
{
    B_DECLARE_PRIVATE(TClientInfo)
    Q_DECLARE_TR_FUNCTIONS(TClientInfo)
public:
    static TClientInfo createDefaultInfo();
    static int compareVersions(const QString &v1, const QString &v2, bool ignoreSuffix = false);
public:
    explicit TClientInfo();
    TClientInfo(const TClientInfo &other);
    ~TClientInfo();
public:
    void setOS(const QString &os);
    void setLocale(const QLocale &l);
    void setClient(const QString &name);
    void setClientVersion(const QString &v);
    void setEditorVersion(const QString &v);
    void setTexsampleVersion(const QString &v);
    void setBeqtVersion(const QString &v);
    void setQtVersion(const QString &v);
    QString os() const;
    QLocale locale() const;
    QString client() const;
    QString clientVersion() const;
    QString editorVersion() const;
    QString texsampleVersion() const;
    QString beqtVersion() const;
    QString qtVersion() const;
    QString toString(const QString &format = "") const;
    //%o - OS, %l - locale, %c - client, %v - client version
    //%t - texsample version, %b - BeQt version, %q - Qt version
    bool isValid() const;
public:
    TClientInfo &operator =(const TClientInfo &other);
    bool operator ==(const TClientInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TClientInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TClientInfo &info);
    friend QDebug operator <<(QDebug dbg, const TClientInfo &info);
};

Q_DECLARE_METATYPE(TClientInfo)

#endif // TCLIENTINFO_H
