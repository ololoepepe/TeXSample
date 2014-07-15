#ifndef TMESSAGE_H
#define TMESSAGE_H

class TMessagePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TMessage ====================================
============================================================================*/

class T_CORE_EXPORT TMessage : public BBase
{
    B_DECLARE_PRIVATE(TMessage)
    Q_DECLARE_TR_FUNCTIONS(TMessage)
public:
    enum Message
    {
        NoMessage = 0,
        //Connection messages
        AlreadyAuthorizedMessage,
        //TerminalIOHandler messages
        ServerAlreadyRunningMessage,
        ServerIsNotRunningMessage,
        OkMessage,
        //Internal errors
        InternalParametersError,
        InternalFileSystemError,
        InternalNetworkError,
        InternalStorageError,
        InternalQueryError,
        InternalDatabaseError,
        //Storage errors
        ReadOnlyError,
        InvalidDataError,
        InvalidUserIdError,
        InvalidSampleIdError,
        InvalidLabIdError,
        InvalidEmailError,
        InvalidOSTypeError,
        NoSuchSampleError,
        NoSuchCodeError,
        NoLabForPlatformError,
        LoginOrEmailOccupiedError,
        SampleAlreadyDeletedError,
        LabAlreadyDeletedError,
        //Connection errors
        InvalidUserInfoError,
        InvalidLoginError,
        InvalidPasswordError,
        NoSuchUserError,
        NotAuthorizedError,
        NotEnoughRightsError,
        CantEditSelfError,
        NotOwnAccountError,
        NotOwnSampleError,
        NotOwnLabError,
        NotModifiableSampleError,
        InvalidFileNameError,
        NoSuchFileError,
        //Client errors
        ClientOperationCanceledError,
        ClientConnectionTimeoutError,
        ClientOperationError,
        ClientFileSystemError,
        ClientInvalidInvitesCountError,
        ClientInvalidSampleInfoError,
        ClientInvalidPathError,
        ClientInvalidFileNameError,
        ClientInvalidLabInfoError,
        //TerminalIOHandler errors
        FailedToStartServerError,
        InvalidCommandArgumentsError,
        //Other errors
        UnknownApplicationError,
        UnknownError
    };
public:
    TMessage(int msg = NoMessage);
    explicit TMessage(int msg, const QString &extraText);
    TMessage(const TMessage &other);
    ~TMessage();
protected:
    explicit TMessage(TMessagePrivate &d);
public:
    QString extraText() const;
    void setExtraText(const QString &extraText);
    QString text() const;
    QString textNoTr() const;
public:
    TMessage &operator =(const TMessage &other);
    TMessage &operator =(int msg);
    bool operator ==(const TMessage &other) const;
    bool operator !=(const TMessage &other) const;
    operator QVariant() const;
    operator QString() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TMessage &msg);
    friend QDataStream &operator >>(QDataStream &stream, TMessage &msg);
    friend QDebug operator <<(QDebug dbg, const TMessage &msg);
};

Q_DECLARE_METATYPE(TMessage)

#endif // TMESSAGE_H
