#ifndef TLABAPPLICATION_H
#define TLABAPPLICATION_H

class TLabApplicationPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>
#include <QStringList>

/*============================================================================
================================ TLabApplication ====================================
============================================================================*/

class T_CORE_EXPORT TLabApplication : BBase
{
    B_DECLARE_PRIVATE(TLabApplication)
public:
    explicit TLabApplication();
    TLabApplication(const TLabApplication &other);
    ~TLabApplication();
public:
    void clear();
    bool isValid() const;
    bool load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames = QStringList());
    bool mayBeExecutable() const;
    BeQt::OSType os() const;
    bool save(const QString &dir) const;
    void setOsType(BeQt::OSType os);
    int size() const;
public:
    TLabApplication &operator =(const TLabApplication &other);
    bool operator ==(const TLabApplication &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabApplication &project);
    friend QDataStream &operator >>(QDataStream &stream, TLabApplication &project);
    friend QDebug operator <<(QDebug dbg, const TLabApplication &project);
};

Q_DECLARE_METATYPE(TLabApplication)

#endif // TLABAPPLICATION_H
