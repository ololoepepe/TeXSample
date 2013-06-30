#ifndef TPROJECT_H
#define TPROJECT_H

class TProjectPrivate;

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
================================ TProject ====================================
============================================================================*/

class TSMP_EXPORT TProject : BBase
{
    B_DECLARE_PRIVATE(TProject)
public:
    static int size(const QString &rootFilePath, QTextCodec *codec = 0);
    static int size(const QString &rootFilePath, const QString &codecName);
public:
    explicit TProject();
    explicit TProject(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec);
    explicit TProject(const QString &rootFileName, const QString &rootFileText, const QString &codecName);
    explicit TProject(const QString &rootFileName, QTextCodec *codec = 0);
    explicit TProject(const QString &rootFileName, const QString &codecName);
    TProject(const TProject &other);
    ~TProject();
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
