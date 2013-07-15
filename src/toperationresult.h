#ifndef TOPERATIONRESULT_H
#define TOPERATIONRESULT_H

class TOperationResultPrivate;

class QDataStream;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TOperationResult ============================
============================================================================*/

class TSMP_EXPORT TOperationResult : public BBase
{
    B_DECLARE_PRIVATE(TOperationResult)
public:
    enum Error
    {
        NoError = 0
    };
public:
    static Error errorFromInt(int err);
    static QString errorToString(int err);
    static QString errorToStringNoTr(int err);
public:
    explicit TOperationResult(bool success, int err = NoError);
    explicit TOperationResult(int err = NoError);
    TOperationResult(const TOperationResult &other);
    ~TOperationResult();
protected:
    explicit TOperationResult(TOperationResultPrivate &d);
public:
    void setSuccess(bool b);
    void setError(int err);
    bool success() const;
    Error error() const;
    QString errorString() const;
    QString errorStringNoTr() const;
public:
    TOperationResult &operator =(const TOperationResult &other);
    bool operator ==(const TOperationResult &other) const;
    operator QVariant() const;
    operator bool() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TOperationResult &result);
    friend QDataStream &operator >>(QDataStream &stream, TOperationResult &result);
    friend QDebug operator <<(QDebug dbg, const TOperationResult &result);
};

Q_DECLARE_METATYPE(TOperationResult)

#endif // TOPERATIONRESULT_H
