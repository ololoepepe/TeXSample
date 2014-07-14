#ifndef TTEXFILE_H
#define TTEXFILE_H

class TTexFilePrivate;

class QDataStream;
class QDebug;
class QStringList;
class QTextCodec;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TTexFile ====================================
============================================================================*/

class T_CORE_EXPORT TTexFile : BBase
{
    B_DECLARE_PRIVATE(TTexFile)
public:
    explicit TTexFile(const QString &fileName = QString(), QTextCodec *codec = 0, const QString &subpath = QString());
    TTexFile(const TTexFile &other);
    ~TTexFile();
public:
    void clear();
    QStringList externalFileNames(bool *ok = 0) const;
    QString fileName() const;
    bool isValid() const;
    bool load(const QString &fileName, QTextCodec *codec = 0, const QString &subpath = QString());
    bool prependExternalFileNames(const QString &subpath);
    QString relativeFileName() const;
    void removeRestrictedCommands();
    QStringList restrictedCommands() const;
    bool save(const QString &dir, QTextCodec *codec = 0) const;
    void setFileName(const QString &fileName);
    void setRelativeFileName(const QString &relativeFileName);
    void setSubpath(const QString &subpath);
    void setText(const QString &text);
    int size() const;
    QString subpath() const;
    QString text() const;
public:
    TTexFile &operator =(const TTexFile &other);
    bool operator ==(const TTexFile &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TTexFile &file);
    friend QDataStream &operator >>(QDataStream &stream, TTexFile &file);
    friend QDebug operator <<(QDebug dbg, const TTexFile &file);
};

Q_DECLARE_METATYPE(TTexFile)

#endif // TTEXFILE_H
