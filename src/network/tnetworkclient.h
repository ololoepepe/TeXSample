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

#include "tglobal.h"

#include <BeQtCore/BBaseObject>

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
    explicit TNetworkClient(QObject *parent = 0);
    ~TNetworkClient();
protected:
    explicit TNetworkClient(TNetworkClientPrivate &d, QObject *parent = 0);
public:
    //
private:
    Q_DISABLE_COPY(TNetworkClient)
};

#endif // TNETWORKCLIENT_H
