#ifndef TCOMPILATIONRESULT_H
#define TCOMPILATIONRESULT_H

class TCompilationResultPrivate;

class QDataStream;
class QVariant;
class QDebug;

#include "tglobal.h"
#include "toperationresult.h"
#include "tmessage.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TCompilationResult ==========================
============================================================================*/

class T_CORE_EXPORT TCompilationResult : public TOperationResult
{
    B_DECLARE_PRIVATE(TCompilationResult)
public:
    explicit TCompilationResult(bool success, int msg = TMessage::NoMessage);
    explicit TCompilationResult(int msg = TMessage::NoMessage);
    TCompilationResult(const TCompilationResult &other);
    TCompilationResult(const TOperationResult &opResult);
    ~TCompilationResult();
public:
    void setExitCode(int code);
    void setLog(const QString &l);
    int exitCode() const;
    QString log() const;
public:
    TCompilationResult &operator =(const TCompilationResult &other);
    TCompilationResult &operator =(const TOperationResult &other);
    bool operator ==(const TCompilationResult &other) const;
    operator QVariant() const;
    operator bool() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompilationResult &result);
    friend QDataStream &operator >>(QDataStream &stream, TCompilationResult &result);
    friend QDebug operator <<(QDebug dbg, const TCompilationResult &result);
};

Q_DECLARE_METATYPE(TCompilationResult)

#endif // TCOMPILATIONRESULT_H
