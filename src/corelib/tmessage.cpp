#include "tmessage.h"
#include "tglobal.h"

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
================================ TMessagePrivate =============================
============================================================================*/

class TMessagePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TMessage)
public:
   explicit TMessagePrivate(TMessage *q);
    ~TMessagePrivate();
public:
    void init();
public:
    TMessage::Message message;
    QString explanation;
private:
    Q_DISABLE_COPY(TMessagePrivate)
};

/*============================================================================
================================ TMessagePrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TMessagePrivate::TMessagePrivate(TMessage *q) :
    BBasePrivate(q)
{
    //
}

TMessagePrivate::~TMessagePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TMessagePrivate::init()
{
    message = TMessage::NoMessage;
}

/*============================================================================
================================ TMessage ====================================
============================================================================*/

/*============================== Static public methods =====================*/

TMessage::Message TMessage::messageFromInt(int msg)
{
    static const QList<int> messages = bRangeD(NoMessage, UnknownError);
    return messages.contains(msg) ? static_cast<Message>(msg) : NoMessage;
}

QString TMessage::messageToString(int msg)
{
    return tr(messageToStringNoTr(msg).toUtf8().constData());
}

QString TMessage::messageToStringNoTr(int msg)
{
    switch (msg)
    {
    //Connection messages
    case AlreadyAuthorizedMessage:
        return QT_TRANSLATE_NOOP("TMessage", "You are already authorized");
    //TerminalIOHandler messages
    case ServerAlreadyRunningMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The server is already running");
    case ServerIsNotRunningMessage:
        return QT_TRANSLATE_NOOP("TMessage", "The server is not running");
    case OkMessage:
        return QT_TRANSLATE_NOOP("TMessage", "OK");
    //Internal errors
    case InternalParametersError:
        return QT_TRANSLATE_NOOP("TMessage", "Internal parameters error occured");
    case InternalFileSystemError:
        return QT_TRANSLATE_NOOP("TMessage", "Internal file system error occured");
    case InternalNetworkError:
        return QT_TRANSLATE_NOOP("TMessage", "Internal network error occured");
    case InternalStorageError:
        return QT_TRANSLATE_NOOP("TMessage", "Internal storage error occured");
    case InternalQueryError:
        return QT_TRANSLATE_NOOP("TMessage", "Internal query error occured");
    case InternalDatabaseError:
        return QT_TRANSLATE_NOOP("TMessage", "Internal database error occured");
    //Storage errors
    case ReadOnlyError:
        return QT_TRANSLATE_NOOP("TMessage", "The operation is not available, "
                                 "because the server is in in read-only mode");
    case InvalidDataError:
        return QT_TRANSLATE_NOOP("TMessage", "The data is invalid");
    case InvalidUserIdError:
        return QT_TRANSLATE_NOOP("TMessage", "The user ID is invalid");
    case InvalidSampleIdError:
        return QT_TRANSLATE_NOOP("TMessage", "The sample ID is invalid");
    case InvalidLabIdError:
        return QT_TRANSLATE_NOOP("TMessage", "The lab ID is invalid");
    case InvalidEmailError:
        return QT_TRANSLATE_NOOP("TMessage", "The e-mail is invalid");
    case InvalidOSTypeError:
        return QT_TRANSLATE_NOOP("TMessage", "The OS type is invalid");
    case NoSuchSampleError:
        return QT_TRANSLATE_NOOP("TMessage", "There is no such sample");
    case NoSuchCodeError:
        return QT_TRANSLATE_NOOP("TMessage", "There is no such code");
    case NoLabForPlatformError:
        return QT_TRANSLATE_NOOP("TMessage", "There is no lab for the given platform");
    case LoginOrEmailOccupiedError:
        return QT_TRANSLATE_NOOP("TMessage", "These login or e-mail are already occupied");
    case SampleAlreadyDeletedError:
        return QT_TRANSLATE_NOOP("TMessage", "The sample is already deleted");
    case LabAlreadyDeletedError:
        return QT_TRANSLATE_NOOP("TMessage", "The lab is already deleted");
    //Connection errors
    case InvalidUserInfoError:
        return QT_TRANSLATE_NOOP("TMessage", "The user info is invalid");
    case InvalidLoginError:
        return QT_TRANSLATE_NOOP("TMessage", "The login is invalid");
    case InvalidPasswordError:
        return QT_TRANSLATE_NOOP("TMessage", "The password is invalid");
    case NoSuchUserError:
        return QT_TRANSLATE_NOOP("TMessage", "There is no such user");
    case NotAuthorizedError:
        return QT_TRANSLATE_NOOP("TMessage", "You are not authorized");
    case NotEnoughRightsError:
        return QT_TRANSLATE_NOOP("TMessage", "You do not have enough rights to do that");
    case CantEditSelfError:
        return QT_TRANSLATE_NOOP("TMessage", "You can not edit your own account");
    case NotOwnAccountError:
        return QT_TRANSLATE_NOOP("TMessage", "This is not your account");
    case NotOwnSampleError:
        return QT_TRANSLATE_NOOP("TMessage", "This is not your sample");
    case NotOwnLabError:
        return QT_TRANSLATE_NOOP("TMessage", "This is not your lab");
    case NotModifiableSampleError:
        return QT_TRANSLATE_NOOP("TMessage", "The sample is not modifiable");
    //Client errors
    case ClientOperationCanceledError:
        return QT_TRANSLATE_NOOP("TMessage", "The operation was canceled");
    case ClientConnectionTimeoutError:
        return QT_TRANSLATE_NOOP("TMessage", "The connection timed out");
    case ClientOperationError:
        return QT_TRANSLATE_NOOP("TMessage", "There was an operation error");
    case ClientFileSystemError:
        return QT_TRANSLATE_NOOP("TMessage", "File system error");
    case ClientInvalidInvitesCountError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid invites count");
    case ClientInvalidSampleInfoError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid sample info");
    case ClientInvalidPathError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid path");
    case ClientInvalidFileNameError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid file name");
    case ClientInvalidLabInfoError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid lab info");
    //TerminalIOHandler errors
    case FailedToStartServerError:
        return QT_TRANSLATE_NOOP("TMessage", "Failed to start server");
    case InvalidCommandArgumentsError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid arguments");
    //Other errors
    case UnknownError:
        return QT_TRANSLATE_NOOP("TMessage", "Unknown error occured");
    case NoMessage:
    default:
        return "";
    }
}

