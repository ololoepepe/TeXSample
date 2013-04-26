#ifndef TPROJECTFILE_H
#define TPROJECTFILE_H

class TProjectFilePrivate;

class QVariant;
class QDebug;
class QDataStream;
class QTextCodec;
class QByteArray;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TProjectFile ================================
============================================================================*/

class TSMP_EXPORT TProjectFile : BBase
{
    B_DECLARE_PRIVATE(TProjectFile)
public:
    enum Type
    {
        Binary,
        Text
    };
public:
    explicit TProjectFile();
    explicit TProjectFile(const QString &fileName, const QByteArray &data);
    explicit TProjectFile(const QString &fileName, const QString &text);
    explicit TProjectFile(const QString &fileName, Type type, QTextCodec *codec = 0);
    explicit TProjectFile(const QString &fileName, Type type, const QString &codecName);
    TProjectFile(const TProjectFile &other);
    ~TProjectFile();
public:
    void setFileName(const QString &fileName);
    void setData(const QByteArray &data);
    void setText(const QString &text);
    void clear();
    QString fileName() const;
    Type type() const;
    QByteArray data() const;
    QString text() const;
    bool loadAsBinary(const QString &fileName);
    bool loadAsText(const QString &fileName, QTextCodec *codec = 0);
    bool loadAsText(const QString &fileName, const QString &codecName);
    bool save(const QString &dir, QTextCodec *codec = 0) const;
    bool save(const QString &dir, const QString &codecName) const;
    bool isValid() const;
    int size() const;
public:
    TProjectFile &operator =(const TProjectFile &other);
    bool operator ==(const TProjectFile &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TProjectFile &file);
    friend QDataStream &operator >>(QDataStream &stream, TProjectFile &file);
    friend QDebug operator <<(QDebug dbg, const TProjectFile &file);
};

Q_DECLARE_METATYPE(TProjectFile)

#endif // TPROJECTFILE_H
