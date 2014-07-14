#ifndef TCOMPILETEXPROJECTREQUESTDATA_H
#define TCOMPILETEXPROJECTREQUESTDATA_H

class TCompileTexProjectRequestDataPrivate;

class TTexCompiler;
class TTexProject;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QTextCodec;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCompileTexProjectRequestData ===============
============================================================================*/

class T_CORE_EXPORT TCompileTexProjectRequestData : public BBase
{
    B_DECLARE_PRIVATE(TCompileTexProjectRequestData)
public:
    explicit TCompileTexProjectRequestData();
    TCompileTexProjectRequestData(const TCompileTexProjectRequestData &other);
    ~TCompileTexProjectRequestData();
public:
    void clear();
    QTextCodec *codec() const;
    QStringList commands() const;
    TTexCompiler compiler() const;
    bool dvipsEnabled() const;
    bool isValid() const;
    bool makeindexEnabled() const;
    QStringList options() const;
    TTexProject project() const;
    void setCodec(QTextCodec *codec);
    void setCommands(const QStringList &commands);
    void setCompiler(const TTexCompiler &compiler);
    void setDvipsEnabled(bool enabled);
    void setMakeindexEnabled(bool enabled);
    void setOptions(const QStringList &options);
    void setProject(const TTexProject &project);
public:
    TCompileTexProjectRequestData &operator =(const TCompileTexProjectRequestData &other);
    bool operator ==(const TCompileTexProjectRequestData &other) const;
    bool operator !=(const TCompileTexProjectRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompileTexProjectRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCompileTexProjectRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TCompileTexProjectRequestData &data);
};

Q_DECLARE_METATYPE(TCompileTexProjectRequestData)

#endif // TCOMPILETEXPROJECTREQUESTDATA_H
