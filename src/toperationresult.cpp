#include "toperationresult.h"
#include "tglobal.h"
#include "toperationresult_p.h"
#include "tmessage.h"

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
    message = TMessage::NoMessage;
}

/*============================================================================
================================ TOperationResult ============================
============================================================================*/

/*============================== Public constructors =======================*/

TOperationResult::TOperationResult(bool success, int msg) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    setSuccess(success);
    setMessage(msg);
}

TOperationResult::TOperationResult(int msg) :
    BBase(*new TOperationResultPrivate(this))
{
    d_func()->init();
    setMessage(msg);
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

void TOperationResult::setMessage(int msg)
{
    d_func()->message = msg;
}

bool TOperationResult::success() const
{
    return d_func()->success;
}

TMessage TOperationResult::message() const
{
    return d_func()->message;
}

QString TOperationResult::messageString() const
{
    return d_func()->message.messageString();
}

QString TOperationResult::messageStringNoTr() const
{
    return d_func()->message.messageStringNoTr();
}

/*============================== Public operators ==========================*/

TOperationResult &TOperationResult::operator =(const TOperationResult &other)
{
    B_D(TOperationResult);
    const TOperationResultPrivate *dd = other.d_func();
    d->success = dd->success;
    d->message = dd->message;
    return *this;
}

bool TOperationResult::operator ==(const TOperationResult &other) const
{
    const B_D(TOperationResult);
    const TOperationResultPrivate *dd = other.d_func();
    return d->success == dd->success && d->message == dd->message;
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
    m.insert("message", d->message);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TOperationResult &result)
{
    TOperationResultPrivate *d = result.d_func();
    QVariantMap m;
    stream >> m;
    d->success = m.value("success").toBool();
    d->message = m.value("message").value<TMessage>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TOperationResult &result)
{
    dbg.nospace() << "TOperationResult(" << result.d_func()->success << "," << result.messageStringNoTr() << ")";
    return dbg.space();
}
