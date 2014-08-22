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

#ifndef TNETWORKCLIENT_P_H
#define TNETWORKCLIENT_P_H

class TReply;

class BNetworkConnection;
class BNetworkOperation;

class QDateTime;
class QVariant;
class QWidget;

#include "tnetworkclient.h"

#include <TeXSampleCore/TUserInfo>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QAbstractSocket>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QTimer>

/*============================================================================
================================ TNetworkClientPrivate =======================
============================================================================*/

class TNetworkClientPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TNetworkClient)
public:
    bool caching;
    BNetworkConnection *connection;
    QString hostName;
    QString login;
    QByteArray password;
    int pingInterval;
    int pingTimeout;
    bool reconnecting;
    TNetworkClient::ShowMessageFunction showMessageFunction;
    TNetworkClient::State state;
    QTimer pingTimer;
    TUserInfo userInfo;
    int waitForConnectedDelay;
    TNetworkClient::WaitForConnectedFunction waitForConnectedFunction;
    int waitForConnectedTimeout;
    int waitForFinishedDelay;
    TNetworkClient::WaitForFinishedFunction waitForFinishedFunction;
    int waitForFinishedTimeout;
public:
    explicit TNetworkClientPrivate(TNetworkClient *q);
    ~TNetworkClientPrivate();
public:
    static bool handleNoopRequest(BNetworkOperation *op);
public:
    void init();
    TReply performOperation(BNetworkConnection *connection, const QString &operation, const QVariant &data,
                            const QDateTime &lastRequestDateTime, int timeout, QWidget *parentWidget = 0);
    void setState(TNetworkClient::State s, TUserInfo info = TUserInfo());
    void showMessage(const QString &text, const QString &informativeText = QString(), bool error = true,
                     QWidget *parentWidget = 0);
    bool waitForConnected(BNetworkConnection *connection, QWidget *parentWidget = 0, QString *msg = 0);
    bool waitForFinished(BNetworkOperation *operation, int timeout, QWidget *parentWidget = 0, QString *msg = 0);
public Q_SLOTS:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError error);
    void ping();
private:
    Q_DISABLE_COPY(TNetworkClientPrivate)
};

#endif // TNETWORKCLIENT_P_H
