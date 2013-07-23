#ifndef TMESSAGE_H
#define TMESSAGE_H

class TMessagePrivate;

class QDataStream;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>

/*============================================================================
================================ TMessage ====================================
============================================================================*/

class TSMP_EXPORT TMessage : public BBase
{
    B_DECLARE_PRIVATE(TMessage)
    Q_DECLARE_TR_FUNCTIONS(TMessage)
public:
    enum Message
    {
        NoMessage = 0,
        //Connection messages
        AlreadyAuthorizedMessage,
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
        InvalidEmailError,
        NoSuchSampleError,
        NoSuchCodeError,
        LoginOrEmailOccupiedError,
        SampleAlreadyDeletedError,
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
        NotModifiableSampleError,
        //Other errors
        UnknownError
    };
public:
    static Message messageFromInt(int msg);
    static QString messageToString(int msg);
    static QString messageToStringNoTr(int msg);
public:
    TMessage(int msg = NoMessage);
    TMessage(const TMessage &other);
    ~TMessage();
protected:
    explicit TMessage(TMessagePrivate &d);
public:
    void setMessage(int msg);
    Message message() const;
    QString messageString() const;
    QString messageStringNoTr() const;
public:
    TMessage &operator =(const TMessage &other);
    TMessage &operator =(int msg);
    bool operator ==(const TMessage &other) const;
    bool operator ==(int other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TMessage &msg);
    friend QDataStream &operator >>(QDataStream &stream, TMessage &msg);
    friend QDebug operator <<(QDebug dbg, const TMessage &msg);
};

Q_DECLARE_METATYPE(TMessage)

#endif // TMESSAGE_H