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

#ifndef TNETWORKCLIENT_H
#define TNETWORKCLIENT_H

class TNetworkClientPrivate;

class TGroupInfo;
class TReply;
class TUserInfo;

class BNetworkOperation;

class QByteArray;
class QDateTime;
class QString;
class QVariant;
class QWidget;

#include "tglobal.h"

#include <BBaseObject>
#include <BNetworkConnection>

#include <QObject>

/*============================================================================
================================ TNetworkClient ==============================
============================================================================*/

class T_NETWORK_EXPORT TNetworkClient : public QObject, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TNetworkClient)
public:
    enum State
    {
        AuthorizedState = 1,
        ConnectedState,
        ConnectingState,
        DisconnectedState,
        DisconnectingState
    };
public:
    typedef void (*ShowMessageFunction)(const QString &text, const QString &informativeText, bool error,
                                        QWidget *parentWidget);
    typedef bool (*WaitForConnectedFunction)(BNetworkConnection *, int timeout, QWidget *parentWidget, QString *msg);
    typedef bool (*WaitForFinishedFunction)(BNetworkOperation *, int timeout, QWidget *parentWidget, QString *msg);
public:
    explicit TNetworkClient(QObject *parent = 0);
    ~TNetworkClient();
protected:
    explicit TNetworkClient(TNetworkClientPrivate &d, QObject *parent = 0);
public:
    static void defaultShowMessageFunction(const QString &text, const QString &informativeText, bool error,
                                    QWidget *parentWidget);
    static bool defaultWaitForConnectedFunction(BNetworkConnection *connection, int timeout, QWidget *parentWidget,
                                                QString *msg);
    static bool defaultWaitForFinishedFunction(BNetworkOperation *op, int timeout, QWidget *parentWidget,
                                               QString *msg);
public:
    void addAvailableGroup(const TGroupInfo &groupInfo);
    bool cachingEnabled() const;
    QString hostName() const;
    bool isAuthorized() const;
    bool isConnected() const;
    bool isValid(bool anonymous = false) const;
    BNetworkConnection::LoggingMode loggingMode() const;
    QString login() const;
    QByteArray password() const;
    TReply performAnonymousOperation(const QString &operation, const QVariant &data, QWidget *parentWidget = 0);
    TReply performAnonymousOperation(const QString &operation, const QVariant &data, int timeout,
                                     QWidget *parentWidget = 0);
    TReply performAnonymousOperation(const QString &operation, const QVariant &data,
                                     const QDateTime &lastRequestDateTime, QWidget *parentWidget = 0);
    virtual TReply performAnonymousOperation(const QString &operation, const QVariant &data,
                                             const QDateTime &lastRequestDateTime, int timeout,
                                             QWidget *parentWidget = 0);
    TReply performOperation(const QString &operation, const QVariant &data, QWidget *parentWidget = 0);
    TReply performOperation(const QString &operation, const QVariant &data, int timeout, QWidget *parentWidget = 0);
    TReply performOperation(const QString &operation, const QVariant &data, const QDateTime &lastRequestDateTime,
                            QWidget *parentWidget = 0);
    virtual TReply performOperation(const QString &operation, const QVariant &data,
                                    const QDateTime &lastRequestDateTime, int timeout, QWidget *parentWidget = 0);
    int pingInterval() const;
    int pingTimeout() const;
    void removeAvailableGroup(quint64 groupId);
    void setCachingEnabled(bool enabled);
    void setHostName(const QString &hostName);
    void setLoggingMode(BNetworkConnection::LoggingMode mode);
    void setLogin(const QString &login);
    void setPassword(const QByteArray &password);
    void setPingInterval(int msecs);
    void setPingTimeout(int msecs);
    void setShowMessageFunction(ShowMessageFunction function);
    void setWaitForConnectedDelay(int msecs);
    void setWaitForConnectedFunction(WaitForConnectedFunction function);
    void setWaitForConnectedTimeout(int msecs);
    void setWaitForFinishedDelay(int msecs);
    void setWaitForFinishedFunction(WaitForFinishedFunction function);
    void setWaitForFinishedTimeout(int msecs);
    ShowMessageFunction showMessageFunction() const;
    State state() const;
    TUserInfo userInfo() const;
    int waitForConnectedDelay() const;
    WaitForConnectedFunction waitForConnectedFunction() const;
    int waitForConnectedTimeout() const;
    int waitForFinishedDelay() const;
    WaitForFinishedFunction waitForFinishedFunction() const;
    int waitForFinishedTimeout() const;
public Q_SLOTS:
    void connectToServer();
    void disconnectFromServer();
    void reconnect();
Q_SIGNALS:
    void authorizedChanged(bool authorized);
    void connectedChanged(bool connected);
    void hostNameChanged(const QString &hostName);
    void loginChanged(const QString &login);
    void passwordChanged(const QByteArray &password);
    void stateChanged(TNetworkClient::State s);
    void validityChanged(bool valid);
    void anonymousValidityChanged(bool valid);
private:
    Q_DISABLE_COPY(TNetworkClient)
};

#endif // TNETWORKCLIENT_H
