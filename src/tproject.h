#ifndef TPROJECT_H
#define TPROJECT_H

class TProjectPrivate;

class QVariant;
class QDebug;
class QDataStream;
class QString;
class QTextCodec;

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
    explicit TProject();
    explicit TProject(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec = 0);
    explicit TProject(const QString &rootFileName, const QString &rootFileText, const QString &codecName);
    explicit TProject(const QString &rootFileName, QTextCodec *codec = 0);
    explicit TProject(const QString &rootFileName, const QString &codecName);
    TProject(const TProject &other);
    ~TProject();
public:
    void clear();
    QString codecName() const;
    TProjectFile *rootFile();
    const TProjectFile *rootFile() const;
    QList<TProjectFile> *files();
    const QList<TProjectFile> *files() const;
    bool load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec);
    bool load(const QString &rootFileName, const QString &rootFileText, const QString &codecName);
    bool load(const QString &rootFileName, QTextCodec *codec = 0);
    bool load(const QString &rootFileName, const QString &codecName);
    bool save(const QString &dir, QTextCodec *codec = 0);
    bool save(const QString &dir, const QString &codecName);
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
