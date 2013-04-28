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
    d->exitCode = dd->exitCode;
    d->log = dd->log;
    return *this;
}

TCompilationResult &TCompilationResult::operator =(const TOperationResult &other)
{
    (TOperationResult) *this = other;
    return *this;
}

bool TCompilationResult::operator ==(const TCompilationResult &other) const
{
    const B_D(TCompilationResult);
    const TCompilationResultPrivate *dd = other.d_func();
    return (TOperationResult) *this == (TOperationResult) other && d->exitCode == dd->exitCode && d->log == dd->log;
}

TCompilationResult::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    stream << (TOperationResult) result;
    stream << d->exitCode;
    stream << d->log;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompilationResult &result)
{
    TCompilationResultPrivate *d = result.d_func();
    TOperationResult r;
    stream >> r;
    result = r;
    stream >> d->exitCode;
    stream >> d->log;
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    dbg.nospace() << "TCompilationResult(" << d->success << "," << d->exitCode << ")";
    return dbg.space();
}
