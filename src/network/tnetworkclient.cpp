/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleNetwork module of the TeXSample library.
**
** TeXSample is free software: you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** TeXSample is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with TeXSample.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

class QWidget;

#include "tnetworkclient.h"
#include "tnetworkclient_p.h"

#include <TeXSampleCore/TAuthorizeReplyData>
#include <TeXSampleCore/TAuthorizeRequestData>
#include <TeXSampleCore/TClientInfo>
#include <TeXSampleCore/TeXSample>
#include <TeXSampleCore/TMessage>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TRequest>
#include <TeXSampleCore/TUserInfo>

#include <BApplicationBase>
#include <BBaseObject>
#include <BeQt>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGenericSocket>
#include <BNetworkConnection>
#include <BNetworkOperation>

#include <QAbstractSocket>
#include <QList>
#include <QMetaObject>
#include <QObject>
#include <QScopedPointer>
#include <QVariant>

/*============================================================================
================================ TNetworkClientPrivate =======================
============================================================================*/

/*============================== Public constructors =======================*/

TNetworkClientPrivate::TNetworkClientPrivate(TNetworkClient *q) :
    BBaseObjectPrivate(q)
{
    //
}

TNetworkClientPrivate::~TNetworkClientPrivate()
{
    //
}

/*============================== Public methods ============================*/

TReply TNetworkClientPrivate::performOperation(const QString &operation, const QVariant &data, QWidget *parentWidget)
{
    return performOperation(0, operation, data, parentWidget);
}

TReply TNetworkClientPrivate::performOperation(BNetworkConnection *connection, const QString &operation,
                                               const QVariant &data, QWidget *parentWidget)
{
    if (operation.isEmpty())
        return TReply(TMessage(TMessage::InternalErrorMessage, "Invalid parameter (operation)"));
    if (hostName.isEmpty())
        return TReply(TMessage(TMessage::InternalErrorMessage, "Invalid TNetworkClient instance (no host name)"));
    bool scopedConnection = !connection;
    if (scopedConnection) {
        connection = new BNetworkConnection(BGenericSocket::TcpSocket);
        connection->connectToHost(hostName, Texsample::MainPort);
        TMessage msg;
        if (!waitForConnected(connection, parentWidget, &msg)) {
            delete connection;
            return TReply(msg);
        }
    }
    QScopedPointer<BNetworkOperation> op(connection->sendRequest(operation, TRequest(data)));
    TMessage msg;
    if (!waitForFinished(op.data(), parentWidget, &msg)) {
        if (scopedConnection)
            delete connection;
        else
            connection->close();
        return TReply(msg);
    }
    if (scopedConnection)
        delete connection;
    else
        connection->close();
    if (op->isError())
        return TReply(TMessage::OperationErrorMessage);
    return op->variantData().value<TReply>();
}

