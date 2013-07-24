#ifndef TTEXPROJECT_H
#define TTEXPROJECT_H

class TTexProjectPrivate;

class QVariant;
class QDebug;
class QDataStream;
class QString;
class QTextCodec;
class QStringList;

#include "tglobal.h"
#include "tprojectfile.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TTexProject =================================
============================================================================*/

class TSMP_EXPORT TTexProject : BBase
{
    B_DECLARE_PRIVATE(TTexProject)
public:
    static int size(const QString &rootFilePath, QTextCodec *codec = 0, bool sourceOnly = false);
    static int size(const QString &rootFilePath, const QString &codecName, bool sourceOnly = false);
public:
    explicit TTexProject();
    explicit TTexProject(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec);
    explicit TTexProject(const QString &rootFileName, const QString &rootFileText, const QString &codecName);
    explicit TTexProject(const QString &rootFileName, QTextCodec *codec = 0);
    explicit TTexProject(const QString &rootFileName, const QString &codecName);
    TTexProject(const TTexProject &other);
    ~TTexProject();
public:
    void clear();
    TProjectFile *rootFile();
    const TProjectFile *rootFile() const;
    QList<TProjectFile> *files();
    const QList<TProjectFile> *files() const;
    QString rootFileName() const;
    QStringList externalFiles(bool *ok = 0) const;
    QStringList restrictedCommands() const;
    void removeRestrictedCommands();
    bool prependExternalFileNames(const QString &subdir);
    void replace(const QString &oldString, const QString &newString, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    bool load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec);
    bool load(const QString &rootFileName, const QString &rootFileText, const QString &codecName);
    bool load(const QString &rootFileName, QTextCodec *codec = 0);
    bool load(const QString &rootFileName, const QString &codecName);
    bool save(const QString &dir, QTextCodec *codec = 0) const;
    bool save(const QString &dir, const QString &codecName) const;
    bool isValid() const;
    int size() const;
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
