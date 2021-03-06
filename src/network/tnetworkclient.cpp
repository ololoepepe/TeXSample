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
#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupInfoList>
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
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QMetaObject>
#include <QObject>
#include <QTimer>
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

/*============================== Static public methods =====================*/

bool TNetworkClientPrivate::handleNoopRequest(BNetworkOperation *op)
{
    op->reply();
    return true;
}

/*============================== Public methods ============================*/

void TNetworkClientPrivate::init()
{
    pingInterval = 0;
    pingTimeout = 5 * BeQt::Minute;
    connect(&pingTimer, SIGNAL(timeout()), this, SLOT(ping()));
    caching = false;
    connection = new BNetworkConnection(BGenericSocket::TcpSocket, this);
    connection->setLoggingMode(BNetworkConnection::NoLogging);
    connect(connection, SIGNAL(connected()), this, SLOT(connected()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connection->installRequestHandler(BNetworkConnection::NoopOperation, &handleNoopRequest);
    reconnecting = false;
    showMessageFunction = &TNetworkClient::defaultShowMessageFunction;
    state = TNetworkClient::DisconnectedState;
    waitForConnectedDelay = BeQt::Second / 2;
    waitForConnectedFunction = &TNetworkClient::defaultWaitForConnectedFunction;
    waitForConnectedTimeout = 10 * BeQt::Second;
    waitForFinishedDelay = BeQt::Second / 2;
    waitForFinishedFunction = &TNetworkClient::defaultWaitForFinishedFunction;
    waitForFinishedTimeout = -1;
}

TReply TNetworkClientPrivate::performOperation(BNetworkConnection *connection, const QString &operation,
                                               const QVariant &data, const QDateTime &lastRequestDateTime, int timeout,
                                               QWidget *parentWidget)
{
    if (operation.isEmpty())
        return TReply(tr("Invalid parameter (internal error)", "error"));
    if (hostName.isEmpty())
        return TReply(tr("Invalid TNetworkClient instance (no host name)", "error"));
    bool scopedConnection = !connection;
    if (scopedConnection) {
        connection = new BNetworkConnection(BGenericSocket::TcpSocket);
        connection->setLoggingMode(this->connection->loggingMode());
        connection->connectToHost(hostName, Texsample::MainPort);
        QString msg;
        if (!waitForConnected(connection, parentWidget, &msg)) {
            delete connection;
            return TReply(msg);
        }
    }
    TRequest request(data);
    request.setLocale(BApplicationBase::locale());
    request.setCachingEnabled(caching);
    request.setLastRequestDateTime(lastRequestDateTime);
    BNetworkOperation *op(connection->sendRequest(operation, request));
    QString msg;
    if (!waitForFinished(op, timeout, parentWidget, &msg)) {
        if (scopedConnection)
            connection->deleteLater();
        else
            connection->close();
        op->deleteLater();
        return TReply(msg);
    }
    op->deleteLater();
    if (scopedConnection)
        connection->deleteLater();
    if (op->isError())
        return TReply(tr("Operation error", "error"));
    return op->variantData().value<TReply>();
}

void TNetworkClientPrivate::setState(TNetworkClient::State s, TUserInfo info)
{
    if (s == state)
        return;
    B_Q(TNetworkClient);
    bool isConnected = q->isConnected();
    state = s;
    userInfo = info;
    QMetaObject::invokeMethod(q, "stateChanged", Q_ARG(TNetworkClient::State, s));
    if (TNetworkClient::AuthorizedState == s || TNetworkClient::AuthorizedState == state)
        QMetaObject::invokeMethod(q, "authorizedChanged", Q_ARG(bool, TNetworkClient::AuthorizedState == state));
    bool isConnectedNew = q->isConnected();
    if (isConnected != isConnectedNew)
        QMetaObject::invokeMethod(q, "connectedChanged", Q_ARG(bool, isConnectedNew));
}

void TNetworkClientPrivate::showMessage(const QString &text, const QString &informativeText, bool error,
                                        QWidget *parentWidget)
{
    if (showMessageFunction)
        return showMessageFunction(text, informativeText, error, parentWidget);
    return TNetworkClient::defaultShowMessageFunction(text, informativeText, error, parentWidget);
}

bool TNetworkClientPrivate::waitForConnected(BNetworkConnection *connection, QWidget *parentWidget, QString *msg)
{
    if (!connection)
        return bRet(msg, tr("Null connection pointer", "error"), false);
    if (connection->error() != QAbstractSocket::UnknownSocketError)
        return bRet(msg, connection->errorString(), false);
    if (connection->isConnected())
        return bRet(msg, QString(), true);
    BeQt::waitNonBlocking(connection, SIGNAL(connected()), waitForConnectedDelay);
    if (connection->isConnected())
        return bRet(msg, QString(), true);
    if (waitForConnectedFunction)
        return waitForConnectedFunction(connection, waitForConnectedTimeout, parentWidget, msg);
    return TNetworkClient::defaultWaitForConnectedFunction(connection, waitForConnectedTimeout, parentWidget, msg);
}

bool TNetworkClientPrivate::waitForFinished(BNetworkOperation *operation, int timeout, QWidget *parentWidget,
                                            QString *msg)
{
    if (!operation)
        return bRet(msg, tr("Null connection pointer", "error"), false);
    if (operation->isFinished() || operation->waitForFinished(waitForFinishedDelay))
        return bRet(msg, QString(), true);
    if (waitForFinishedFunction)
        return waitForFinishedFunction(operation, timeout, parentWidget, msg);
    return TNetworkClient::defaultWaitForFinishedFunction(operation, timeout, parentWidget, msg);
}

/*============================== Public slots ==============================*/

void TNetworkClientPrivate::connected()
{
    setState(TNetworkClient::ConnectedState);
    TAuthorizeRequestData requestData;
    requestData.setIdentifier(login);
    requestData.setPassword(password);
    requestData.setClientInfo(TClientInfo::create());
    TReply reply = q_func()->performOperation(TOperation::Authorize, requestData);
    if (reply.success()) {
        TAuthorizeReplyData replyData = reply.data().value<TAuthorizeReplyData>();
        setState(TNetworkClient::AuthorizedState, replyData.userInfo());
        if (pingInterval > 0 && pingTimeout > 0)
            pingTimer.start(pingInterval);
    } else {
        q_func()->disconnectFromServer();
        showMessage(reply.message(), "", true);
    }
}

void TNetworkClientPrivate::disconnected()
{
    pingTimer.stop();
    setState(TNetworkClient::DisconnectedState);
    if (reconnecting) {
        reconnecting = false;
        q_func()->connectToServer();
    }
}

void TNetworkClientPrivate::error(QAbstractSocket::SocketError)
{
    pingTimer.stop();
    setState(TNetworkClient::DisconnectedState);
    QString errorString = connection->errorString();
    if (connection->isConnected())
        connection->close();
    showMessage(tr("An error occured", "message text"), errorString, true);
}

void TNetworkClientPrivate::ping()
{
    if (pingTimeout <= 0)
        return pingTimer.stop();
    BNetworkOperation *op = connection->sendRequest(BNetworkConnection::operation(BNetworkConnection::NoopOperation));
    op->setAutoDelete(true);
    if (!op->waitForFinished(pingTimeout))
        q_func()->disconnectFromServer();
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

/*============================== Static public methods =====================*/

void TNetworkClient::defaultShowMessageFunction(const QString &, const QString &, bool, QWidget *)
{
    //Do nothing
}

bool TNetworkClient::defaultWaitForConnectedFunction(BNetworkConnection *connection, int timeout, QWidget *,
                                                     QString *msg)
{
    if (!connection)
        return bRet(msg, tr("Null connection pointer", "error"), false);
    if (connection->error() != QAbstractSocket::UnknownSocketError)
        return bRet(msg, connection->errorString(), false);
    if (connection->isConnected())
        return bRet(msg, QString(), true);
    BeQt::waitNonBlocking(connection, SIGNAL(connected()), timeout);
    if (connection->isConnected())
        return bRet(msg, QString(), true);
    return bRet(msg, connection->errorString(), false);
}

bool TNetworkClient::defaultWaitForFinishedFunction(BNetworkOperation *op, int timeout, QWidget *, QString *msg)
{
    if (!op)
        return bRet(msg, tr("Null connection pointer", "error"), false);
    if (op->isFinished())
        return bRet(msg, QString(), true);
    if (op->waitForFinished(timeout))
        return bRet(msg, QString(), true);
    return bRet(msg, tr("Operation timed out", "error"), false);
}

/*============================== Public methods ============================*/

void TNetworkClient::addAvailableGroup(const TGroupInfo &groupInfo)
{
    if (!groupInfo.isValid())
        return;
    TUserInfo &info = d_func()->userInfo;
    TGroupInfoList list = info.availableGroups();
    list << groupInfo;
    info.setAvailableGroups(list);
}

bool TNetworkClient::cachingEnabled() const
{
    return d_func()->caching;
}

QString TNetworkClient::hostName() const
{
    return d_func()->hostName;
}

void TNetworkClient::installRequestHandler(const QString &operation, BNetworkConnection::ExternalHandler handler)
{
    d_func()->connection->installRequestHandler(operation, handler);
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

BNetworkConnection::LoggingMode TNetworkClient::loggingMode() const
{
    return d_func()->connection->loggingMode();
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
    return performAnonymousOperation(operation, data, QDateTime(), parentWidget);
}

TReply TNetworkClient::performAnonymousOperation(const QString &operation, const QVariant &data, int timeout,
                                                 QWidget *parentWidget)
{
    return performAnonymousOperation(operation, data, QDateTime(), timeout, parentWidget);
}

TReply TNetworkClient::performAnonymousOperation(const QString &operation, const QVariant &data,
                                                 const QDateTime &lastRequestDateTime, QWidget *parentWidget)
{
    return performAnonymousOperation(operation, data, lastRequestDateTime, d_func()->waitForFinishedTimeout,
                                     parentWidget);
}

TReply TNetworkClient::performAnonymousOperation(const QString &operation, const QVariant &data,
                                                 const QDateTime &lastRequestDateTime, int timeout,
                                                 QWidget *parentWidget)
{
    return d_func()->performOperation(0, operation, data, lastRequestDateTime, timeout, parentWidget);
}

TReply TNetworkClient::performOperation(const QString &operation, const QVariant &data, QWidget *parentWidget)
{
    return performOperation(operation, data, QDateTime(), parentWidget);
}

TReply TNetworkClient::performOperation(const QString &operation, const QVariant &data, int timeout,
                                        QWidget *parentWidget)
{
    return performOperation(operation, data, QDateTime(), timeout, parentWidget);
}

TReply TNetworkClient::performOperation(const QString &operation, const QVariant &data,
                                        const QDateTime &lastRequestDateTime, QWidget *parentWidget)
{
    return performOperation(operation, data, lastRequestDateTime, d_func()->waitForFinishedTimeout, parentWidget);
}

TReply TNetworkClient::performOperation(const QString &operation, const QVariant &data,
                                        const QDateTime &lastRequestDateTime, int timeout, QWidget *parentWidget)
{
    if (!isAuthorized() && TOperation::Authorize != operation)
        return TReply(tr("Not authorized", "error"));
    return d_func()->performOperation(d_func()->connection, operation, data, lastRequestDateTime, timeout,
                                      parentWidget);
}

int TNetworkClient::pingInterval() const
{
    return d_func()->pingInterval;
}

int TNetworkClient::pingTimeout() const
{
    return d_func()->pingTimeout;
}

void TNetworkClient::removeAvailableGroup(quint64 groupId)
{
    if (!groupId)
        return;
    TUserInfo &info = d_func()->userInfo;
    TGroupInfoList list = info.availableGroups();
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).id() == groupId) {
            list.removeAt(i);
            break;
        }
    }
    info.setAvailableGroups(list);
}

void TNetworkClient::setCachingEnabled(bool enabled)
{
    d_func()->caching = enabled;
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

void TNetworkClient::setLoggingMode(BNetworkConnection::LoggingMode mode)
{
    d_func()->connection->setLoggingMode(mode);
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
    QByteArray pwd = Texsample::testPassword(password) ? password : QByteArray();
    B_D(TNetworkClient);
    bool b = pwd != d->password;
    bool bvalid = isValid();
    d->password = pwd;
    if (b)
        Q_EMIT passwordChanged(pwd);
    if (bvalid != isValid())
        Q_EMIT validityChanged(!bvalid);
}

void TNetworkClient::setPingInterval(int msecs)
{
    B_D(TNetworkClient);
    d->pingInterval = (msecs > 0) ? msecs : 0;
    d->pingTimer.stop();
    if (msecs > 0 && d->pingTimeout > 0 && isAuthorized())
        d->pingTimer.start(msecs);
}

void TNetworkClient::setPingTimeout(int msecs)
{
    d_func()->pingTimeout = (msecs > 0) ? msecs : 0;
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
    if (!isValid() || DisconnectedState != d_func()->state)
        return;
    B_D(TNetworkClient);
    d->setState(ConnectingState);
    d->connection->connectToHost(d->hostName, Texsample::MainPort);
}

void TNetworkClient::disconnectFromServer()
{
    B_D(TNetworkClient);
    if (DisconnectedState == d->state || DisconnectingState == d->state)
        return;
    if (ConnectingState == d->state) {
        d->connection->abort();
        d->setState(DisconnectedState);
    } else {
        d->setState(DisconnectingState);
        d->connection->disconnectFromHost();
    }
}

void TNetworkClient::reconnect()
{
    if (DisconnectedState == d_func()->state || DisconnectingState == d_func()->state)
        return;
    d_func()->reconnecting = true;
    disconnectFromServer();
}
