#include "tcompilationresult.h"
#include "tglobal.h"

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

class TCompilationResultPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCompilationResult)
public:
   explicit TCompilationResultPrivate(TCompilationResult *q);
    ~TCompilationResultPrivate();
public:
    void init();
public:
    bool success;
    int exitCode;
    QString log;
    QString error;
private:
    Q_DISABLE_COPY(TCompilationResultPrivate)
};

/*============================================================================
================================ TCompilationResultPrivate ===================
============================================================================*/

/*============================== Public constructors =======================*/

TCompilationResultPrivate::TCompilationResultPrivate(TCompilationResult *q) :
    BBasePrivate(q)
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
    success = false;
    exitCode = -1;
}

/*============================================================================
================================ TCompilationResult ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TCompilationResult::TCompilationResult(const QString &errs) :
    BBase(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    setErrorString(errs);
}

TCompilationResult::TCompilationResult(const TCompilationResult &other) :
    BBase(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCompilationResult::~TCompilationResult()
{
    //
}

/*============================== Public methods ============================*/

void TCompilationResult::setSuccess(bool b)
{
    d_func()->success = b;
}

void TCompilationResult::setExitCode(int code)
{
    d_func()->exitCode = code;
}

void TCompilationResult::setLog(const QString &l)
{
    d_func()->log = l;
}

void TCompilationResult::setErrorString(const QString &s)
{
    d_func()->error = s;
}

bool TCompilationResult::success() const
{
    return d_func()->success;
}

int TCompilationResult::exitCode() const
{
    return d_func()->exitCode;
}

QString TCompilationResult::log() const
{
    return d_func()->log;
}

QString TCompilationResult::errorString() const
{
    return d_func()->error;
}

/*============================== Public operators ==========================*/

TCompilationResult &TCompilationResult::operator =(const TCompilationResult &other)
{
    B_D(TCompilationResult);
    const TCompilationResultPrivate *dd = other.d_func();
    d->success = dd->success;
    d->exitCode = dd->exitCode;
    d->log = dd->log;
    d->error = dd->error;
    return *this;
}

bool TCompilationResult::operator ==(const TCompilationResult &other) const
{
    const B_D(TCompilationResult);
    const TCompilationResultPrivate *dd = other.d_func();
    return d->success == dd->success && d->exitCode == dd->exitCode && d->log == dd->log && d->error == dd->error;
}

TCompilationResult::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    stream << d->success;
    stream << d->exitCode;
    stream << d->log;
    stream << d->error;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompilationResult &result)
{
    TCompilationResultPrivate *d = result.d_func();
    stream >> d->success;
    stream >> d->exitCode;
    stream >> d->log;
    stream >> d->error;
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    dbg.nospace() << "TCompilationResult(" << d->success << "," << d->exitCode << ")";
    return dbg.space();
}
