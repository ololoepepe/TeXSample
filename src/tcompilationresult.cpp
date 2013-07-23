#include "tcompilationresult.h"
#include "tglobal.h"
#include "toperationresult.h"
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

TCompilationResult::TCompilationResult(bool success, int msg) :
    TOperationResult(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    setSuccess(success);
    setMessage(msg);
}

TCompilationResult::TCompilationResult(int msg) :
    TOperationResult(*new TCompilationResultPrivate(this))
{
    d_func()->init();
    setMessage(msg);
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
    d->message = dd->message;
    d->exitCode = dd->exitCode;
    d->log = dd->log;
    return *this;
}

TCompilationResult &TCompilationResult::operator =(const TOperationResult &other)
{
    B_D(TCompilationResult);
    d->success = other.success();
    d->message = other.message();
    return *this;
}

bool TCompilationResult::operator ==(const TCompilationResult &other) const
{
    const B_D(TCompilationResult);
    const TCompilationResultPrivate *dd = other.d_func();
    return d->success == dd->success && d->message == dd->message && d->exitCode == dd->exitCode && d->log == dd->log;
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
    QVariantMap m;
    m.insert("success", d->success);
    m.insert("message", d->message);
    m.insert("exitCode", d->exitCode);
    m.insert("log", d->log);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompilationResult &result)
{
    TCompilationResultPrivate *d = result.d_func();
    QVariantMap m;
    stream >> m;
    d->success = m.value("success").toBool();
    d->message = m.value("message").value<TMessage>();
    d->exitCode = m.value("exitCode").toInt();
    d->log = m.value("log").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompilationResult &result)
{
    const TCompilationResultPrivate *d = result.d_func();
    dbg.nospace() << "TCompilationResult(" << d->success << "," << d->message.messageStringNoTr()
                  << "," << d->exitCode << ")";
    return dbg.space();
}
