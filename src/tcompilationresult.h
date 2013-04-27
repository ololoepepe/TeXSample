#ifndef TCOMPILATIONRESULT_H
#define TCOMPILATIONRESULT_H

class TCompilationResultPrivate;

class QDataStream;
class QVariant;
class QDebug;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TCompilationResult ==========================
============================================================================*/

class TSMP_EXPORT TCompilationResult : public BBase
{
    B_DECLARE_PRIVATE(TCompilationResult)
public:
    explicit TCompilationResult(const QString &errs = QString());
    TCompilationResult(const TCompilationResult &other);
    ~TCompilationResult();
public:
    void setSuccess(bool b);
    void setExitCode(int code);
    void setLog(const QString &l);
    void setErrorString(const QString &s);
    bool success() const;
    int exitCode() const;
    QString log() const;
    QString errorString() const;
public:
    TCompilationResult &operator =(const TCompilationResult &other);
    bool operator ==(const TCompilationResult &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompilationResult &result);
    friend QDataStream &operator >>(QDataStream &stream, TCompilationResult &result);
    friend QDebug operator <<(QDebug dbg, const TCompilationResult &result);
};

Q_DECLARE_METATYPE(TCompilationResult)

#endif // TCOMPILATIONRESULT_H
