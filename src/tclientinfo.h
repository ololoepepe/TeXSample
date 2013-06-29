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

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

class TSMP_EXPORT TClientInfo : public BBase
{
    B_DECLARE_PRIVATE(TClientInfo)
    Q_DECLARE_TR_FUNCTIONS(TClientInfo)
public:
    static TClientInfo createDefaultInfo();
public:
    explicit TClientInfo();
    TClientInfo(const TClientInfo &other);
    ~TClientInfo();
public:
    void setOS(const QString &os);
    void setEditorVersion(const QString &v);
    void setTexsampleVersion(const QString &v);
    void setBeqtVersion(const QString &v);
    void setQtVersion(const QString &v);
    QString os() const;
    QString editorVersion() const;
    QString texsampleVersion() const;
    QString beqtVersion() const;
    QString qtVersion() const;
    QString toString(const QString &format = "") const; //%o - OS, %v - version, %t - texsample, %b - BeQt, %q - qt
    //%c - client
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
