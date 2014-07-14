#ifndef TCOMPILETEXPROJECTREPLYDATA_H
#define TCOMPILETEXPROJECTREPLYDATA_H

class TCompileTexProjectReplyDataPrivate;

class TBinaryFileList;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCompileTexProjectReplyData =================
============================================================================*/

class TCompileTexProjectReplyData : public BBase
{
    B_DECLARE_PRIVATE(TCompileTexProjectReplyData)
public:
    explicit TCompileTexProjectReplyData();
    TCompileTexProjectReplyData(const TCompileTexProjectReplyData &other);
    ~TCompileTexProjectReplyData();
public:
    int exitCode() const;
    TBinaryFileList files() const;
    QString output() const;
    void setExitCode(int code);
    void setFiles(const TBinaryFileList &files);
    void setOutput(const QString &output);
public:
    TCompileTexProjectReplyData &operator =(const TCompileTexProjectReplyData &other);
    bool operator ==(const TCompileTexProjectReplyData &other) const;
    bool operator !=(const TCompileTexProjectReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompileTexProjectReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCompileTexProjectReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TCompileTexProjectReplyData &data);
};

Q_DECLARE_METATYPE(TCompileTexProjectReplyData)

#endif // TCOMPILETEXPROJECTREPLYDATA_H
