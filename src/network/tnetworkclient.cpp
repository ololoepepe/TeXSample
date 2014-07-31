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

#include <BBaseObject>
#include <BeQt>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BNetworkConnection>
#include <BNetworkOperation>

#include <QAbstractSocket>
#include <QList>
#include <QObject>

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

void TNetworkClientPrivate::init()
{
    waitForConnectedFunction = 0;
    waitForFinishedFunction = 0;
}

bool TNetworkClientPrivate::waitForConnected(BNetworkConnection *connection, QWidget *parentWidget)
{
    if (!connection)
        return false;
    if (connection->isConnected())
        return true;
    if (waitForConnectedFunction)
        return waitForConnectedFunction(connection, parentWidget);
    QList<BeQt::Until> until;
    until << BeQt::until(connection, SIGNAL(connected()));
    until << BeQt::until(connection, SIGNAL(disconnected()));
    until << BeQt::until(connection, SIGNAL(error(QAbstractSocket::SocketError)));
    BeQt::waitNonBlocking(until);
    return connection->isConnected();
}

bool TNetworkClientPrivate::waitForFinished(BNetworkOperation *operation, QWidget *parentWidget)
{
    if (!operation)
        return false;
    if (operation->isFinished())
        return true;
    if (waitForFinishedFunction)
        return waitForFinishedFunction(operation, parentWidget);
    QList<BeQt::Until> until;
    until << BeQt::until(operation, SIGNAL(finished()));
    until << BeQt::until(operation, SIGNAL(error()));
    until << BeQt::until(operation, SIGNAL(canceled()));
    BeQt::waitNonBlocking(until, BeQt::Second);
    return operation->isFinished();
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

void TNetworkClient::setWaitForConnectedFunction(WaitForConnectedFunction function)
{
    d_func()->waitForConnectedFunction = function;
}

void TNetworkClient::setWaitForFinishedFunction(WaitForFinishedFunction function)
{
    d_func()->waitForFinishedFunction = function;
}

TNetworkClient::WaitForConnectedFunction TNetworkClient::waitForConnectedFunction() const
{
    return d_func()->waitForConnectedFunction;
}

TNetworkClient::WaitForFinishedFunction TNetworkClient::waitForFinishedFunction() const
{
    return d_func()->waitForFinishedFunction;
}
