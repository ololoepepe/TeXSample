#ifndef TTEXPROJECT_H
#define TTEXPROJECT_H

class TTexProjectPrivate;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QTextCodec;
class QVariant;

#include "tbinaryfile.h"
#include "ttexfile.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TTexProject =================================
============================================================================*/

class T_CORE_EXPORT TTexProject : BBase
{
    B_DECLARE_PRIVATE(TTexProject)
public:
    explicit TTexProject();
    TTexProject(const TTexProject &other);
    ~TTexProject();
public:
    QList<TBinaryFile> &binaryFiles();
    const QList<TBinaryFile> &binaryFiles() const;
    void clear();
    bool isValid() const;
    bool load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec = 0);
    bool load(const QString &rootFileName, QTextCodec *codec = 0);
    bool prependExternalFileNames(const QString &subpath);
    void removeRestrictedCommands();
    QStringList restrictedCommands() const;
    TTexFile &rootFile();
    const TTexFile &rootFile() const;
    bool save(const QString &dir, QTextCodec *codec = 0) const;
    int size() const;
    QList<TTexFile> &texFiles();
    const QList<TTexFile> &texFiles() const;
public:
    TTexProject &operator =(const TTexProject &other);
    bool operator ==(const TTexProject &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TTexProject &project);
    friend QDataStream &operator >>(QDataStream &stream, TTexProject &project);
    friend QDebug operator <<(QDebug dbg, const TTexProject &project);
};

Q_DECLARE_METATYPE(TTexProject)

#endif // TTEXPROJECT_H
