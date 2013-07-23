#ifndef TCOMPILEDPROJECT_H
#define TCOMPILEDPROJECT_H

class TCompiledProjectPrivate;

class QVariant;
class QDebug;
class QDataStream;
class QString;

#include "tglobal.h"
#include "tprojectfile.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>
#include <QStringList>

/*============================================================================
================================ TCompiledProject ============================
============================================================================*/

class TSMP_EXPORT TCompiledProject : BBase
{
    B_DECLARE_PRIVATE(TCompiledProject)
public:
    explicit TCompiledProject(const QString &dir = QString(), const QStringList &nameFilters = QStringList());
    explicit TCompiledProject(const QStringList &files);
    TCompiledProject(const TCompiledProject &other);
    ~TCompiledProject();
public:
    void clear();
    QList<TProjectFile> *files();
    const QList<TProjectFile> *files() const;
    bool load(const QString &dir, const QStringList &nameFilters = QStringList());
    bool load(const QStringList &files);
    bool save(const QString &dir) const;
    bool isEmpty() const;
    bool isValid() const;
    int size() const;
public:
    TCompiledProject &operator =(const TCompiledProject &other);
    bool operator ==(const TCompiledProject &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompiledProject &project);
    friend QDataStream &operator >>(QDataStream &stream, TCompiledProject &project);
    friend QDebug operator <<(QDebug dbg, const TCompiledProject &project);
};

Q_DECLARE_METATYPE(TCompiledProject)

#endif // TCOMPILEDPROJECT_H