/*============================== Public constructors =======================*/

TMessage::TMessage(int msg, const QString &explanation) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    setMessage(msg);
    setExplanation(explanation);
}

TMessage::TMessage(const TMessage &other) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    *this = other;
}

TMessage::~TMessage()
{
    //
}

/*============================== Protected constructors ====================*/


TMessage::TMessage(TMessagePrivate &d) :
    BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

void TMessage::setMessage(int msg)
{
    d_func()->message = messageFromInt(msg);
}

void TMessage::setExplanation(const QString &s)
{
    d_func()->explanation = s;
}

TMessage::Message TMessage::message() const
{
    return d_func()->message;
}

QString TMessage::messageString() const
{
    return messageToString(d_func()->message);
}

QString TMessage::messageStringNoTr() const
{
    return messageToStringNoTr(d_func()->message);
}

QString TMessage::explanation() const
{
    return d_func()->explanation;
}

/*============================== Public operators ==========================*/

TMessage &TMessage::operator =(const TMessage &other)
{
    d_func()->message = other.d_func()->message;
    d_func()->explanation = other.d_func()->explanation;
    return *this;
}

TMessage &TMessage::operator =(int msg)
{
    d_func()->message = messageFromInt(msg);
    d_func()->explanation.clear();
    return *this;
}

bool TMessage::operator ==(const TMessage &other) const
{
    return d_func()->message == other.d_func()->message && d_func()->explanation == other.d_func()->explanation;
}

bool TMessage::operator ==(int other) const
{
    return d_func()->message == other && d_func()->explanation.isEmpty();
}

TMessage::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TMessage::operator int() const
{
    return d_func()->message;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TMessage &msg)
{
    QVariantMap m;
    m.insert("message", (int) msg.d_func()->message);
    m.insert("explanation", msg.d_func()->explanation);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TMessage &msg)
{
    QVariantMap m;
    stream >> m;
    msg.d_func()->message = TMessage::messageFromInt(m.value("message").toInt());
    msg.d_func()->explanation = m.value("explanation").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TMessage &msg)
{
    dbg.nospace() << "TMessage(" << msg.messageStringNoTr() << "," << msg.explanation() << ")";
    return dbg.space();
}
