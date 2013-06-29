#include "tcompilationresult.h"
#include "tglobal.h"
#include "toperationresult.h"
#include "toperationresult_p.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>

/*============================================================================
================================ TCompilationResultPrivate ===================
============================================================================*/

class TCompilationResultPrivate : public TOperationResultPrivate
{
    B_DECLARE_PUBLIC(TCompilationResult)
public:
   explicit TCompilationResultPrivate(TCompilationResult *q);
    ~TCompilationResultPrivate();
public:
    void init();
public:
    int exitCode;
    QString log;
private:
    Q_DISABLE_COPY(TCompilationResultPrivate)
};

/*============================================================================
================================ TCompilationResultPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TCompilationResultPrivate::TCompilationResultPrivate(TCompilationResult *q) :
    TOperationResultPrivate(q)
{
    //
}

TCompilationResultPrivate::~TCompilationResultPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCompilationResultPrivate::init()
{
    exitCode = -1;
}

/*============================================================================
================================ TCompilationResult ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TCompilationResult::TCompilationResult(bool success, const QString &errs) :
    TOperationResult(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    setSuccess(success);
    setErrorString(errs);
}

TCompilationResult::TCompilationResult(const QString &errs) :
    TOperationResult(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    setErrorString(errs);
}

TCompilationResult::TCompilationResult(const TCompilationResult &other) :
    TOperationResult(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCompilationResult::TCompilationResult(const TOperationResult &opResult) :
    TOperationResult(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    *this = opResult;
}

TCompilationResult::~TCompilationResult()
{
    //
}

/*============================== Public methods ============================*/

void TCompilationResult::setExitCode(int code)
{
    d_func()->exitCode = code;
}

void TCompilationResult::setLog(const QString &l)
{
    d_func()->log = l;
}

int TCompilationResult::exitCode() const
{
    return d_func()->exitCode;
}

QString TCompilationResult::log() const
{
    return d_func()->log;
}

/*============================== Public operators ==========================*/

TCompilationResult &TCompilationResult::operator =(const TCompilationResult &other)
{
    B_D(TCompilationResult);
    const TCompilationResultPrivate *dd = other.d_func();
    d->success = dd->success;
    d->error = dd->error;
    d->exitCode = dd->exitCode;
    d->log = dd->log;
    return *this;
}

TCompilationResult &TCompilationResult::operator =(const TOperationResult &other)
{
    B_D(TCompilationResult);
    d->success = other.success();
    d->error = other.errorString();
    return *this;
}

bool TCompilationResult::operator ==(const TCompilationResult &other) const
{
    const B_D(TCompilationResult);
    const TCompilationResultPrivate *dd = other.d_func();
    return d->success == dd->success && d->error == dd->error && d->exitCode == dd->exitCode && d->log == dd->log;
}

TCompilationResult::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TCompilationResult::operator bool() const
{
    return d_func()->success;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    stream << d->success;
    stream << d->error;
    stream << d->exitCode;
    stream << d->log;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompilationResult &result)
{
    TCompilationResultPrivate *d = result.d_func();
    stream >> d->success;
    stream >> d->error;
    stream >> d->exitCode;
    stream >> d->log;
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    dbg.nospace() << "TCompilationResult(" << d->success << "," << d->error << "," << d->exitCode << ")";
    return dbg.space();
}
