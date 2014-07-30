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

#include "tnetworkclient.h"
#include "tnetworkclient_p.h"

#include <BeQtCore/BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

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
    //
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

//
