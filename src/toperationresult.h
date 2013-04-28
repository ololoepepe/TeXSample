#ifndef TOPERATIONRESULT_H
#define TOPERATIONRESULT_H

class TOperationResultPrivate;

class QDataStream;
class QVariant;
class QDebug;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TOperationResult ============================
============================================================================*/

class TSMP_EXPORT TOperationResult : public BBase
{
    B_DECLARE_PRIVATE(TOperationResult)
public:
    explicit TOperationResult(bool success, const QString &errs = QString());
    explicit TOperationResult(const QString &errs = QString());
    TOperationResult(const TOperationResult &other);
    ~TOperationResult();
protected:
    explicit TOperationResult(TOperationResultPrivate &d);
public:
    void setSuccess(bool b);
    void setErrorString(const QString &s);
    bool success() const;
    QString errorString() const;
public:
    TOperationResult &operator =(const TOperationResult &other);
    bool operator ==(const TOperationResult &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TOperationResult &result);
    friend QDataStream &operator >>(QDataStream &stream, TOperationResult &result);
    friend QDebug operator <<(QDebug dbg, const TOperationResult &result);
};

Q_DECLARE_METATYPE(TOperationResult)

#endif // TOPERATIONRESULT_H
