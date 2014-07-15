#ifndef TPROJECT_H
#define TPROJECT_H

class TProjectPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>
#include <QStringList>

/*============================================================================
================================ TProject ====================================
============================================================================*/

class T_CORE_EXPORT TProject : BBase
{
    B_DECLARE_PRIVATE(TProject)
public:
    explicit TProject();
    explicit TProject(const QString &dir, const QString &relativeMainFileName,
                      const QStringList &relativeFileNames = QStringList());
    TProject(const TProject &other);
    ~TProject();
public:
    void clear();
    bool isValid() const;
    bool load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames = QStringList());
    bool mayBeExecutable() const;
    bool save(const QString &dir) const;
    int size() const;
public:
    TProject &operator =(const TProject &other);
    bool operator ==(const TProject &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TProject &project);
    friend QDataStream &operator >>(QDataStream &stream, TProject &project);
    friend QDebug operator <<(QDebug dbg, const TProject &project);
};

Q_DECLARE_METATYPE(TProject)

#endif // TPROJECT_H
