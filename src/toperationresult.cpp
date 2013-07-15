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
#include <QVariantMap>
#include <QList>

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
    error = TOperationResult::NoError;
}

/*============================================================================
================================ TOperationResult ============================
============================================================================*/

/*============================== Static public methods =====================*/

TOperationResult::Error TOperationResult::errorFromInt(int err)
{
    static const QList<int> errors = bRangeD(NoError, NoError);
    return errors.contains(err) ? static_cast<Error>(err) : NoError;
}

QString TOperationResult::errorToString(int err)
{
    switch (err)
    {
    case NoError:
    default:
        return "";
    }
}

QString TOperationResult::errorToStringNoTr(int err)
{
    switch (err)
    {
    case NoError:
    default:
        return "";
    }
}

/*============================== Public constructors =======================*/

TOperationResult::TOperationResult(bool success, int err) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    setSuccess(success);
    setError(err);
}

TOperationResult::TOperationResult(int err) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    setError(err);
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

void TOperationResult::setError(int err)
{
    d_func()->error = errorFromInt(err);
}

bool TOperationResult::success() const
{
    return d_func()->success;
}

TOperationResult::Error TOperationResult::error() const
{
    return d_func()->error;
}

QString TOperationResult::errorString() const
{
    return errorToString(d_func()->error);
}

QString TOperationResult::errorStringNoTr() const
{
    return errorToStringNoTr(d_func()->error);
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

TOperationResult::operator bool() const
{
    return d_func()->success;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TOperationResult &result)
{
    const TOperationResultPrivate *d = result.d_func();
    QVariantMap m;
    m.insert("success", d->success);
    m.insert("error", (int) d->error);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TOperationResult &result)
{
    TOperationResultPrivate *d = result.d_func();
    QVariantMap m;
    stream >> m;
    d->success = m.value("success").toBool();
    d->error = TOperationResult::errorFromInt(m.value("error").toInt());
    return stream;
}

QDebug operator <<(QDebug dbg, const TOperationResult &result)
{
    dbg.nospace() << "TOperationResult(" << result.d_func()->success << "," << result.errorStringNoTr() << ")";
    return dbg.space();
}
