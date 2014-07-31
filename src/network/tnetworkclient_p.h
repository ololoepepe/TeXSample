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

class BNetworkConnection;
class BNetworkOperation;

class QWidget;

#include "tnetworkclient.h"

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>

/*============================================================================
================================ TNetworkClientPrivate =======================
============================================================================*/

class TNetworkClientPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TNetworkClient)
public:
    TNetworkClient::WaitForConnectedFunction waitForConnectedFunction;
    TNetworkClient::WaitForFinishedFunction waitForFinishedFunction;
public:
    explicit TNetworkClientPrivate(TNetworkClient *q);
    ~TNetworkClientPrivate();
public:
    void init();
    bool waitForConnected(BNetworkConnection *connection, QWidget *parentWidget);
    bool waitForFinished(BNetworkOperation *operation, QWidget *parentWidget);
private:
    Q_DISABLE_COPY(TNetworkClientPrivate)
};

#endif // TNETWORKCLIENT_P_H
