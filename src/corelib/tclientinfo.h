#ifndef TCLIENTINFO_H
#define TCLIENTINFO_H

class TClientInfoPrivate;

class BVersion;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

class T_CORE_EXPORT TClientInfo : public BBase
{
    B_DECLARE_PRIVATE(TClientInfo)
public:
    explicit TClientInfo();
    TClientInfo(const TClientInfo &other);
    ~TClientInfo();
public:
    static TClientInfo create();
public:
    QString applicationName() const;                        //%n
    BVersion applicationVersion() const;                    //%v
    BVersion beqtVersion() const;                           //%b
    bool isPortable() const;                                //%p
    bool isValid() const;
    QString os() const;                                     //%o
    BeQt::OSType osType() const;
    BeQt::ProcessorArchitecture processorArchitecture() const;
    BVersion qtVersion() const;                             //%q
    BVersion texsampleVersion() const;                      //%t
    QString toString(const QString &format = "%n v%v (%p)\nTeXSample v%t; BeQt v%b; Qt v%q\nOS: %o") const;
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
