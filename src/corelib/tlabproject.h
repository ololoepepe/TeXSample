#ifndef TLABPROJECT_H
#define TLABPROJECT_H

class TLabProjectPrivate;

class QVariant;
class QDebug;
class QDataStream;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TLabProject =================================
============================================================================*/

class T_CORE_EXPORT TLabProject : BBase
{
    B_DECLARE_PRIVATE(TLabProject)
public:
    static int size(const QString &dir);
public:
    explicit TLabProject();
    explicit TLabProject(const QString &dir, const QString &mainFileName);
    explicit TLabProject(const QString &mainFilePath);
    TLabProject(const TLabProject &other);
    ~TLabProject();
public:
    void clear();
    QString mainFileName() const;
    QString mainFileSubdir() const;
    QString mainFilePath(const QString &path) const;
    bool load(const QString &dir, const QString &mainFileName);
    bool load(const QString &mainFilePath);
    bool save(const QString &dir) const;
    bool isExecutable() const;
    bool isValid() const;
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