void TNetworkClientPrivate::init()
{
    connection = new BNetworkConnection(BGenericSocket::TcpSocket, this);
    connect(connection, SIGNAL(connected()), this, SLOT(connected()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    reconnecting = false;
    showMessageFunction = 0;
    state = TNetworkClient::DisconnectedState;
    waitForConnectedDelay = BeQt::Second / 2;
    waitForConnectedFunction = 0;
    waitForConnectedTimeout = 10 * BeQt::Second;
    waitForFinishedDelay = BeQt::Second / 2;
    waitForFinishedFunction = 0;
    waitForFinishedTimeout = -1;
}

void TNetworkClientPrivate::setState(TNetworkClient::State s, TUserInfo info)
{
    if (s == state)
        return;
    B_Q(TNetworkClient);
    bool isConnected = q->isConnected();
    bool canConnect = q->canConnect();
    bool canDisconnect = q->canDisconnect();
    state = s;
    QMetaObject::invokeMethod(q, "stateChanged", Q_ARG(TNetworkClient::State, s));
    if (TNetworkClient::AuthorizedState == s || TNetworkClient::AuthorizedState == state)
        QMetaObject::invokeMethod(q, "authorizedChanged", Q_ARG(bool, TNetworkClient::AuthorizedState == state));
    bool isConnectedNew = q->isConnected();
    bool canConnectNew = q->canConnect();
    bool canDisconnectNew = q->canDisconnect();
    if (isConnected != isConnectedNew)
        QMetaObject::invokeMethod(q, "connectedChanged", Q_ARG(bool, isConnectedNew));
    if (canConnect != canConnectNew)
        QMetaObject::invokeMethod(q, "canConnectChanged", Q_ARG(bool, canConnectNew));
    if (canDisconnect != canDisconnectNew)
        QMetaObject::invokeMethod(q, "canDisconnectChanged", Q_ARG(bool, canDisconnectNew));
    userInfo = info;
}

void TNetworkClientPrivate::showMessage(const QString &text, const QString &informativeText)
{
    if (showMessageFunction)
        showMessageFunction(text, informativeText, 0);
}

bool TNetworkClientPrivate::waitForConnected(BNetworkConnection *connection, QWidget *parentWidget, TMessage *message)
{
    if (!connection)
        return bRet(message, TMessage(TMessage::InternalErrorMessage, "Null connection pointer"), false);
    if (connection->isConnected())
        return bRet(message, TMessage(), true);
    BeQt::waitNonBlocking(connection, SIGNAL(connected()), waitForConnectedDelay);
    if (connection->isConnected())
        return bRet(message, TMessage(), true);
    if (waitForConnectedFunction)
        return waitForConnectedFunction(connection, waitForConnectedTimeout, parentWidget, message);
    BeQt::waitNonBlocking(connection, SIGNAL(connected()), waitForConnectedTimeout);
    if (connection->isConnected())
        return bRet(message, TMessage(), true);
    return bRet(message, TMessage(TMessage::ConnectionTimeoutMessage, connection->errorString()), false);
}

bool TNetworkClientPrivate::waitForFinished(BNetworkOperation *operation, QWidget *parentWidget, TMessage *message)
{
    if (!operation)
        return bRet(message, TMessage(TMessage::InternalErrorMessage, "Null operation pointer"), false);
    if (operation->isFinished() || operation->waitForFinished(waitForFinishedDelay))
        return bRet(message, TMessage(), true);
    if (waitForFinishedFunction)
        return waitForFinishedFunction(operation, waitForFinishedTimeout, parentWidget, message);
    if (operation->waitForFinished(waitForFinishedTimeout))
        return bRet(message, TMessage(), true);
    return bRet(message, TMessage(TMessage::OperationTimeoutMessage), false);
}

/*============================== Public slots ==============================*/

void TNetworkClientPrivate::connected()
{
    setState(TNetworkClient::ConnectedState);
    TAuthorizeRequestData requestData;
    requestData.setIdentifier(login);
    requestData.setPassword(password);
    requestData.setClientInfo(TClientInfo::create());
    TReply reply = performOperation(connection, TOperation::Authorize, requestData);
    if (reply.success()) {
        TAuthorizeReplyData replyData = reply.data().value<TAuthorizeReplyData>();
        setState(TNetworkClient::AuthorizedState, replyData.userInfo());
    } else {
        q_func()->disconnectFromServer();
        showMessage(reply.message().text(), reply.message().extraText());
    }
}

void TNetworkClientPrivate::disconnected()
{
    setState(TNetworkClient::DisconnectedState);
    if (reconnecting) {
        reconnecting = false;
        q_func()->connectToServer();
    }
}

void TNetworkClientPrivate::error(QAbstractSocket::SocketError)
{
    setState(TNetworkClient::DisconnectedState);
    QString errorString = connection->errorString();
    if (connection->isConnected())
        connection->close();
    showMessage(tr("An error occured", "message text"), errorString);
}

/*============================================================================
================================ TNetworkClient ==============================
============================================================================*/

/*============================== Public constructors =======================*/

TNetworkClient::TNetworkClient(QObject *parent) :
    QObject(parent), BBaseObject(*new TNetworkClientPrivate(this))
{
    d_func()->init();
}

TNetworkClient::~TNetworkClient()
{
    //
}

/*============================== Protected constructors ====================*/

TNetworkClient::TNetworkClient(TNetworkClientPrivate &d, QObject *parent) :
    QObject(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

bool TNetworkClient::canConnect() const
{
    return (DisconnectedState == d_func()->state) && isValid();
}

bool TNetworkClient::canDisconnect() const
{
    const B_D(TNetworkClient);
    return (ConnectingState == d->state || ConnectedState == d->state || AuthorizedState == d->state);
}

QString TNetworkClient::hostName() const
{
    return d_func()->hostName;
}

bool TNetworkClient::isAuthorized() const
{
    return (AuthorizedState == d_func()->state);
}

bool TNetworkClient::isConnected() const
{
    return (ConnectedState == d_func()->state || AuthorizedState == d_func()->state);
}

bool TNetworkClient::isValid(bool anonymous) const
{
    return !d_func()->hostName.isEmpty()
            && (anonymous || (!d_func()->login.isEmpty() && !d_func()->password.isEmpty()));
}

QString TNetworkClient::login() const
{
    return d_func()->login;
}

QByteArray TNetworkClient::password() const
{
    return d_func()->password;
}

TReply TNetworkClient::performAnonymousOperation(const QString &operation, const QVariant &data, QWidget *parentWidget)
{
    return d_func()->performOperation(operation, data, parentWidget);
}

TReply TNetworkClient::performOperation(const QString &operation, const QVariant &data, QWidget *parentWidget)
{
    if (!isAuthorized())
        return TReply(TMessage(TMessage::InternalErrorMessage, "Not authorized"));
    return d_func()->performOperation(d_func()->connection, operation, data, parentWidget);
}

void TNetworkClient::setHostName(const QString &hostName)
{
    B_D(TNetworkClient);
    bool b = hostName != d->hostName;
    bool bvalid = isValid();
    bool bvalida = isValid(true);
    d->hostName = hostName;
    if (b)
        Q_EMIT hostNameChanged(hostName);
    if (bvalid != isValid())
        Q_EMIT validityChanged(!bvalid);
    if (bvalida != isValid(true))
        Q_EMIT anonymousValidityChanged(!bvalida);
}

void TNetworkClient::setLogin(const QString &login)
{
    B_D(TNetworkClient);
    bool b = login != d->login;
    bool bvalid = isValid();
    d->login = login;
    if (b)
        Q_EMIT loginChanged(login);
    if (bvalid != isValid())
        Q_EMIT validityChanged(!bvalid);
}

void TNetworkClient::setPassword(const QByteArray &password)
{
    QByteArray pwd = Texsample::testPassword(password) ? pwd : QByteArray();
    B_D(TNetworkClient);
    bool b = pwd != d->password;
    bool bvalid = isValid();
    d->password = pwd;
    if (b)
        Q_EMIT passwordChanged(pwd);
    if (bvalid != isValid())
        Q_EMIT validityChanged(!bvalid);
}

void TNetworkClient::setShowMessageFunction(ShowMessageFunction function)
{
    d_func()->showMessageFunction = function;
}

void TNetworkClient::setWaitForConnectedDelay(int msecs)
{
    d_func()->waitForConnectedDelay = (msecs > 0) ? msecs : -1;
}

void TNetworkClient::setWaitForConnectedFunction(WaitForConnectedFunction function)
{
    d_func()->waitForConnectedFunction = function;
}

void TNetworkClient::setWaitForConnectedTimeout(int msecs)
{
    d_func()->waitForConnectedTimeout = (msecs > 0) ? msecs : -1;
}

void TNetworkClient::setWaitForFinishedDelay(int msecs)
{
    d_func()->waitForFinishedDelay = (msecs > 0) ? msecs : -1;
}

void TNetworkClient::setWaitForFinishedFunction(WaitForFinishedFunction function)
{
    d_func()->waitForFinishedFunction = function;
}

void TNetworkClient::setWaitForFinishedTimeout(int msecs)
{
    d_func()->waitForFinishedTimeout = (msecs > 0) ? msecs : -1;
}

TNetworkClient::ShowMessageFunction TNetworkClient::showMessageFunction() const
{
    return d_func()->showMessageFunction;
}

TNetworkClient::State TNetworkClient::state() const
{
    return d_func()->state;
}

TUserInfo TNetworkClient::userInfo() const
{
    return d_func()->userInfo;
}

int TNetworkClient::waitForConnectedDelay() const
{
    return d_func()->waitForConnectedDelay;
}

TNetworkClient::WaitForConnectedFunction TNetworkClient::waitForConnectedFunction() const
{
    return d_func()->waitForConnectedFunction;
}

int TNetworkClient::waitForConnectedTimeout() const
{
    return d_func()->waitForConnectedTimeout;
}

int TNetworkClient::waitForFinishedDelay() const
{
    return d_func()->waitForFinishedDelay;
}

TNetworkClient::WaitForFinishedFunction TNetworkClient::waitForFinishedFunction() const
{
    return d_func()->waitForFinishedFunction;
}

int TNetworkClient::waitForFinishedTimeout() const
{
    return d_func()->waitForFinishedTimeout;
}

/*============================== Public slots ==============================*/

void TNetworkClient::connectToServer()
{
    if (!canConnect())
        return;
    B_D(TNetworkClient);
    d->setState(ConnectingState);
    d->connection->connectToHost(d->hostName, Texsample::MainPort);
}

void TNetworkClient::disconnectFromServer()
{
    if (!isConnected())
        return;
    if (ConnectingState == d_func()->state) {
        d_func()->connection->abort();
        d_func()->setState(DisconnectedState);
    } else {
        d_func()->setState(DisconnectingState);
        d_func()->connection->disconnectFromHost();
    }
}

void TNetworkClient::reconnect()
{
    if (DisconnectedState == d_func()->state || DisconnectingState == d_func()->state)
        return;
    d_func()->reconnecting = true;
    disconnectFromServer();
}
