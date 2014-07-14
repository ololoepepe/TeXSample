#ifndef TLABPROJECT_H
#define TLABPROJECT_H

class TLabProjectPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>
#include <QStringList>

/*============================================================================
================================ TLabProject =================================
============================================================================*/

class T_CORE_EXPORT TLabProject : BBase
{
    B_DECLARE_PRIVATE(TLabProject)
public:
    explicit TLabProject();
    explicit TLabProject(const QString &dir, const QString &relativeMainFileName,
                         const QStringList &relativeFileNames = QStringList());
    TLabProject(const TLabProject &other);
    ~TLabProject();
public:
    void clear();
    bool isValid() const;
    bool load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames = QStringList());
    bool mayBeExecutable() const;
    bool save(const QString &dir) const;
    int size() const;
public:
    TLabProject &operator =(const TLabProject &other);
    bool operator ==(const TLabProject &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabProject &project);
    friend QDataStream &operator >>(QDataStream &stream, TLabProject &project);
    friend QDebug operator <<(QDebug dbg, const TLabProject &project);
};

Q_DECLARE_METATYPE(TLabProject)

#endif // TLABPROJECT_H
