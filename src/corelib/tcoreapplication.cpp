/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleCore module of the TeXSample library.
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

#include "tcoreapplication.h"

#include "tapplicationbase.h"

#include <BCoreApplication>

#include <QString>

/*============================================================================
================================ TCoreApplication ============================
============================================================================*/

/*============================== Public constructors =======================*/

TCoreApplication::TCoreApplication(int &argc, char **argv, const QString &applicationName,
                                   const QString &organizationName) :
    BCoreApplication(argc, argv, applicationName, organizationName), TApplicationBase()
{
    //
}

TCoreApplication::TCoreApplication(int &argc, char **argv, const InitialSettings &s) :
    BCoreApplication(argc, argv, s), TApplicationBase()
{
    //
}

TCoreApplication::~TCoreApplication()
{
    //
}
