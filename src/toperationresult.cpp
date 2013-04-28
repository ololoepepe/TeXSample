#include "toperationresult.h"
#include "tglobal.h"
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
================================ TOperationResultPrivate =====================
============================================================================*/

/*============================== Public constructors =======================*/

TOperationResultPrivate::TOperationResultPrivate(TOperationResult *q) :
    BBasePrivate(q)
{
    //
}

TOperationResultPrivate::~TOperationResultPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TOperationResultPrivate::init()
{
    success = false;
}

/*============================================================================
================================ TOperationResult ============================
============================================================================*/

/*============================== Public constructors =======================*/

TOperationResult::TOperationResult(bool success, const QString &errs) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    setSuccess(success);
    setErrorString(errs);
}

TOperationResult::TOperationResult(const QString &errs) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    setErrorString(errs);
}

TOperationResult::TOperationResult(const TOperationResult &other) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    *this = other;
}

TOperationResult::~TOperationResult()
{
    //
}

/*============================== Protected constructors ====================*/


TOperationResult::TOperationResult(TOperationResultPrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

void TOperationResult::setSuccess(bool b)
{
    d_func()->success = b;
}

void TOperationResult::setErrorString(const QString &s)
{
    d_func()->error = s;
}

bool TOperationResult::success() const
{
    return d_func()->success;
}

QString TOperationResult::errorString() const
{
    return d_func()->error;
}

/*============================== Public operators ==========================*/

TOperationResult &TOperationResult::operator =(const TOperationResult &other)
{
    B_D(TOperationResult);
    const TOperationResultPrivate *dd = other.d_func();
    d->success = dd->success;
    d->error = dd->error;
    return *this;
}

bool TOperationResult::operator ==(const TOperationResult &other) const
{
    const B_D(TOperationResult);
    const TOperationResultPrivate *dd = other.d_func();
    return d->success == dd->success && d->error == dd->error;
}

TOperationResult::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TOperationResult &result)
{
    const TOperationResultPrivate *d = result.d_func();
    stream << d->success;
    stream << d->error;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TOperationResult &result)
{
    TOperationResultPrivate *d = result.d_func();
    stream >> d->success;
    stream >> d->error;
    return stream;
}

QDebug operator <<(QDebug dbg, const TOperationResult &result)
{
    dbg.nospace() << "TOperationResult(" << result.d_func()->success << ")";
    return dbg.space();
}
