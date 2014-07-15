#include "tmessage.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TMessagePrivate =============================
============================================================================*/

class TMessagePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TMessage)
public:
    QString extraText;
    TMessage::Message message;
public:
   explicit TMessagePrivate(TMessage *q);
    ~TMessagePrivate();
public:
    void init();
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

/*============================== Public constructors =======================*/

TMessage::TMessage(int msg) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
}

TMessage::TMessage(int msg, const QString &extraText) :
    BBase(*new TMessagePrivate(this))
{
    d_func()->init();
    *this = msg;
    d_func()->extraText = extraText;
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

QString TMessage::extraText() const
{
    return d_func()->extraText;
}

void TMessage::setExtraText(const QString &extraText)
{
    d_func()->extraText = extraText;
}

QString TMessage::text() const
{
    return tr(textNoTr().toUtf8().constData());
}

QString TMessage::textNoTr() const
{
    switch (d_func()->message)
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
    case InvalidFileNameError:
        return QT_TRANSLATE_NOOP("TMessage", "Invalid file name");
    case NoSuchFileError:
        return QT_TRANSLATE_NOOP("TMessage", "No such file");
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
    case UnknownApplicationError:
        return QT_TRANSLATE_NOOP("TMessage", "Unknown application");
    case UnknownError:
        return QT_TRANSLATE_NOOP("TMessage", "Unknown error occured");
    case NoMessage:
    default:
        return "";
    }
}

/*============================== Public operators ==========================*/

TMessage &TMessage::operator =(const TMessage &other)
{
    d_func()->message = other.d_func()->message;
    d_func()->extraText = other.d_func()->extraText;
    return *this;
}

TMessage &TMessage::operator =(int msg)
{
    d_func()->message = enum_cast<Message>(msg, NoMessage, UnknownError);
    d_func()->extraText.clear();
    return *this;
}

bool TMessage::operator ==(const TMessage &other) const
{
    return d_func()->message == other.d_func()->message && d_func()->extraText == other.d_func()->extraText;
}

bool TMessage::operator !=(const TMessage &other) const
{
    return !(*this == other);
}

TMessage::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TMessage::operator QString() const
{
    return text();
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
    m.insert("extra_text", msg.d_func()->extraText);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TMessage &msg)
{
    QVariantMap m;
    stream >> m;
    msg.d_func()->message = enum_cast<TMessage::Message>(m.value("message"), TMessage::NoMessage,
                                                         TMessage::UnknownError);
    msg.d_func()->extraText = m.value("extra_text").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TMessage &msg)
{
    dbg.nospace() << "TMessage(" << msg.textNoTr() << "," << msg.extraText() << ")";
    return dbg.space();
}
